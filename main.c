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
#define WIN_COLOR (Color){0, 128, 0, 255}

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

Vector2 winStart = {-1, -1}, winEnd = {-1, -1};

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

    if (winStart.x != -1) DrawLineEx(winStart, winEnd, THICKNESS * 2, WIN_COLOR);
}


bool hovered(Vector2 mousePos, int i, int j) {
    Vector2 pos = drawBoardPositions[i][j];
    return (pos.x - BOX_SIZE / 2 < mousePos.x && mousePos.x < pos.x + BOX_SIZE / 2 && pos.y - BOX_SIZE / 2 < mousePos.y && mousePos.y < pos.y + BOX_SIZE / 2);
}


int checkWin() {
    if (board[0][0] && board[0][0] == board[0][1] && board[0][1] == board[0][2]) {
        winStart = drawBoardPositions[0][0];
        winEnd = drawBoardPositions[0][2];
        return board[0][0];
    }
    if (board[1][0] && board[1][0] == board[1][1] && board[1][1] == board[1][2]) {
        winStart = drawBoardPositions[1][0];
        winEnd = drawBoardPositions[1][2];
        return board[1][0];
    }
    if (board[2][0] && board[2][0] == board[2][1] && board[2][1] == board[2][2]) {
        winStart = drawBoardPositions[2][0];
        winEnd = drawBoardPositions[2][2];
        return board[2][0];
    }
    if (board[0][0] && board[0][0] == board[1][0] && board[1][0] == board[2][0]) {
        winStart = drawBoardPositions[0][0];
        winEnd = drawBoardPositions[2][0];
        return board[0][0];
    }
    if (board[0][1] && board[0][1] == board[1][1] && board[1][1] == board[2][1]) {
        winStart = drawBoardPositions[0][1];
        winEnd = drawBoardPositions[2][1];
        return board[0][1];
    }
    if (board[0][2] && board[0][2] == board[1][2] && board[1][2] == board[2][2]) {
        winStart = drawBoardPositions[0][2];
        winEnd = drawBoardPositions[2][2];
        return board[0][2];
    }
    if (board[0][0] && board[0][0] == board[1][1] && board[1][1] == board[2][2]) {
        winStart = drawBoardPositions[0][0];
        winEnd = drawBoardPositions[2][2];
        return board[0][0];
    }
    if (board[0][2] && board[0][2] == board[1][1] && board[1][1] == board[2][0]) {
        winStart = drawBoardPositions[0][2];
        winEnd = drawBoardPositions[2][0];
        return board[0][2];
    }
    return -1;
}


void GetAIMove() {

}


int main() {
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, TITLE);
    SetTargetFPS(60);

    int pause = 0;
    while (!WindowShouldClose()) {
        if (!pause && IsMouseButtonDown(MOUSE_BUTTON_LEFT)) {
            Vector2 mousePos = GetMousePosition();
            int flag = 0;
            for (int i = 0 ; i < 3 ; i ++) {
                for (int j = 0 ; j < 3 ; j ++) {
                    if (hovered(mousePos, i, j)) {
                        flag = 1;
                        if (board[i][j] == 0) {
                            board[i][j] = HUMAN;
                            if (checkWin() == HUMAN) {
                                pause = 1;
                                break;
                            }
                            GetAIMove();
                            if (checkWin() == AI) {
                                pause = 1;
                                break;
                            }
                        }
                        break;
                    }
                }
                if (flag) break;
            }
        }

        if (pause && IsKeyDown(KEY_R)) {
            pause = 0;
            for (int i = 0 ; i < 3 ; i ++) board[i][0] = board[i][1] = board[i][2] = 0;
            winStart = winEnd = (Vector2){-1, -1};
        }

        BeginDrawing();
        ClearBackground(WHITE);
        showBoard();
        EndDrawing();
    }

    CloseWindow();
    return 0;
}