#pragma once

#include "State.h"
#include "Menu.h"

class MenuManager
{
public:
	// Variables
	std::stack<Menu*> menus;
	std::pair<int, int> update(const float& delTime, sf::RenderWindow& win);

	// Methods
	MenuManager();
	~MenuManager();
	void render(sf::RenderWindow& win);
};

