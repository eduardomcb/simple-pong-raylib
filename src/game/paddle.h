//
// Created by eduardo on 13/06/25.
//

#ifndef PADDLE_H
#define PADDLE_H

#include "../utils/types.h"

void InitPaddle(Paddle *paddle, Vector2 position);
void UpdatePaddle(Paddle *paddle, int upKey, int downKey);
void DrawPaddle(const Paddle *paddle);
Rectangle GetPaddleRect(const Paddle *paddle);
void ClampPaddle(Paddle *paddle);

#endif //PADDLE_H
