//#include <SFML/Graphics.hpp>
#include "State.h"
#include "Door.h"
#include "EnemyManager.h"
#include "Hud.h"

class Player {
public:
    //sf::RectangleShape shape;
    sf::Sprite* shape;
    sf::RectangleShape hitbox;
    sf::Sound* hurtSound;
    Hud* hud;
    float speed;
    float hp;
    float max_hp;
    float money;
    enum Player_State { idle, walking, attacking, dead};
    Player_State pState;

    sf::Clock damageClock;
    sf::Clock attackClock;
    bool damageable;
    sf::Clock runAnimClock;
    Player(float x, float y, int h, float m, float max);
    sf::Texture texture;
    sf::Texture dTexture;
    int frame;
    int dir;
    //void movement(sf::Vector2f movement, float delTime, std::vector<sf::FloatRect*> collisionRects, std::vector<Door*> doors);
    void update();
    void animate();
    void attack();
    Door* movement(sf::Vector2f movement, const float& delTime, std::vector<sf::FloatRect*> collisionRects, std::vector<Door*> doors);
    EnemyManager* eManager;
    void teleport(sf::Vector2f pos);
};