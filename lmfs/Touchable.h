#pragma once
#include "State.h"

class Touchable
{
public: 
	int type, value;
	bool forDeletion;
	sf::Texture texture;
	sf::RectangleShape shape;
	Touchable(int type, int value, sf::Vector2f pos);
	~Touchable();
};

