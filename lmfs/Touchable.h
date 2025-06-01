#pragma once
#include "State.h"

class Touchable
{
public: 
	int type;
	float value;
	sf::RectangleShape shape;
	Touchable();
	~Touchable();
};

