#pragma once
#include "State.h"
#include "Enemy.h"
class EnemyManager
{
public:
	EnemyManager(std::vector<sf::FloatRect*>& collisionRects);
	std::vector<Enemy*> enemies;
	std::vector<sf::FloatRect*>& collisionRects;

	void update(const float& delTime);
	void render(sf::RenderWindow& window);
};

