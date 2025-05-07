#pragma once
#include "State.h"
#include "EnemyManager.h"

class Sword
{
	//sf::Clock lifetimeClock;
	EnemyManager* eManager;
	Sword(EnemyManager* eManager);
};

