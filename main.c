#include "raylib.h"
#define SCREEN_WIDTH 800
#define SCREEN_HEIGHT 600
#define TITLE "井字棋遊戲"
#define SCREEN_CENTER (Vector2){SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2}
#define BOX_SIZE 100
#define THICKNESS 5
#define CIRCLE_OUTSIDE_RADIUS 45
#define CIRCLE_INSIDE_RADIUS (CIRCLE_OUTSIDE_RADIUS - THICKNESS)
#define CROSS_SIZE 90
#define BACKGROUND_COLOR (Color){255, 255, 255, 255}
#define CIRCLE_COLOR (Color){255, 0, 0, 255}
#define CROSS_COLOR (Color){0, 0, 255, 255}


void drawCircleAt(Vector2 center) {
    DrawCircleV(center, CIRCLE_OUTSIDE_RADIUS, CIRCLE_COLOR);
    DrawCircleV(center, CIRCLE_INSIDE_RADIUS, BACKGROUND_COLOR);
}


void drawCrossAt(Vector2 center) {
    DrawLineEx(
        (Vector2){center.x - CROSS_SIZE / 2, center.y - CROSS_SIZE / 2},
        (Vector2){center.x + CROSS_SIZE / 2, center.y + CROSS_SIZE / 2},
        THICKNESS,
        CROSS_COLOR
    );
    DrawLineEx(
        (Vector2){center.x + CROSS_SIZE / 2, center.y - CROSS_SIZE / 2},
        (Vector2){center.x - CROSS_SIZE / 2, center.y + CROSS_SIZE / 2},
        THICKNESS,
        CROSS_COLOR
    );
}


int main() {
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, TITLE);
    SetTargetFPS(60);

    while (!WindowShouldClose()) {
        
        BeginDrawing();
        ClearBackground(WHITE);
        drawCircleAt(SCREEN_CENTER);
        EndDrawing();
    }

    CloseWindow();
    return 0;
}