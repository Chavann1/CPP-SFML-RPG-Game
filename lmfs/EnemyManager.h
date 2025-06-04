#pragma once
#include "State.h"
#include "Enemy.h"
#include "Touchable.h"

class EnemyManager
{
public:
	// Variables
	std::vector<Enemy*> enemies;
	std::vector<sf::FloatRect*>& collisionRects;
	std::vector<Touchable*>& touchables;
	sf::Vector2f pPos;

	// Methods
	EnemyManager(std::vector<sf::FloatRect*>& collisionRects, std::vector<Touchable*>& touchables);
	bool update(const float& delTime);
	void render(sf::RenderWindow& window);
	void updateEnemiesInRange(size_t start, size_t end, float delTime, const std::vector<sf::FloatRect*>& collisionRects, sf::Vector2f pPos);
};

