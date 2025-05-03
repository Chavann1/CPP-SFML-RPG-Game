//#include <SFML/Graphics.hpp>
#include "State.h"
#include "Door.h"
#include "EnemyManager.h"

class Player {
public:
    sf::RectangleShape shape;
    sf::RectangleShape hitbox;
    float speed;
    int hp;
    int money;
    enum State { idle, walking, attacking};
    sf::Clock damageClock;
    sf::Clock runAnimClock;
    State pState;
    Player(float x, float y, int h, int m);
    sf::Texture texture;
    int frame;
    int dir;
    //void movement(sf::Vector2f movement, float delTime, std::vector<sf::FloatRect*> collisionRects, std::vector<Door*> doors);
    void update();
    void animate();
    Door* movement(sf::Vector2f movement, const float& delTime, std::vector<sf::FloatRect*> collisionRects, std::vector<Door*> doors);
    EnemyManager* eManager;
    void teleport(sf::Vector2f pos);
};