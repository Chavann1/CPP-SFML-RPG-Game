#include "Sword.h"

Sword::Sword(EnemyManager* eManager, float x, float y, int dir, float damage): damage(damage), eManager(eManager) {
	float width, height;
	float sword_x, sword_y;
	switch (dir) {
	case 0:
		sword_x = x;
		sword_y = y + 24.f;
		width = 28.f;
		height = 32.f;
		break;
	case 1:
		sword_x = x + 24.f;
		sword_y = y;
		width = 32.f;
		height = 28.f;
		break;
	case 2:
		sword_x = x;
		sword_y = y-32.f;
		width = 28.f;
		height = 32.f;
		break;
	case 3:
		sword_x = x-32.f;
		sword_y = y;
		width = 32.f;
		height = 28.f;
		break;
	}
	hitbox.size = sf::Vector2f(width, height);
	hitbox.position = sf::Vector2f(sword_x, sword_y);

	szejp.setOrigin(sf::Vector2f(0.f, 0.f));
	szejp.setPosition(sf::Vector2f(sword_x, sword_y));
	szejp.setSize(sf::Vector2f(width, height));
	szejp.setFillColor(sf::Color(255, 255, 255, 55));
}

void Sword::update()
{
	sf::FloatRect eRect;
	if (eManager != nullptr) {
		for (auto& p : eManager->enemies) {
			eRect = p->hitbox.getGlobalBounds();
			if (hitbox.findIntersection(eRect)) {
				//p->hp -= damage;
				p->dealDamage(damage, hitbox.position.x, hitbox.position.y);
				//if (p->hp <= 0) p->deathComplete = true;
			}
		}
	}
}
