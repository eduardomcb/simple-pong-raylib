//
// Created by eduardo on 13/06/25.
//
#include "paddle.h"
#include "../utils/constants.h"
#include "raylib.h"

void InitPaddle(Paddle *paddle, Vector2 position) {
    paddle->position = position;
    paddle->size = (Vector2){PLAYER_WIDTH, PLAYER_HEIGHT};
    paddle->speed = PLAYER_SPEED;
    paddle->score = 0;
}

void UpdatePaddle(Paddle *paddle, int upKey, int downKey) {
    if (IsKeyDown(upKey)) {
        paddle->position.y -= paddle->speed;
    }
    if (IsKeyDown(downKey)) {
        paddle->position.y += paddle->speed;
    }

    ClampPaddle(paddle);
}

void DrawPaddle(const Paddle *paddle) {
    DrawRectangleV(paddle->position, paddle->size, RAYWHITE);
}

Rectangle GetPaddleRect(const Paddle *paddle) {
    return (Rectangle){
        paddle->position.x,
        paddle->position.y,
        paddle->size.x,
        paddle->size.y
    };
}

void ClampPaddle(Paddle *paddle) {
    if (paddle->position.y < 0) {
        paddle->position.y = 0;
    }
    if (paddle->position.y + paddle->size.y > SCREEN_HEIGHT) {
        paddle->position.y = SCREEN_HEIGHT - paddle->size.y;
    }
}