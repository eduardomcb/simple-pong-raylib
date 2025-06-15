//
// Created by eduardo on 13/06/25.
//

#ifndef GAME_H
#define GAME_H

#include "../utils/types.h"

void InitGame(GameState *game);
void UpdateGame(GameState *game);
void DrawGame(const GameState *game);
void DrawUI(const GameState *game);
void DrawCenterLine(void);
void DrawDebugInfo(const Ball *ball);
bool CheckWinCondition(const GameState *game);

// funções da contagem regressiva
void StartCountdown(GameState *game);
void UpdateCountdown(GameState *game);
void DrawCountdown(const GameState *game);

#endif //GAME_H
