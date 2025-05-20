#pragma once
#include "State.h"

class Enemy
{
private:
	sf::Texture texture;
	sf::Texture deathTexture;
	sf::Vector2f move;
	sf::Clock moveClock;
	sf::Clock runAnimClock;
	sf::Clock deathAnimClock;
	int walk, dir, frame, w, h, frameNum;
	bool stuck = false;
public:
	// Variables
	//sf::RectangleShape shape;
	sf::Sprite shape;
	sf::RectangleShape hitbox;
	sf::Clock damageClock;
	float hp, speed, damage;
	bool deathComplete = false;
	bool damageable;
	int type;
	int moveCounter;
	enum Enemy_State { walking, stunned, dead };
	Enemy_State eState;

	// Methods
	Enemy(const sf::Vector2f& pos, int type, int dropId, int dropCount, bool priority);
	~Enemy();
	void dealDamage(float damage, float x, float y);
	void loadSprite();
	void movement(const float& delTime, std::vector<sf::FloatRect*> collisionRects, sf::Vector2f pPos);
	void animate();
	sf::Vector2f randomDirection(int& directionVar);
	sf::Vector2f playerDirection(sf::Vector2f pPos);
};

