#pragma once
#include "State.h"
#include "MenuManager.h"

class MainMenuState : public State
{
public:
    sf::Font font;
    sf::SoundBuffer hoverBuffer, clickBuffer;
    //Menu* menu;
    std::stack<State*>& states;
    MainMenuState(sf::RenderWindow* newWin, std::map<std::string, int>* keyNew, std::stack<State*>& states);
    virtual ~MainMenuState();
    void initFonts();
    void initSounds();
    bool update(const float& delTime);
    void render(sf::RenderTarget* target);
    void start();
    virtual void inputUpdate(const float& delTime);
    void endState();
    void initKeys();
    MenuManager *manager;
};

