#include "State.h"
#include "Door.h"
#include "EnemyManager.h"
#include "Hud.h"
#include "Sword.h"

class Player {
public:
    // Variables
    sf::Sprite* shape;
    sf::RectangleShape hitbox;
    sf::Sound* hurtSound;
    sf::Clock damageClock;
    sf::Clock attackClock;
    sf::Clock runAnimClock;
    sf::Texture texture;
    sf::Texture dTexture;
    sf::Texture aTexture;
    sf::CircleShape lightHole;
    sf::CircleShape lightHole2;
    Hud* hud;
    EnemyManager* eManager;
    Sword* sword;
    int frame;
    int dir;
    bool damageable;
    float speed;
    float hp;
    float max_hp;
    float money;
    enum Player_State { idle, walking, attacking, dead};
    Player_State pState;

    // Methods
    Player(float x, float y, int h, float m, float max);
    ~Player();
    void update();
    void animate();
    void attack();
    bool interactCheck(sf::FloatRect box);
    Door* movement(sf::Vector2f movement, const float& delTime, std::vector<sf::FloatRect*> collisionRects, std::vector<Door*> doors);
    void teleport(sf::Vector2f pos);
};