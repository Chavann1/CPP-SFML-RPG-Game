#include "EnemyManager.h"

EnemyManager::EnemyManager(std::vector<sf::FloatRect*>& collisionRects, std::vector<Touchable*>& touchables): collisionRects(collisionRects), touchables(touchables) {
	pPos = sf::Vector2f(0.f, 0.f);
}

bool EnemyManager::update(const float& delTime) {
    if (enemies.empty()) return true;

    const size_t count = enemies.size();
    const size_t mid = count / 2;

    // Parallel movement/animation
    auto worker = [&](size_t start, size_t end) {
        for (size_t i = start; i < end; ++i) {
            Enemy* p = enemies[i];
            if (!p->deathComplete) {
                p->movement(delTime, collisionRects, pPos);
                p->animate();
            }
        }
    };

    std::thread t1(worker, 0, mid);
    std::thread t2(worker, mid, count);

    t1.join();
    t2.join();

    // Cleanup
    for (auto it = enemies.begin(); it != enemies.end(); ) {
        Enemy* p = *it;
        if (p->deathComplete) {
            if(p->dropCount > 0) touchables.push_back(new Touchable(p->dropId, p->dropCount, p->shape.getPosition()));
            delete p;
            it = enemies.erase(it);
        }
        else {
            ++it;
        }
    }

    return false;
}

void EnemyManager::updateEnemiesInRange(size_t start, size_t end, float delTime, const std::vector<sf::FloatRect*>& collisionRects, sf::Vector2f pPos) {
	for (size_t i = start; i < end; ++i) {
		if (!enemies[i]->deathComplete) {
			enemies[i]->movement(delTime, collisionRects, pPos);
			enemies[i]->animate();
		}
	}
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
