#pragma once
#include "State.h"
#include "MenuManager.h"

class MainMenuState : public State
{
public:
    // Variables
    MenuManager* manager;
    sf::RectangleShape bgShape;
    sf::Texture bgTexture;
    sf::Music music;
    sf::Font font;
    sf::SoundBuffer hoverBuffer, clickBuffer;
    std::stack<State*>& states;

    // Methods
    // Co/De -structors
    MainMenuState(sf::RenderWindow* newWin, std::map<std::string, int>* keyNew, std::stack<State*>& states);
    virtual ~MainMenuState();

    // Initialization
    void initFonts();
    void initSounds();
    void initKeys();

    // Executed every frame
    bool update(const float& delTime);
    void render(sf::RenderTarget* target);
    virtual void inputUpdate(const float& delTime);

    // Other
    void start();
    void endState();

};

