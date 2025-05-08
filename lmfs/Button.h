#pragma once
#include "State.h"

class Button
{

    private:
        sf::RectangleShape shape;
        sf::Text *text;
        bool isHovered = false;
        sf::Sound* hoverSound;
        sf::Sound* clickSound;
        bool wasHovered = false;
        int bType;
        int bData;
        std::pair<int, int> retData;

    public:
        Button(const sf::Vector2f& position, const sf::Vector2f& size, const std::string& label, const int type, const int data, const sf::Font& font, const sf::SoundBuffer& hoverBuffer, const sf::SoundBuffer& clickBuffer);

        void setHovered(bool hovered);

        void draw(sf::RenderWindow& window);

        bool contains(sf::Vector2f point) const;

        std::pair<int, int> onClick();
};

