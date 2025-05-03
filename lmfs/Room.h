#pragma once
#include "State.h"
#include "Door.h"
#include "Enemy.h"
#include "EnemyManager.h"

class Room {
public:
    Room(const std::string& layoutFile, const std::string& graphicsFile, bool completed);
    ~Room();
    bool completed;
    void render(sf::RenderWindow& window) const;
    bool update(const float& delTime) const;
    void complete();
    const std::vector<sf::FloatRect*>& getCollisionRects() const;
    EnemyManager* getEManager();
    std::vector<Door*> doors;

private:
    void loadLayout(const std::string& layoutFile, bool completed);
    void loadGraphics(const std::string& graphicsFile);

    std::vector<sf::RectangleShape> tiles;
    std::vector<sf::FloatRect*> collisionRects;
    sf::Texture tileset;
    EnemyManager* eManager;
};
