#include "Player.h"

Player::Player(float x, float y, int h, int m) {
    shape.setSize(sf::Vector2f(20.f, 24.f));
    shape.setOrigin(sf::Vector2f(0.f, 0.f));
    shape.setPosition(sf::Vector2f(x, y));
    shape.setFillColor(sf::Color::Green);
    speed = 100.f;
    hp = h;
    money = m;
}
Door* Player::movement(sf::Vector2f movement, float delTime, std::vector<sf::FloatRect*> collisionRects, std::vector<Door*> doors) {
    if (movement.x != 0 && movement.y != 0) {
        movement *= 0.7071f;
    }

    //sf::Vector2f oldPos = shape.getPosition();
    
    // Test Copy
    sf::RectangleShape newS = shape;
    newS.move(movement * speed * delTime);

    // Player bounds shape
    sf::FloatRect oldRect = shape.getGlobalBounds();
    float olLeft = oldRect.position.x;
    float olRight = olLeft + oldRect.size.x;
    float olUp = oldRect.position.y;
    float olDown = olUp + oldRect.size.y;

    sf::FloatRect rect = newS.getGlobalBounds();
    float pLeft = rect.position.x;
    float pRight = pLeft + rect.size.x;
    float pUp = rect.position.y;
    float pDown = pUp + rect.size.y;

    // Check collision with walls
    for (auto p : collisionRects) {
        // Check if it's colliding at all
        if (rect.findIntersection(*p)) {
            sf::FloatRect wall = *p;
            float wLeft = wall.position.x;
            float wRight = wLeft + wall.size.x;
            float wUp = wall.position.y;
            float wDown = wUp + wall.size.y;
            // Check if it's to the right
            if (pLeft < wLeft && pRight < wRight && pUp < wDown && pDown > wUp) {
                movement.x = 0.f;
                //shape.setPosition(sf::Vector2f(wLeft - rect.size.x, rect2.position.y));
            }
            // Check if it's to the left
            if (pLeft > wLeft && pRight > wRight && pUp < wDown && pDown > wUp) {
                movement.x = 0.f;
                //shape.setPosition(sf::Vector2f(wRight, rect2.position.y));
            }
            // Check if it's on the bottom
            if (pUp < wUp && pDown < wDown && pLeft < wRight && pRight > wLeft) {
                movement.y = 0.f;
                //shape.setPosition(sf::Vector2f(rect2.position.x, wUp- rect.size.y));
            }
            // Check if it's on the top
            if (pUp > wUp && pDown > wDown && pLeft < wRight && pRight > wLeft) {
                movement.y = 0.f;
                //shape.setPosition(sf::Vector2f(rect2.position.x, wDown));
            }
        }
    }
    // Check collision with doors
    for (auto p : doors) {
        if (p->open) {
            if (rect.findIntersection(p->collisionBox)) {
                return p;
            }
        }
        else continue;
    }
    shape.move(movement * speed * delTime);
    return nullptr;
}

void Player::teleport(sf::Vector2f pos)
{
    shape.setPosition(pos);
}
