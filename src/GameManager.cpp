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


    UIText.setFont(font);
    UIText.setCharacterSize(20);
    UIText.setFillColor(sf::Color::White);
    UIText.setPosition(10.f, window.getSize().y-20);
    // Set Up Audio
    AudioManager::getInstance().playBackgroundMusic("resources/sounds/bg/bg_music2.wav");
    AudioManager::getInstance().setBackgroundMusicVolume(50);
    AudioManager::getInstance().loadSound("bounce", "resources/sounds/bounce.wav");
    AudioManager::getInstance().loadSound("score", "resources/sounds/score.wav");
    AudioManager::getInstance().start();

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
    static bool isKeyReleased = true;
    while (window.isOpen()) {
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::M)) {
            if (isKeyReleased) {  // Only toggle on initial key press
                if (AudioManager::getInstance().IsBackgroundMusicPlaying()) {
                    AudioManager::getInstance().stopBackgroundMusic();
                } else {
                    AudioManager::getInstance().playBackgroundMusic("resources/sounds/bg/bg_music2.wav");
                }
                isKeyReleased = false;  // Mark key as pressed
            }
        } else {
            isKeyReleased = true;  // Reset the state when the key is released
        }
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
        drawUI();

        window.display();
    }

}

void GameManager::drawUI() {
    leftScoreText.setString(std::to_string(leftScore));
    rightScoreText.setString(std::to_string(rightScore));
    UIText.setString("Press M to mute Background Music");
    window.draw(leftScoreText);
    window.draw(rightScoreText);
    window.draw(UIText);

}

void GameManager::scoreCallback(int player) {
    if (player == 1) {
        leftScore++;
    } else if (player == -1) {
        rightScore++;
    }
    AudioManager::getInstance().enqueueMessage(AudioMessage(AudioAction::PLAY_SOUND,"score",50.f));

}
