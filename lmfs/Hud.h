#pragma once
#include "State.h"

class Hud
{
public:
	std::vector<std::pair<sf::RectangleShape, int>> hearts;
	sf::RectangleShape moneyIcon;
	sf::Text* moneyNum;
	sf::Texture hpFullTexture;
	sf::Texture hpEmptyTexture;
	sf::Texture moneyTexture;

	Hud(float max_hp, float money, const sf::Font& font);
	void draw(sf::RenderWindow& window);
	void updateHp(float hp, float max_hp);
	void updateMoney(float money);
};

