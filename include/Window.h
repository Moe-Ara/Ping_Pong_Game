//
// Created by Mohamad on 17/11/2024.
//

#ifndef PONG_WINDOW_H
#define PONG_WINDOW_H
#include <SFML/Graphics.hpp>
#include <memory>
#include <string>
class Window{
public:
    virtual ~Window()=default;

    static sf::RenderWindow& getInstance(const std::string& title="Pong",  int width=800,int height=600);

private:
    explicit Window(const std::string& title,int width, int height);

    Window(const Window& other)=delete;
    Window& operator=(const Window& other)=delete;
    Window(const Window&& other) noexcept=delete;
    Window& operator=(const Window&& other) noexcept=delete;
    sf::RenderWindow instance;
    static std::unique_ptr<Window> s_instance;
};
#endif //PONG_WINDOW_H
