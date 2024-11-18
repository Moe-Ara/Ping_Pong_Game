#include "GameManager.h"

GameManager::GameManager()  : window(Window::getInstance("Ping Pong Game",800,600)), leftScore(0), rightScore(0), playerPaddle(10.f,100.f,Window::getInstance().getSize().y/2,50.f),
                                                      opponentPaddle(10.f, 100.f, Window::getInstance().getSize().y/2, Window::getInstance().getSize().x-50, true){
    if (!font.loadFromFile("resources/fonts/font.ttf")) {
        throw std::exception("ERROR: Couldn't load game font ");
    }

    leftScoreText.setFont(font);
    leftScoreText.setCharacterSize(30);
    leftScoreText.setFillColor(sf::Color::White);
    leftScoreText.setPosition(100.f, 10.f);

    rightScoreText.setFont(font);
    rightScoreText.setCharacterSize(30);
    rightScoreText.setFillColor(sf::Color::White);
    rightScoreText.setPosition(window.getSize().x - 150.f, 10.f);
}

void GameManager::drawDottedLine(sf::RenderWindow &window, float startY, float endY, float x, float dotLength,
                                 float gapLength) {
    sf::RectangleShape dot(sf::Vector2f(dotLength, dotLength));
    dot.setFillColor(sf::Color::White);

    float currentY = startY;
    while (currentY < endY) {
        dot.setPosition(x - dotLength / 2, currentY);
        window.draw(dot);
        currentY += dotLength + gapLength;
    }

}

void GameManager::startGame() {
    ball.setBallOutOfBoundsCallback([this](int player){this->scoreCallback(player);});
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        float deltaTime = clock.restart().asSeconds();

        ball.update(deltaTime);
        playerPaddle.update(deltaTime);
        opponentPaddle.update(deltaTime, ball.getPosition());

        ball.checkCollisionWithPaddle(playerPaddle.getShape());
        ball.checkCollisionWithPaddle(opponentPaddle.getShape());

        if (ball.getPosition().x <= 0) {
            scoreCallback(1);  // Player 1 (left) scored
        } else if (ball.getPosition().x >= window.getSize().x) {
            scoreCallback(2);  // Player 2 (right) scored
        }

        window.clear();
        drawDottedLine(window, 0.f, window.getSize().y, window.getSize().x / 2, 5.f, 10.f); // Dotted line
        ball.draw();
        playerPaddle.draw();
        opponentPaddle.draw();
        drawScores();

        window.display();
    }

}

void GameManager::drawScores() {
    leftScoreText.setString(std::to_string(leftScore));
    rightScoreText.setString(std::to_string(rightScore));

    window.draw(leftScoreText);
    window.draw(rightScoreText);
}

void GameManager::scoreCallback(int player) {
    if (player == 1) {
        leftScore++;
    } else if (player == -1) {
        rightScore++;
    }
}
