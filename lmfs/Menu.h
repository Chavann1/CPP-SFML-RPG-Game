#pragma once
#include "State.h"
#include "Button.h"

class Menu {
private:
    // Button vector
    std::vector<Button> buttons;

public:
    // Methods
    void addButton(const Button& button);
    std::pair<int, int> update(sf::RenderWindow& window);
    void draw(sf::RenderWindow& window);
};
