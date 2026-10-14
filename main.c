#include "raylib.h"
#define SCREEN_WIDTH 800
#define SCREEN_HEIGHT 600
#define TITLE "井字棋遊戲"

int main() {
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, TITLE);
    SetTargetFPS(60);

    while (!WindowShouldClose()) {
        
        BeginDrawing();
        ClearBackground(WHITE);
        
        EndDrawing();
    }

    CloseWindow();
    return 0;
}