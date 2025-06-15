//
// Created by eduardo on 13/06/25.
//
#include "game.h"
#include "paddle.h"
#include "ball.h"
#include "particles_system.h"
#include "../utils/constants.h"
#include "raylib.h"

void InitGame(GameState *game) {
    // Inicializar paddles
    Vector2 p1Pos = {20, SCREEN_HEIGHT/2 - PLAYER_HEIGHT/2};
    Vector2 p2Pos = {SCREEN_WIDTH - 40, SCREEN_HEIGHT/2 - PLAYER_HEIGHT/2};

    InitPaddle(&game->player1, p1Pos);
    InitPaddle(&game->player2, p2Pos);

    // Inicializar bola
    InitBall(&game->ball);

    // Inicializar estado do jogo
    game->currentScreen = GAME_MENU;
    game->winner = 0;

    // Inicializar contagem regressiva
    game->countdownTimer = 0.0f;
    game->countdownNumber = COUNTDOWN_START;
    game->countdownActive = false;
}

void UpdateGame(GameState *game) {
    switch (game->currentScreen) {
        case GAME_MENU:
            if (IsKeyPressed(KEY_SPACE)) {
                StartCountdown(game);
            }
            break;

        case GAME_COUNTDOWN:
            UpdateCountdown(game);
            break;

        case GAME_PLAYING:
            if (IsKeyPressed(KEY_P)) {
                game->currentScreen = GAME_PAUSED;
            }

            // Atualizar particulas
            UpdateParticles();

            // Atualizar paddles
            UpdatePaddle(&game->player1, KEY_W, KEY_S);
            UpdatePaddle(&game->player2, KEY_UP, KEY_DOWN);

            // Atualizar bola
            UpdateBall(&game->ball, &game->player1, &game->player2);

            // Checar se alguem venceu
            if (CheckWinCondition(game)) {
                game->winner = (game->player1.score >= WINNING_SCORE) ? 1 : 2;
                game->currentScreen = GAME_OVER;
            }
            break;

        case GAME_PAUSED:
            if (IsKeyPressed(KEY_P)) {
                game->currentScreen = GAME_PLAYING;
            }
            break;

        case GAME_OVER:
            if (IsKeyPressed(KEY_R)) {
                InitGame(game);  // Reiniciando o jogo
            }
            break;
    }
}

void DrawGame(const GameState *game) {
    BeginDrawing();
    ClearBackground(DARKGRAY);

    // Desenhando elementos do jogo
    DrawCenterLine();
    DrawUI(game);
    DrawPaddle(&game->player1);
    DrawPaddle(&game->player2);
    DrawBall(&game->ball);
    DrawParticles();

    // Desenhando overlays da tela
    switch (game->currentScreen) {
        case GAME_MENU:
            // overlay semi transparente
            DrawRectangle(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, (Color){0, 0, 0, 128});
            DrawText("SIMPLE PONG",
                    SCREEN_WIDTH/2 - 120, SCREEN_HEIGHT/2 - 60, 40, RAYWHITE);
            DrawText("Press SPACE to start",
                    SCREEN_WIDTH/2 - 100, SCREEN_HEIGHT/2, 20, RAYWHITE);
            DrawText("Player 1: W/S    Player 2: UP/DOWN",
                    SCREEN_WIDTH/2 - 140, SCREEN_HEIGHT/2 + 40, 16, LIGHTGRAY);
            break;

        case GAME_COUNTDOWN:
            DrawCountdown(game);
            break;

        case GAME_PAUSED:
            // overlay semi transparente
            DrawRectangle(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, (Color){0, 0, 0, 128});
            DrawText("PAUSED",
                    SCREEN_WIDTH/2 - 60, SCREEN_HEIGHT/2 - 20, 30, RAYWHITE);
            DrawText("Press P to continue",
                    SCREEN_WIDTH/2 - 80, SCREEN_HEIGHT/2 + 20, 16, LIGHTGRAY);
            break;

        case GAME_OVER:
            // overlay semi transparente
            DrawRectangle(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, (Color){0, 0, 0, 128});
            DrawText(TextFormat("PLAYER %d WINS!", game->winner),
                    SCREEN_WIDTH/2 - 100, SCREEN_HEIGHT/2 - 20, 30, RAYWHITE);
            DrawText("Press R to restart",
                    SCREEN_WIDTH/2 - 70, SCREEN_HEIGHT/2 + 20, 16, LIGHTGRAY);
            break;

        case GAME_PLAYING:
            // Sem o overlay, apenas o jogo mesmo
            break;
    }

    // Debug info na tela
    if (IsKeyDown(KEY_D)) {
        DrawDebugInfo(&game->ball);
    }

    EndDrawing();
}

void DrawUI(const GameState *game) {
    // Desenhar scores, a pontuação dos jogadores
    DrawText(TextFormat("%d", game->player1.score),
            SCREEN_WIDTH/2 - 30, 20, 26, RAYWHITE);
    DrawText(TextFormat("%d", game->player2.score),
            SCREEN_WIDTH/2 + 15, 20, 26, RAYWHITE);
}

void DrawCenterLine(void) {
    int centerX = SCREEN_WIDTH / 2;
    for (int y = 0; y < SCREEN_HEIGHT; y += DASH_LENGTH + GAP_LENGTH) {
        DrawLineEx(
            (Vector2){centerX, y},
            (Vector2){centerX, y + DASH_LENGTH},
            CENTER_LINE_THICKNESS,
            RAYWHITE
        );
    }
}

void DrawDebugInfo(const Ball *ball) {
    DrawFPS(10, 10);
    DrawText(TextFormat("Ball: X=%.2f, Y=%.2f", ball->position.x, ball->position.y),
            10, 30, 18, RAYWHITE);
    DrawText(TextFormat("Velocity: X=%.2f, Y=%.2f", ball->velocity.x, ball->velocity.y),
            10, 50, 18, RAYWHITE);
}

bool CheckWinCondition(const GameState *game) {
    return (game->player1.score >= WINNING_SCORE ||
            game->player2.score >= WINNING_SCORE);
}

// Implementações de funções da contagem regressiva do jogo
void StartCountdown(GameState *game) {
    game->currentScreen = GAME_COUNTDOWN;
    game->countdownTimer = COUNTDOWN_DURATION;
    game->countdownNumber = COUNTDOWN_START;
    game->countdownActive = true;

    // Resetando posição da bola, mas não deixando ela movimentar
    ResetBall(&game->ball);
    game->ball.velocity = (Vector2){0, 0}; // Parar movimento da bola durante contagem regressiva
}

void UpdateCountdown(GameState *game) {
    if (!game->countdownActive) return;

    game->countdownTimer -= GetFrameTime();

    if (game->countdownTimer <= 0.0f) {
        game->countdownNumber--;

        if (game->countdownNumber <= 0) {
            // Contagem regressiva finalizada e jogo iniciado
            game->currentScreen = GAME_PLAYING;
            game->countdownActive = false;

            // Inciar movimento da bola
            ResetBall(&game->ball);
        } else {
            // Continuar contagem regressiva
            game->countdownTimer = COUNTDOWN_DURATION;
        }
    }
}

void DrawCountdown(const GameState *game) {
    if (!game->countdownActive) return;

    // Um overlay semi transparente
    DrawRectangle(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, (Color){0, 0, 0, 128});

    // Calcular efeito de escala com base no temporizador
    float scale = 1.0f + (COUNTDOWN_DURATION - game->countdownTimer) * 0.5f;
    int fontSize = (int)(80 * scale);

    // Calcular alfa para efeito de fade
    float alpha = game->countdownTimer / COUNTDOWN_DURATION;
    Color textColor = (Color){255, 255, 255, (unsigned char)(255 * alpha)};

    if (game->countdownNumber > 0) {
        const char* numberText = TextFormat("%d", game->countdownNumber);
        int textWidth = MeasureText(numberText, fontSize);

        DrawText(numberText,
                SCREEN_WIDTH/2 - textWidth/2,
                SCREEN_HEIGHT/2 - fontSize/2,
                fontSize,
                textColor);
    }

    DrawText("GET READY!",
            SCREEN_WIDTH/2 - 60,
            SCREEN_HEIGHT/2 - 120,
            20,
            RAYWHITE);
}