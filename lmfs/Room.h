#pragma once
#include "State.h"
#include "Door.h"
#include "Enemy.h"
#include "EnemyManager.h"

class Room {
public:
    // Variables
    std::vector<Door*> doors;
    bool completed;

    // Methods
    Room(const std::string& layoutFile, const std::string& graphicsFile, bool completed);
    ~Room();
    void render(sf::RenderWindow& window) const;
    bool update(const float& delTime);
    void complete();
    const std::vector<sf::FloatRect*>& getCollisionRects() const;
    EnemyManager* getEManager();

private:
    // Variables
    std::vector<sf::RectangleShape> tiles;
    std::vector<sf::FloatRect*> collisionRects;
    sf::Texture tileset;
    EnemyManager* eManager;

    // Methods
    void loadLayout(const std::string& layoutFile, bool completed);
    void loadGraphics(const std::string& graphicsFile);
};
