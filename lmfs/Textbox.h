#pragma once
#include "State.h"

class Textbox {
private:
    std::vector<std::string> lines;
    int currentLine = 0;
    bool visible = false;

    sf::RectangleShape box;
    sf::Text text;

public:
    Textbox(const sf::Font& font, const sf::Vector2f& size, const sf::Vector2f& position);

    void setLines(const std::vector<std::string>& newLines);
    std::string wrapText(const std::string& input, const sf::Font& font, unsigned int characterSize, float maxWidth);
    void show();
    void hide();
    void next();
    bool isVisible() const;
    bool isFinished() const;

    void update();
    void draw(sf::RenderWindow& window);
};