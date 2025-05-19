#pragma once
#include "State.h"
#include "EnemyManager.h"

class Sword
{
	//sf::Clock lifetimeClock;
	EnemyManager* eManager;
	sf::FloatRect hitbox;
	float damage;
public:
	Sword(EnemyManager* eManager, float x, float y, int dir, float damage);
	void update();
	sf::RectangleShape szejp;
};

