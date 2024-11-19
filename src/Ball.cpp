#include "Ball.h"
#include "Window.h"

void Ball::draw() {
    Window::getInstance().draw(shape);
}

Ball::Ball(float radius, float speed) : speed(speed*Window::getInstance().getSize().x/500), velocity(getRandomVelocity()), originalSpeed(speed*Window::getInstance().getSize().x/500) {
    shape.setRadius(radius);
    shape.setFillColor(sf::Color::White);
    shape.setOrigin(radius, radius);
    reset();

}

void Ball::update(float deltaTime) {
    shape.move(speed * velocity * deltaTime);
    if (shape.getPosition().y - shape.getRadius() <= 0 ||
        shape.getPosition().y + shape.getRadius() >= Window::getInstance().getSize().y) {
        velocity.y = -velocity.y;
        AudioManager::getInstance().enqueueMessage(AudioMessage(AudioAction::PLAY_SOUND,"bounce",100.f));

    }
    if (shape.getPosition().x - shape.getRadius() <= 0) {
        if (onBallOutOfBounds) {
            onBallOutOfBounds(-1);
        }
        reset();
    }
    if (shape.getPosition().x + shape.getRadius() >= Window::getInstance().getSize().x) {
        onBallOutOfBounds(1);
        reset();
    }
    const float maxVelocityY = 1.5f;
    if (std::abs(velocity.y) > maxVelocityY) {
        velocity.y = maxVelocityY * (velocity.y < 0 ? -1 : 1);
    }

}

void Ball::reset() {
    shape.setPosition(Window::getInstance().getSize().x / 2, Window::getInstance().getSize().y / 2);
    velocity = sf::Vector2f(getRandomVelocity());
    this->speed = originalSpeed;
}

sf::Vector2f Ball::getPosition() {
    return shape.getPosition();
}

void Ball::checkCollisionWithPaddle(sf::RectangleShape &paddleBounds) {
    if (shape.getGlobalBounds().intersects(paddleBounds.getGlobalBounds())) {
        velocity.x = -velocity.x;

        float paddleCenter = paddleBounds.getPosition().y + paddleBounds.getSize().y / 2;
        float ballCenter = shape.getPosition().y;
        float diff = ballCenter - paddleCenter;


        velocity.y += diff * 0.006f;
        if (speed <= 1000) {
            speed += 5;
        }
        AudioManager::getInstance().enqueueMessage(AudioMessage(AudioAction::PLAY_SOUND,"bounce",100.f));
    }
}

void Ball::setBallOutOfBoundsCallback(Ball::BallOutOfBoundsCallback callback) {
    onBallOutOfBounds = callback;


}
sf::Vector2f Ball::getRandomVelocity() {
    std::random_device rd;
    std::mt19937 gen(rd());

    std::uniform_real_distribution<float> distX(0.1f, 0.3f);  // Random horizontal speed between 0.1 and 0.3
    std::uniform_real_distribution<float> distY(0.1f, 0.3f);  // Random vertical speed between 0.1 and 0.3

    float velocityX = distX(gen);
    float velocityY = distY(gen);

    if (std::rand() % 2 == 0) {
        velocityX = -velocityX;
    }
    if (std::rand() % 2 == 0) {
        velocityY = -velocityY;
    }

    return sf::Vector2f(velocityX, velocityY);
}