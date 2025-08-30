#ifndef GAME_H
#define GAME_H

#include "raylib.h"

#define MAX_ENEMIES 50
#define MAX_TOWERS 20
#define MAX_PROJECTILES 100
#define GRID_SIZE 40

typedef struct {
    Vector2 position;
    float health;
    float max_health;
    float speed;
    int path_index;
    bool active;
    Color color;
} Enemy;

typedef struct {
    Vector2 position;
    float range;
    float damage;
    float fire_rate;
    float last_shot;
    bool active;
    Color color;
} Tower;

typedef struct {
    Vector2 position;
    Vector2 velocity;
    float damage;
    int target_enemy;
    bool active;
} Projectile;

typedef struct {
    Enemy enemies[MAX_ENEMIES];
    Tower towers[MAX_TOWERS];
    Projectile projectiles[MAX_PROJECTILES];
    Vector2 path[20];
    int path_length;
    int money;
    int lives;
    int wave;
    float spawn_timer;
} GameState;

void InitGame(void);
void UpdateGame(void);
void DrawGame(void);
void CleanupGame(void);

#endif