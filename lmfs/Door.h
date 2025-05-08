#pragma once
#include "State.h"

class Door {
public:
    // Variables
    sf::Vector2f position;
    sf::Vector2f destinationPosition;
    sf::RectangleShape shape;
    sf::RectangleShape secondaryShape;
    sf::FloatRect collisionBox;
    int type, destinationRoomId;
    bool open = true;

    // Methods
    Door(const sf::Vector2f& pos, float w, float h, int destId, const sf::Vector2f& destPos, int type);
};

