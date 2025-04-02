#pragma once
#include <SFML/Graphics.hpp>

class Button
{
    sf::Font *font;
    //sf::Text text(font, "");
    sf::RectangleShape *shape;

    Button(sf::Font bfont, unsigned int width, unsigned int height, std::string text);
    ~Button();
};

