//#include <SFML/Graphics.hpp>
#include "State.h"
#include "Door.h"

class Player {
public:
    sf::RectangleShape shape;
    float speed;
    int hp;
    int money;

    Player(float x, float y, int h, int m);

    //void movement(sf::Vector2f movement, float delTime, std::vector<sf::FloatRect*> collisionRects, std::vector<Door*> doors);
    Door* movement(sf::Vector2f movement, float delTime, std::vector<sf::FloatRect*> collisionRects, std::vector<Door*> doors);
    void teleport(sf::Vector2f pos);
};