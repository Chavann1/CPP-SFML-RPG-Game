#include "Player.h"

Player::Player(float x, float y, int h, int m) {
    speed = 100.f;
    hp = h;
    money = m;
    pState = idle;
    frame = 1;
    dir = 0;
    runAnimClock.restart();

    // Load sprite
    std::string textureFilename = "player_run.png";

    if (!texture.loadFromFile("assets/" + textureFilename)) {
        std::cerr << "Failed to load texture: " << textureFilename << std::endl;
        return;
    }

    shape.setOrigin(sf::Vector2f(0.f, 0.f));
    shape.setPosition(sf::Vector2f(x, y));
    shape.setTexture(&texture);
    shape.setTextureRect(sf::IntRect(sf::Vector2i(0, 0), sf::Vector2i(19, 27)));
    //shape.setSize(sf::Vector2f(38.f, 54.f));
    shape.setSize(sf::Vector2f(38.f, 54.f));

    hitbox.setOrigin(sf::Vector2f(0.f, 0.f));
    hitbox.setPosition(sf::Vector2f(x+8, y+16));
    hitbox.setSize(sf::Vector2f(24.f, 34.f));
}
void Player::update()
{
    sf::FloatRect rect = shape.getGlobalBounds();
    sf::FloatRect eRect;
    if (eManager != nullptr) {
        for (auto p : eManager->enemies) {
            eRect = p->shape.getGlobalBounds();
            if (rect.findIntersection(eRect)) {
                std::cout << "ecollision";
            }
        }
    }
}
Door* Player::movement(sf::Vector2f movement, const float& delTime, std::vector<sf::FloatRect*> collisionRects, std::vector<Door*> doors) {
    if (movement.x != 0 && movement.y != 0) {
        movement *= 0.7071f;
    }

    //sf::Vector2f oldPos = shape.getPosition();
    
    // Test Copy
    sf::RectangleShape newS = hitbox;
    newS.move(movement * speed * delTime);

    // Player bounds shape
    sf::FloatRect oldRect = hitbox.getGlobalBounds();
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
    if (movement.x == 0 && movement.y == 0) {
        pState = idle;
    }
    else {
        pState = walking;
    }
    shape.move(movement * speed * delTime);
    hitbox.setPosition(shape.getPosition() + sf::Vector2f(8.f, 16.f));
    return nullptr;
}

void Player::animate()
{
    if(pState == idle) shape.setTextureRect(sf::IntRect(sf::Vector2i(0, dir * 27), sf::Vector2i(19, 27)));
    else {
        if (runAnimClock.getElapsedTime() >= sf::milliseconds(200)) {
            frame++;
            if (frame > 4) frame = 1;
            runAnimClock.restart();
        }
        shape.setTextureRect(sf::IntRect(sf::Vector2i(frame * 19, dir * 27), sf::Vector2i(19, 27)));
    }

}

void Player::teleport(sf::Vector2f pos)
{
    shape.setPosition(pos);
}
