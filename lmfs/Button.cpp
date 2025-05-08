#include "Button.h"

Button::Button(const sf::Vector2f& position, const sf::Vector2f& size, const std::string& label, const int type, const int data, const sf::Font& font, const sf::SoundBuffer& hoverBuffer, const sf::SoundBuffer& clickBuffer): bType(type), bData(data) {
            shape.setPosition(position);
            shape.setSize(size);
            shape.setFillColor(sf::Color::Blue);
            text = new sf::Text(font);
            text->setFont(font);
            text->setString(label);
            text->setCharacterSize(24);
            text->setFillColor(sf::Color::White);
            sf::FloatRect textBounds = text->getLocalBounds();
            text->setOrigin(sf::Vector2f(textBounds.size.x / 2, textBounds.size.y / 2));
            text->setPosition(position + size / 2.f);

            hoverSound = new sf::Sound(hoverBuffer);
            clickSound = new sf::Sound(clickBuffer);
        }

void Button::setHovered(bool hovered) {
    if (hovered && !wasHovered) {
        hoverSound->play();
    }
    wasHovered = hovered;

    isHovered = hovered;
    shape.setFillColor(hovered ? sf::Color(100, 100, 255) : sf::Color::Blue);
}

void Button::draw(sf::RenderWindow& window) {
    window.draw(shape);
    window.draw(*text);
}

bool Button::contains(sf::Vector2f point) const {
    return shape.getGlobalBounds().contains(point);
}

std::pair<int, int> Button::onClick() {
    if(clickSound->getStatus() != sf::SoundSource::Status::Playing) clickSound->play();

    return std::pair<int, int>(bType, bData);
}