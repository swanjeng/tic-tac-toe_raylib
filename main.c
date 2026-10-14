#include "raylib.h"
#define SCREEN_WIDTH 800
#define SCREEN_HEIGHT 600
#define TITLE "井字棋遊戲"
#define SCREEN_CENTER ((Vector2){SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2})

#define BOX_SIZE 100
#define THICKNESS 5
#define CIRCLE_OUTSIDE_RADIUS 45
#define CIRCLE_INSIDE_RADIUS (CIRCLE_OUTSIDE_RADIUS - THICKNESS)
#define CROSS_SIZE 90

#define BACKGROUND_COLOR (Color){255, 255, 255, 255}
#define LINE_COLOR (Color){0, 0, 0, 255}
#define CIRCLE_COLOR (Color){255, 0, 0, 255}
#define CROSS_COLOR (Color){0, 0, 255, 255}

#define HUMAN 1
#define AI 2

int board[3][3] = {{0, 0, 0},
                   {0, 0, 0},
                   {0, 0, 0}};

Vector2 drawBoardPositions[3][3] = {
    {{SCREEN_WIDTH / 2 - BOX_SIZE, SCREEN_HEIGHT / 2 - BOX_SIZE}, {SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2 - BOX_SIZE}, {SCREEN_WIDTH / 2 + BOX_SIZE, SCREEN_HEIGHT / 2 - BOX_SIZE}},
    {{SCREEN_WIDTH / 2 - BOX_SIZE, SCREEN_HEIGHT / 2}, {SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2}, {SCREEN_WIDTH / 2 + BOX_SIZE, SCREEN_HEIGHT / 2}},
    {{SCREEN_WIDTH / 2 - BOX_SIZE, SCREEN_HEIGHT / 2 + BOX_SIZE}, {SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2 + BOX_SIZE}, {SCREEN_WIDTH / 2 + BOX_SIZE, SCREEN_HEIGHT / 2 + BOX_SIZE}}
};

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


void showBoard() {
    DrawLine(SCREEN_WIDTH / 2 - BOX_SIZE * 3 / 2,
             SCREEN_HEIGHT / 2 - BOX_SIZE / 2,
             SCREEN_WIDTH / 2 + BOX_SIZE * 3 / 2,
             SCREEN_HEIGHT / 2 - BOX_SIZE / 2,
             LINE_COLOR
    );
    DrawLine(SCREEN_WIDTH / 2 - BOX_SIZE * 3 / 2,
             SCREEN_HEIGHT / 2 + BOX_SIZE / 2,
             SCREEN_WIDTH / 2 + BOX_SIZE * 3 / 2,
             SCREEN_HEIGHT / 2 + BOX_SIZE / 2,
             LINE_COLOR
    );
    DrawLine(SCREEN_WIDTH / 2 - BOX_SIZE / 2,
             SCREEN_HEIGHT / 2 - BOX_SIZE * 3 / 2,
             SCREEN_WIDTH / 2 - BOX_SIZE / 2,
             SCREEN_HEIGHT / 2 + BOX_SIZE * 3 / 2,
             LINE_COLOR
    );
    DrawLine(SCREEN_WIDTH / 2 + BOX_SIZE / 2,
             SCREEN_HEIGHT / 2 - BOX_SIZE * 3 / 2,
             SCREEN_WIDTH / 2 + BOX_SIZE / 2,
             SCREEN_HEIGHT / 2 + BOX_SIZE * 3 / 2,
             LINE_COLOR
    );

    for (int i = 0 ; i < 3 ; i ++) {
        for (int j = 0 ; j < 3 ; j ++) {
            Vector2 pos = drawBoardPositions[i][j];
            if (board[i][j] == HUMAN) drawCrossAt(pos);
            else if (board[i][j] == AI) drawCircleAt(pos);
        }
    }
}


int main() {
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, TITLE);
    SetTargetFPS(60);

    while (!WindowShouldClose()) {
        
        BeginDrawing();
        ClearBackground(WHITE);
        showBoard();
        EndDrawing();
    }

    CloseWindow();
    return 0;
}