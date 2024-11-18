#ifndef PONG_GAMEMANAGER_H
#define PONG_GAMEMANAGER_H


#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include "Window.h"
#include "Ball.h"
#include "Paddle.h"
#include "OpponentPaddle.h"

class GameManager {
public:
    GameManager();
    virtual ~GameManager()=default;
    void drawDottedLine(sf::RenderWindow &window, float startY, float endY, float x, float dotLength, float gapLength);
    void startGame();
    void drawScores();
    void scoreCallback(int player);
private:
    int leftScore,rightScore;
    sf::RenderWindow& window;
    Ball ball;
    sf::Clock clock;
    Paddle playerPaddle;
    OpponentPaddle opponentPaddle;
    sf::Text leftScoreText, rightScoreText;
    sf::Font font;
};


#endif //PONG_GAMEMANAGER_H
