#include "Npc.h"

Npc::Npc(const sf::Vector2f& pos, int id, int state, int sprite): Interactable(id, state, sprite) {
    switch (sprite) {
    case 0:
        State::loadTextureImage(texture, "npc_statue");
        shape.setSize({ 38.f, 54.f });
        shape.setTextureRect(sf::IntRect(sf::Vector2i(0, 0), sf::Vector2i(19, 27)));
        break;
    case 1:
        State::loadTextureImage(texture, "npc_man");
        shape.setSize({ 28.f, 46.f });
        shape.setTextureRect(sf::IntRect(sf::Vector2i(0, 0), sf::Vector2i(14, 23)));
        break;
    case 2:
        State::loadTextureImage(texture, "npc_woman");
        shape.setSize({ 36.f, 46.f });
        shape.setTextureRect(sf::IntRect(sf::Vector2i(0, 0), sf::Vector2i(18, 23)));
        break;
    }
    shape.setOrigin(sf::Vector2f(0.f, 0.f));
    shape.setPosition(pos);
    shape.setTexture(&texture);

}

std::vector<std::string> Npc::loadDialogueLines(const std::string& filename) {
    std::ifstream file(filename);
    std::vector<std::string> lines;

    if (!file.is_open()) {
        std::cerr << "Failed to open dialogue file: " << filename << std::endl;
        return lines;
    }

    std::string targetHeader = std::to_string(id) + "," + std::to_string(state);
    std::string line;
    bool reading = false;

    while (std::getline(file, line)) {
        // Trim whitespace
        if (line.empty()) continue;

        // Check if line matches the header format of another NPC/state
        std::istringstream iss(line);
        int curId, curState;
        char comma;
        if ((iss >> curId >> comma >> curState) && comma == ',') {
            // Start of new block
            reading = (id == curId && state == curState);
            //std::cout << id << comma << state << std::endl;
            //std::cout << reading << std::endl;
            continue;
        }

        if (reading) {
            lines.push_back(line);
        }
    }

    return lines;
}

void Npc::interact(Player& player, Textbox& textbox) {
    //if (!spokenTo) {
        dialogue = loadDialogueLines("data/dialogue.txt");
        textbox.setLines(dialogue);
        //spokenTo = true;
    //}
}

sf::FloatRect Npc::getBounds() const {
    return shape.getGlobalBounds();
}

