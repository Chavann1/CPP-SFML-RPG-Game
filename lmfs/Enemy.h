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
	sf::RectangleShape hitbox;
	float hp;
	float speed;
	float damage;
	sf::Clock damageClock;
	enum Enemy_State { walking, stunned, dead };
	Enemy_State eState;

private:
	sf::Texture texture;
	sf::Texture deathTexture;
	sf::Clock moveClock;
	sf::Vector2f move;
	int walk;
	int dir;
	int frame;
	int w, h, frameNum;
	sf::Clock runAnimClock;
	sf::Clock deathAnimClock;
	bool stuck = false;
};

