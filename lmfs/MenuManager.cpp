#include "MenuManager.h"

MenuManager::MenuManager()
{
}

MenuManager::~MenuManager()
{
}

std::pair<int, int> MenuManager::update(const float& delTime, sf::RenderWindow& win)
{
	return menus.top()->update(win);
}

void MenuManager::render(sf::RenderWindow& win)
{
	menus.top()->draw(win);
}
