#include "Touchable.h"

Touchable::Touchable(int type, int value, sf::Vector2f pos): type(type), value(value)
{
	forDeletion = false;
	shape.setPosition(pos);
	switch (type) {
	case 0:
		State::loadTextureImage(texture, "pickup_heal");
		shape.setTextureRect(sf::IntRect(sf::Vector2i(0,0), sf::Vector2i(11, 12)));
		shape.setSize(sf::Vector2f(22, 24));
		break;
	case 1:
		State::loadTextureImage(texture, "pickup_money");
		shape.setTextureRect(sf::IntRect(sf::Vector2i(0, 0), sf::Vector2i(11, 14)));
		shape.setSize(sf::Vector2f(22, 28));
		break;
	}

	shape.setTexture(&texture);
}

Touchable::~Touchable()
{
}
