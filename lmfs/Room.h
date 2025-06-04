#pragma once
#include "State.h"
#include "Door.h"
#include "Enemy.h"
#include "EnemyManager.h"
#include "Interactable.h"
#include "Touchable.h"
#include "NPC.h"

class Room {
public:
    // Variables
    std::vector<Door*> doors;
    std::vector<Interactable*> interacts;
    std::vector<Touchable*> touchables;
    std::vector<std::pair<sf::CircleShape, sf::CircleShape>> lights;
    sf::Clock lightClock;
    bool darknessOn;
    bool lightCycle;
    bool completed;
    int musicId;

    // Methods
    Room(const std::string& layoutFile, const std::string& graphicsFile, bool completed);
    ~Room();
    void render(sf::RenderWindow& window) const;
    bool update(const float& delTime);
    void complete();
    const std::vector<sf::FloatRect*>& getCollisionRects() const;
    EnemyManager* getEManager();
    void addLights(sf::RenderTexture& darkness);

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
