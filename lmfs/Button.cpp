#include "Button.h"

Button::Button(sf::Font bfont, unsigned int width, unsigned int height, std::string text){
    font = &bfont;
    shape->setSize(sf::Vector2f(80, 40));
    shape->setOrigin(shape->getGeometricCenter());
    shape->setPosition({ width / 2.0f, height / 2.0f });
    shape->setFillColor(sf::Color::Green);
    //text.setFont(font);
}

Button::~Button() {
    delete this->font;
    delete this->shape;

}