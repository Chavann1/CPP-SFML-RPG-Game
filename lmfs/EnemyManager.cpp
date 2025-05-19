#include "EnemyManager.h"

EnemyManager::EnemyManager(std::vector<sf::FloatRect*>& collisionRects) : collisionRects(collisionRects) {
}

bool EnemyManager::update(const float& delTime)
{
	if (enemies.size() > 0) {
		
		for(auto it = enemies.begin(); it != enemies.end(); ) {
			Enemy* p = *it;

			if (p->deathComplete) {
				delete p;
				it = enemies.erase(it);
			} else {
				p->movement(delTime, collisionRects);
				p->animate();
				++it;
			}
		}
		
		/*
		for (auto p : enemies) {
			p->movement(delTime, collisionRects);
			p->animate();
		}
		*/
		
	} else return true;
	return false;
}

void EnemyManager::render(sf::RenderWindow& window)
{
	if (enemies.size() > 0) {
		for (auto p : enemies) {
			//window.draw(p->hitbox);
			window.draw(p->shape);
		}
	}
}
