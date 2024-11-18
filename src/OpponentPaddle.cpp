#include "OpponentPaddle.h"
#include "Window.h"

void OpponentPaddle::update(float deltaTime, sf::Vector2f ballPosition){
    if(!IsCPU){
        update(deltaTime);
        return;
    }
    float randomness = static_cast<float>(std::rand() % 100) / 100.f;
    float aiError = (randomness - 0.5f) * 20.f;

    if (shape.getPosition().y + shape.getSize().y / 2 < ballPosition.y+aiError) {
        moveDown(deltaTime);
    } else if (shape.getPosition().y + shape.getSize().y / 2 > ballPosition.y+aiError) {
        moveUp(deltaTime);
    }
    if (shape.getPosition().y < shape.getSize().y / 2.f) {
        shape.setPosition(shape.getPosition().x, shape.getSize().y / 2.f);
    }
    if (shape.getPosition().y > Window::getInstance().getSize().y - shape.getSize().y / 2.f) {
        shape.setPosition(shape.getPosition().x, Window::getInstance().getSize().y - shape.getSize().y / 2.f);
    }
}

OpponentPaddle::OpponentPaddle(float width, float height, float posX, float posY, bool IsCPU) : Paddle(width, height, posX, posY), IsCPU(IsCPU) {
    std::srand(static_cast<unsigned int>(std::time(nullptr)));
}

void OpponentPaddle::update(float deltaTime) {
    if(IsCPU){
        throw std::exception("ERROR: You are using 'Update(deltaTime)' with CPU flag. Try calling 'Update(deltaTime, BallPosition)'");
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
        moveUp(deltaTime);
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
        moveDown(deltaTime);
    }

    if (shape.getPosition().y < shape.getSize().y / 2.f) {
        shape.setPosition(shape.getPosition().x, shape.getSize().y / 2.f);
    }
    if (shape.getPosition().y > Window::getInstance().getSize().y - shape.getSize().y / 2.f) {
        shape.setPosition(shape.getPosition().x, Window::getInstance().getSize().y - shape.getSize().y / 2.f);
    }
}
