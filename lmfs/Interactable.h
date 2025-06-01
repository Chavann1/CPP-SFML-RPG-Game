#pragma once
#include "State.h"
#include "Player.h"
#include "Textbox.h"

class Interactable {
public:
    sf::RectangleShape shape;
    int id, state, sprite;
    Interactable(int id, int state, int sprite) : id(id), state(state), sprite(sprite) {}
    virtual void interact(Player& player, Textbox& textbox) = 0;
    virtual sf::FloatRect getBounds() const = 0;
    virtual ~Interactable() = default;
};
