#include "Door.h"

Door::Door(const sf::Vector2f& pos, float w, float h, int destId, const sf::Vector2f& destPos)
{
	collisionBox.position = pos;
	collisionBox.size = sf::Vector2f(w, h);
	destinationRoomId = destId;
	destinationPosition = destPos;

	shape.setPosition(pos);
	shape.setSize(sf::Vector2f(w, h));

}
