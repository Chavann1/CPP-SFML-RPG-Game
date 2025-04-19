#pragma once

#include "State.h"
#include "Menu.h"
//#include "GameState.h"

class MenuManager
{
public:
	std::stack<Menu*> menus;
	MenuManager(/*std::stack<State*>& states*/);
	~MenuManager();
	std::pair<int, int> update(const float& delTime, sf::RenderWindow& win);
	void render(sf::RenderWindow& win);
	//std::stack<State*>& states;
};

