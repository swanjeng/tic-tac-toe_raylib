#include "raylib.h"
#define SCREEN_WIDTH 800
#define SCREEN_HEIGHT 600
#define TITLE "井字棋遊戲"
#define SCREEN_CENTER ((Vector2){SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2})

#define BOX_SIZE 150
#define THICKNESS 5
#define CIRCLE_OUTSIDE_RADIUS 60
#define CIRCLE_INSIDE_RADIUS (CIRCLE_OUTSIDE_RADIUS - THICKNESS)
#define CROSS_SIZE 120

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


bool hovered(Vector2 mousePos, int i, int j) {
    Vector2 pos = drawBoardPositions[i][j];
    return (pos.x - BOX_SIZE / 2 < mousePos.x && mousePos.x < pos.x + BOX_SIZE / 2 && pos.y - BOX_SIZE / 2 < mousePos.y && mousePos.y < pos.y + BOX_SIZE / 2);
}


bool checkWin(int player) {

}


int main() {
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, TITLE);
    SetTargetFPS(60);

    while (!WindowShouldClose()) {
        if (IsMouseButtonDown(MOUSE_BUTTON_LEFT)) {
            Vector2 mousePos = GetMousePosition();
            int flag = 0;
            for (int i = 0 ; i < 3 ; i ++) {
                for (int j = 0 ; j < 3 ; j ++) {
                    if (hovered(mousePos, i, j)) {
                        flag = 1;
                        if (board[i][j] == 0) board[i][j] = HUMAN;
                        break;
                    }
                }
                if (flag) break;
            }
        }

        BeginDrawing();
        ClearBackground(WHITE);
        showBoard();
        EndDrawing();
    }

    CloseWindow();
    return 0;
}