#include "Paddle.h"
#include "Window.h"

Paddle::Paddle(float width, float height, float speed, float xPos)
        : speed(speed) {
    shape.setSize(sf::Vector2f(width, height));
    shape.setFillColor(sf::Color::White);
    shape.setOrigin(width / 2.f, height / 2.f); // So the paddle moves from its center
    shape.setPosition(xPos, Window::getInstance().getSize().y/2); // Initial position (left side of the screen)
}

void Paddle::update(float deltaTime) {
    // Use input to move paddle
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
        moveUp(deltaTime);
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
        moveDown(deltaTime);
    }

    // Ensure paddle stays within the window bounds (assumes window height = 600)
    if (shape.getPosition().y < shape.getSize().y / 2.f) {
        shape.setPosition(shape.getPosition().x, shape.getSize().y / 2.f);
    }
    if (shape.getPosition().y > Window::getInstance().getSize().y - shape.getSize().y / 2.f) {
        shape.setPosition(shape.getPosition().x, Window::getInstance().getSize().y - shape.getSize().y / 2.f);
    }
}

void Paddle::moveUp(float deltaTime) {
    shape.move(0.f, -speed * deltaTime);  // Move paddle up
}

void Paddle::moveDown(float deltaTime) {
    shape.move(0.f, speed * deltaTime);  // Move paddle down
}

void Paddle::draw() {
    Window::getInstance().draw(shape);
}

sf::RectangleShape &Paddle::getShape() {
    return shape;
}
