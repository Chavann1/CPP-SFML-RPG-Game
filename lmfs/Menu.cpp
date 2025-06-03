#include "Menu.h"

void Menu::addButton(const Button& button) {
    buttons.push_back(button);
}

std::pair<int, int> Menu::update(sf::RenderWindow& window) {
    //sf::Vector2f mousePos = (sf::Vector2f)sf::Mouse::getPosition(window);
    sf::Vector2i pixelPos = sf::Mouse::getPosition(window);
    sf::Vector2f mousePos = window.mapPixelToCoords(pixelPos);

    for (auto& button : buttons) {
        bool hovering = button.contains(mousePos);
        button.setHovered(hovering);

        if (hovering && sf::Mouse::isButtonPressed(sf::Mouse::Button::Left)) {
            return button.onClick();
        }
    }

    return std::pair<int, int>(-1, -1);
}

void Menu::draw(sf::RenderWindow& window) {
    for (auto& button : buttons) {
        button.draw(window);
    }
}
