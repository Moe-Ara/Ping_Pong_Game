#include "Window.h"

std::unique_ptr<Window> Window::s_instance = nullptr;

sf::RenderWindow &Window::getInstance(const std::string &title, int width, int height) {
    if (!s_instance) {
        s_instance = std::unique_ptr<Window>(new Window(title, width, height));
    }
    return s_instance->instance;
}

Window::Window(const std::string &title, int width, int height) : instance(sf::VideoMode(width, height), title,
                                                                           sf::Style::Default) {

}
