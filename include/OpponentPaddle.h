#ifndef PONG_OPPONENTPADDLE_H
#define PONG_OPPONENTPADDLE_H
#include "Paddle.h"

class OpponentPaddle: public Paddle {
public:
    OpponentPaddle(float width, float height, float posX, float , bool IsCPU);
void update(float deltaTime)override;
void update(float deltaTime, sf::Vector2f ballPosition);
private:
    bool IsCPU;
};


#endif //PONG_OPPONENTPADDLE_H
