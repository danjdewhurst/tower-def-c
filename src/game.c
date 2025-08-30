#include "game.h"
#include <math.h>
#include <stdlib.h>
#include <string.h>

static GameState game;

static Vector2 GetGridPosition(Vector2 world_pos) {
    return (Vector2) {floorf(world_pos.x / GRID_SIZE) * GRID_SIZE + GRID_SIZE / 2,
                      floorf(world_pos.y / GRID_SIZE) * GRID_SIZE + GRID_SIZE / 2};
}

static float Vector2Distance(Vector2 a, Vector2 b) {
    return sqrtf((a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y));
}

void InitGame(void) {
    memset(&game, 0, sizeof(GameState));

    game.path[0] = (Vector2) {0, 400};
    game.path[1] = (Vector2) {200, 400};
    game.path[2] = (Vector2) {200, 200};
    game.path[3] = (Vector2) {600, 200};
    game.path[4] = (Vector2) {600, 600};
    game.path[5] = (Vector2) {1000, 600};
    game.path[6] = (Vector2) {1000, 400};
    game.path[7] = (Vector2) {1200, 400};
    game.path_length = 8;

    game.money = 100;
    game.lives = 20;
    game.wave = 1;
    game.spawn_timer = 0;

    Wave shoot_wave = {0};
    shoot_wave.frameCount = 1000;
    shoot_wave.sampleRate = 22050;
    shoot_wave.sampleSize = 16;
    shoot_wave.channels = 1;
    shoot_wave.data =
        RL_CALLOC(shoot_wave.frameCount * shoot_wave.channels, sizeof(short));
    for(unsigned int i = 0; i < shoot_wave.frameCount; i++) {
        ((short *) shoot_wave.data)[i] =
            (short) (sin(2 * PI * 440 * i / shoot_wave.sampleRate) * 0.3 * 32767 *
                     exp(-5.0 * i / shoot_wave.frameCount));
    }
    game.shoot_sound = LoadSoundFromWave(shoot_wave);
    UnloadWave(shoot_wave);

    Wave hit_wave = {0};
    hit_wave.frameCount = 800;
    hit_wave.sampleRate = 22050;
    hit_wave.sampleSize = 16;
    hit_wave.channels = 1;
    hit_wave.data = RL_CALLOC(hit_wave.frameCount * hit_wave.channels, sizeof(short));
    for(unsigned int i = 0; i < hit_wave.frameCount; i++) {
        ((short *) hit_wave.data)[i] =
            (short) (sin(2 * PI * 220 * i / hit_wave.sampleRate) * 0.4 * 32767 *
                     exp(-3.0 * i / hit_wave.frameCount));
    }
    game.hit_sound = LoadSoundFromWave(hit_wave);
    UnloadWave(hit_wave);

    Wave place_wave = {0};
    place_wave.frameCount = 1200;
    place_wave.sampleRate = 22050;
    place_wave.sampleSize = 16;
    place_wave.channels = 1;
    place_wave.data =
        RL_CALLOC(place_wave.frameCount * place_wave.channels, sizeof(short));
    for(unsigned int i = 0; i < place_wave.frameCount; i++) {
        ((short *) place_wave.data)[i] =
            (short) (sin(2 * PI * 330 * i / place_wave.sampleRate) * 0.2 * 32767);
    }
    game.place_sound = LoadSoundFromWave(place_wave);
    UnloadWave(place_wave);

    Wave death_wave = {0};
    death_wave.frameCount = 1500;
    death_wave.sampleRate = 22050;
    death_wave.sampleSize = 16;
    death_wave.channels = 1;
    death_wave.data =
        RL_CALLOC(death_wave.frameCount * death_wave.channels, sizeof(short));
    for(unsigned int i = 0; i < death_wave.frameCount; i++) {
        float freq = 110 - 50.0 * i / death_wave.frameCount;
        ((short *) death_wave.data)[i] =
            (short) (sin(2 * PI * freq * i / death_wave.sampleRate) * 0.3 * 32767 *
                     exp(-2.0 * i / death_wave.frameCount));
    }
    game.enemy_death_sound = LoadSoundFromWave(death_wave);
    UnloadWave(death_wave);
}

static void SpawnEnemy(void) {
    for(int i = 0; i < MAX_ENEMIES; i++) {
        if(!game.enemies[i].active) {
            game.enemies[i].position = game.path[0];
            game.enemies[i].health = 50;
            game.enemies[i].max_health = 50;
            game.enemies[i].speed = 50;
            game.enemies[i].path_index = 0;
            game.enemies[i].active = true;
            game.enemies[i].color = RED;
            break;
        }
    }
}

static void UpdateEnemies(void) {
    float dt = GetFrameTime();

    for(int i = 0; i < MAX_ENEMIES; i++) {
        if(!game.enemies[i].active)
            continue;

        Enemy *enemy = &game.enemies[i];

        if(enemy->path_index >= game.path_length - 1) {
            game.lives--;
            enemy->active = false;
            continue;
        }

        Vector2 target = game.path[enemy->path_index + 1];
        Vector2 direction = {target.x - enemy->position.x,
                             target.y - enemy->position.y};
        float distance = sqrtf(direction.x * direction.x + direction.y * direction.y);

        if(distance < 5) {
            enemy->path_index++;
        } else {
            direction.x /= distance;
            direction.y /= distance;
            enemy->position.x += direction.x * enemy->speed * dt;
            enemy->position.y += direction.y * enemy->speed * dt;
        }

        if(enemy->health <= 0) {
            game.money += 10;
            enemy->active = false;
            PlaySound(game.enemy_death_sound);
        }
    }
}

static void UpdateTowers(void) {
    float dt = GetFrameTime();

    for(int i = 0; i < MAX_TOWERS; i++) {
        if(!game.towers[i].active)
            continue;

        Tower *tower = &game.towers[i];
        tower->last_shot += dt;

        if(tower->last_shot < 1.0f / tower->fire_rate)
            continue;

        int closest_enemy = -1;
        float closest_distance = tower->range;

        for(int j = 0; j < MAX_ENEMIES; j++) {
            if(!game.enemies[j].active)
                continue;

            float distance = Vector2Distance(tower->position, game.enemies[j].position);
            if(distance < closest_distance) {
                closest_distance = distance;
                closest_enemy = j;
            }
        }

        if(closest_enemy >= 0) {
            for(int k = 0; k < MAX_PROJECTILES; k++) {
                if(!game.projectiles[k].active) {
                    Vector2 direction = {
                        game.enemies[closest_enemy].position.x - tower->position.x,
                        game.enemies[closest_enemy].position.y - tower->position.y};
                    float distance =
                        sqrtf(direction.x * direction.x + direction.y * direction.y);
                    direction.x /= distance;
                    direction.y /= distance;

                    game.projectiles[k].position = tower->position;
                    game.projectiles[k].velocity =
                        (Vector2) {direction.x * 400, direction.y * 400};
                    game.projectiles[k].damage = tower->damage;
                    game.projectiles[k].target_enemy = closest_enemy;
                    game.projectiles[k].active = true;
                    tower->last_shot = 0;
                    PlaySound(game.shoot_sound);
                    break;
                }
            }
        }
    }
}

static void UpdateProjectiles(void) {
    float dt = GetFrameTime();

    for(int i = 0; i < MAX_PROJECTILES; i++) {
        if(!game.projectiles[i].active)
            continue;

        Projectile *proj = &game.projectiles[i];
        proj->position.x += proj->velocity.x * dt;
        proj->position.y += proj->velocity.y * dt;

        if(proj->position.x < 0 || proj->position.x > 1200 || proj->position.y < 0 ||
           proj->position.y > 800) {
            proj->active = false;
            continue;
        }

        for(int j = 0; j < MAX_ENEMIES; j++) {
            if(!game.enemies[j].active)
                continue;

            if(Vector2Distance(proj->position, game.enemies[j].position) < 15) {
                game.enemies[j].health -= proj->damage;
                proj->active = false;
                PlaySound(game.hit_sound);
                break;
            }
        }
    }
}

void UpdateGame(void) {
    float dt = GetFrameTime();

    game.spawn_timer += dt;
    if(game.spawn_timer > 1.5f) {
        SpawnEnemy();
        game.spawn_timer = 0;
    }

    UpdateEnemies();
    UpdateTowers();
    UpdateProjectiles();

    if(IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
        Vector2 mouse_pos = GetMousePosition();
        Vector2 grid_pos = GetGridPosition(mouse_pos);

        bool can_place = true;
        for(int i = 0; i < game.path_length; i++) {
            if(Vector2Distance(grid_pos, game.path[i]) < GRID_SIZE) {
                can_place = false;
                break;
            }
        }

        if(can_place && game.money >= 50) {
            for(int i = 0; i < MAX_TOWERS; i++) {
                if(!game.towers[i].active) {
                    game.towers[i].position = grid_pos;
                    game.towers[i].range = 100;
                    game.towers[i].damage = 25;
                    game.towers[i].fire_rate = 1;
                    game.towers[i].last_shot = 0;
                    game.towers[i].active = true;
                    game.towers[i].color = BLUE;
                    game.money -= 50;
                    PlaySound(game.place_sound);
                    break;
                }
            }
        }
    }
}

void DrawGame(void) {
    for(int i = 1; i < game.path_length; i++) {
        DrawLineEx(game.path[i - 1], game.path[i], 8, BROWN);
    }

    for(int i = 0; i < MAX_TOWERS; i++) {
        if(game.towers[i].active) {
            DrawCircleV(game.towers[i].position, 15, game.towers[i].color);
            DrawCircleLines((int) game.towers[i].position.x,
                            (int) game.towers[i].position.y,
                            game.towers[i].range,
                            LIGHTGRAY);
        }
    }

    Vector2 mouse_pos = GetMousePosition();
    Vector2 grid_pos = GetGridPosition(mouse_pos);

    bool can_place = true;
    for(int i = 0; i < game.path_length; i++) {
        if(Vector2Distance(grid_pos, game.path[i]) < GRID_SIZE) {
            can_place = false;
            break;
        }
    }

    for(int i = 0; i < MAX_TOWERS; i++) {
        if(game.towers[i].active &&
           Vector2Distance(grid_pos, game.towers[i].position) < GRID_SIZE) {
            can_place = false;
            break;
        }
    }

    if(can_place && game.money >= 50) {
        Color preview_color = (Color) {0, 0, 255, 80};
        DrawCircleV(grid_pos, 15, preview_color);
        DrawCircleLines((int) grid_pos.x, (int) grid_pos.y, 100, preview_color);
    }

    for(int i = 0; i < MAX_ENEMIES; i++) {
        if(game.enemies[i].active) {
            DrawCircleV(game.enemies[i].position, 12, game.enemies[i].color);

            float health_ratio = game.enemies[i].health / game.enemies[i].max_health;
            DrawRectangle((int) (game.enemies[i].position.x - 15),
                          (int) (game.enemies[i].position.y - 20),
                          (int) (30 * health_ratio),
                          4,
                          GREEN);
            DrawRectangle((int) (game.enemies[i].position.x - 15 + 30 * health_ratio),
                          (int) (game.enemies[i].position.y - 20),
                          (int) (30 * (1 - health_ratio)),
                          4,
                          RED);
        }
    }

    for(int i = 0; i < MAX_PROJECTILES; i++) {
        if(game.projectiles[i].active) {
            DrawCircleV(game.projectiles[i].position, 3, YELLOW);
        }
    }

    DrawText(TextFormat("Money: $%d", game.money), 10, 10, 20, WHITE);
    DrawText(TextFormat("Lives: %d", game.lives), 10, 35, 20, WHITE);
    DrawText(TextFormat("Wave: %d", game.wave), 10, 60, 20, WHITE);
    DrawText("Left click to place tower ($50)", 10, 750, 16, WHITE);
}

void CleanupGame(void) {
    UnloadSound(game.shoot_sound);
    UnloadSound(game.hit_sound);
    UnloadSound(game.place_sound);
    UnloadSound(game.enemy_death_sound);
}