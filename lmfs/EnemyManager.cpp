#include "EnemyManager.h"

EnemyManager::EnemyManager(std::vector<sf::FloatRect*>& collisionRects) : collisionRects(collisionRects) {
}

bool EnemyManager::update(const float& delTime)
{
	if (enemies.size() > 0) {
		for (auto p : enemies) {
			p->movement(delTime, collisionRects);
			p->animate();
		}
	} else return true;
	return false;
}

void EnemyManager::render(sf::RenderWindow& window)
{
	if (enemies.size() > 0) {
		for (auto p : enemies) {
			window.draw(p->shape);
		}
	}
}
