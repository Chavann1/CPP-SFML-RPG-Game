#pragma once
#include "State.h"
#include "Interactable.h"

class Npc : public Interactable {
private:
    sf::Texture texture;
    std::vector<std::string> dialogue;
    bool spokenTo = false;

public:
    Npc(const sf::Vector2f& pos, int id, int state, int sprite);
    std::vector<std::string> loadDialogueLines(const std::string& filename);
    void interact(Player& player, Textbox& textbox) override;
    sf::FloatRect getBounds() const override;
};

