//
// Created by eduardo on 13/06/25.
//
#include "ball.h"

#include "paddle.h"
#include "particles_system.h"
#include "../utils/constants.h"
#include "raylib.h"
#include "../audio/audio_manager.h"

void InitBall(Ball *ball) {
    ResetBall(ball);
}

void UpdateBall(Ball *ball, Paddle *p1, Paddle *p2) {
    // Movimento da bola
    ball->position.x += ball->velocity.x;
    ball->position.y += ball->velocity.y;

    // Colisão da parte de cima e a de baixo
    if (ball->position.y <= ball->radius ||
        ball->position.y >= SCREEN_HEIGHT - ball->radius) {
        ball->velocity.y *= -1;
        ActivateParticles(ball->position,2.0f);
    }

    // Colisão dos paddles(players)
    Rectangle p1Rect = GetPaddleRect(p1);
    Rectangle p2Rect = GetPaddleRect(p2);

    if (CheckCollisionCircleRec(ball->position, ball->radius, p1Rect)) {
        PlayAudio(AUDIO_PADDLE_HIT);
        HandleBallCollision(ball, p1);
        ActivateParticles(ball->position,2.0f);
    }

    if (CheckCollisionCircleRec(ball->position, ball->radius, p2Rect)) {
        PlayAudio(AUDIO_PADDLE_HIT);
        HandleBallCollision(ball, p2);
        ActivateParticles(ball->position,2.0f);
    }

    // Tratamento do scores
    if (ball->position.x <= 0) {
        p2->score++;
        TraceLog(LOG_INFO,"Player 2 ganhou um ponto! Score: %d\n", p2->score);
        ResetBall(ball);
    }

    if (ball->position.x >= SCREEN_WIDTH) {
        p1->score++;
        TraceLog(LOG_INFO,"Player 1 ganhou um ponto! Score: %d\n", p1->score);
        ResetBall(ball);
    }
}

void DrawBall(const Ball *ball) {
    DrawCircleV(ball->position, ball->radius, RAYWHITE);
}

void ResetBall(Ball *ball) {
    ball->position = (Vector2){SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2};
    ball->radius = BALL_RADIUS;

    // direção randomica
    int dirX = (GetRandomValue(0, 1) == 0) ? -1 : 1;
    int dirY = (GetRandomValue(0, 1) == 0) ? -1 : 1;

    ball->velocity = (Vector2){
        BALL_INITIAL_SPEED * dirX,
        BALL_INITIAL_SPEED * dirY * GetRandomValue(1, BALL_SPEED_VARIATION)
    };
}

void HandleBallCollision(Ball *ball, const Paddle *paddle) {
    ball->velocity.x *= -1;

    float hitPoint = (ball->position.y - paddle->position.y) / paddle->size.y;
    ball->velocity.y = (hitPoint - 0.5f) * 10.0f;
    TraceLog(LOG_DEBUG,"velocidade: %lf\n", ball->velocity.y);
}
