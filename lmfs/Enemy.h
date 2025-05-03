#pragma once
#include "State.h"

class Enemy
{
public:
	int type;
	Enemy(const sf::Vector2f& pos, int type, int dropId, int dropCount, bool priority);
	void loadSprite();
	void movement(const float& delTime, std::vector<sf::FloatRect*> collisionRects);
	void animate();
	sf::RectangleShape shape;
	float hp;
	float speed;
	sf::Clock damageClock;

private:
	sf::Texture texture;
	sf::Clock moveClock;
	sf::Vector2f move;
	int walk;
	int dir;
	int frame;
	int w, h, frameNum;
	sf::Clock runAnimClock;
	bool stuck = false;
};

