#include "State.h"
#include "GameState.h"

State::State(sf::RenderWindow* newWin, std::map<std::string, int>* keyNew)
{
    window = newWin;
    keyRef = keyNew;
}

State::~State()
{
}


void State::loadTextureImage(sf::Texture& texture, std::string filename) {
    if (!texture.loadFromFile("assets/" + filename + ".png")) {
        std::cerr << "Failed to load texture: " << filename << std::endl;
        return;
    }
}
