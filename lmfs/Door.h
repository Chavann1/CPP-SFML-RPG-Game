#pragma once
#include "State.h"

class Door {
public:
    bool open = true;
    sf::Vector2f position;
    int destinationRoomId;
    sf::Vector2f destinationPosition;
    sf::RectangleShape shape;
    sf::RectangleShape secondaryShape;
    sf::FloatRect collisionBox;
    int type;

    Door(const sf::Vector2f& pos, float w, float h, int destId, const sf::Vector2f& destPos, int type);
};

