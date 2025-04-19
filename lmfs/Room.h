#pragma once
#include "State.h"
#include "Door.h"

class Room {
public:
    Room(const std::string& layoutFile, const std::string& graphicsFile, bool completed);
    ~Room();

    void render(sf::RenderWindow& window) const;
    const std::vector<sf::FloatRect*>& getCollisionRects() const;
    std::vector<Door*> doors;

private:
    void loadLayout(const std::string& layoutFile, bool completed);
    void loadGraphics(const std::string& graphicsFile);

    std::vector<sf::RectangleShape> tiles;
    std::vector<sf::FloatRect*> collisionRects;
    sf::Texture tileset;
};
