#include "game.h"
#include "raylib.h"

#define SCREEN_WIDTH 1200
#define SCREEN_HEIGHT 800

int main(void) {
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Tower Defense");
    SetTargetFPS(60);

    InitGame();

    while(!WindowShouldClose()) {
        UpdateGame();

        BeginDrawing();
        ClearBackground(DARKGREEN);
        DrawGame();
        EndDrawing();
    }

    CleanupGame();
    CloseWindow();

    return 0;
}