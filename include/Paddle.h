#ifndef PONG_PADDLE_H
#define PONG_PADDLE_H


#include <SFML/Graphics.hpp>

class Paddle {
public:
    Paddle(float width, float height, float speed, float xPos);

    virtual void update(float deltaTime);

    void draw();

    sf::FloatRect getBounds() const {return shape.getGlobalBounds();}
    sf::Vector2f getPosition()const {return shape.getPosition();}

    void moveUp(float deltaTime);

    void moveDown(float deltaTime);

    sf::RectangleShape &getShape();

protected:
    sf::RectangleShape shape;
    float speed;

};


#endif //PONG_PADDLE_H
