#ifndef PONG_BALL_H
#define PONG_BALL_H


#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/CircleShape.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <functional>
#include <iostream>
#include <random>
class Ball {
public:
    using BallOutOfBoundsCallback = std::function<void(int)>;
    void setBallOutOfBoundsCallback(BallOutOfBoundsCallback callback);
    Ball(float radius = 10.0f, float speed = 400.f);
    virtual ~Ball()=default;
    void update(float deltaTime);
    void draw();
    void reset();
    sf::Vector2f velocity;
    sf::Vector2f getPosition();
    void checkCollisionWithPaddle(sf::RectangleShape &paddleBounds);

private:
    sf::CircleShape shape;
    float speed;
    float originalSpeed;
    BallOutOfBoundsCallback onBallOutOfBounds;

private:
    Ball(const Ball& other)=default;
    Ball& operator=(const Ball& other)=delete;
    Ball(const Ball&& other)=delete;
    Ball& operator=(const Ball&& other)=delete;

    sf::Vector2f getRandomVelocity();
};


#endif //PONG_BALL_H
