//
// Created by eduardo on 13/06/25.
//

#ifndef TYPES_H
#define TYPES_H
#include "raylib.h"

typedef struct {
    Vector2 position;
    Vector2 size;
    float speed;
    int score;
} Paddle;

typedef struct {
    Vector2 position;
    float radius;
    Vector2 velocity;
} Ball;

typedef struct {
    Vector2 position;
    Vector2 velocity;
    float life;
    Color color;
} Particle;

//Telas do jogo
typedef enum {
    GAME_MENU,
    GAME_COUNTDOWN,
    GAME_PLAYING,
    GAME_PAUSED,
    GAME_OVER
} GameScreens;

typedef struct {
    Paddle player1;
    Paddle player2;
    Ball ball;
    GameScreens currentScreen;
    int winner;

    // Sistema de contagem regressivaa
    float countdownTimer;
    int countdownNumber;
    bool countdownActive;

} GameState;

#endif //TYPES_H
