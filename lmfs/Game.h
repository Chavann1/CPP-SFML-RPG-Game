#pragma once

#include "State.h"
#include "GameState.h"
#include "MainMenuState.h"

namespace fs = std::filesystem;

class Game
{
private:
	// Initialization
	void initWindow();
	void initStates();
	void initKeybinds();

	// Variables
	sf::RenderWindow *window;
	sf::View* mainView;
	sf::Clock clock;
	float delTime;
	std::stack<State*> states;
	std::map<std::string, int> keyRef;

public:
	Game();
	virtual ~Game();
	void update();
	void run();
	void render();
	void popState();
	void close();
	void eventUpdate();
	void clockUpdate();
};

