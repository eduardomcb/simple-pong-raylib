//
// Created by eduardo on 13/06/25.
//

#ifndef BALL_H
#define BALL_H

#include "../utils/types.h"

void InitBall(Ball *ball);
void UpdateBall(Ball *ball, Paddle *p1, Paddle *p2);
void DrawBall(const Ball *ball);
void ResetBall(Ball *ball);
void HandleBallCollision(Ball *ball, const Paddle *paddle);

#endif //BALL_H
