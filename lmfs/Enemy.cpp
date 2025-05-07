#include "Enemy.h"

Enemy::Enemy(const sf::Vector2f& pos, int type, int dropId, int dropCount, bool priority): type(type) {
    shape.setPosition(pos);
    shape.setOrigin(sf::Vector2f(0.f, 0.f));
    loadSprite();
    damageClock.restart();
    moveClock.restart();
    runAnimClock.restart();
    dir = 0;
    frame = 0;
}

void Enemy::loadSprite()
{

    std::string textureFilename = "enemy_" + std::to_string(type);

    if (!texture.loadFromFile("assets/" + textureFilename + ".png")) {
        std::cerr << "Failed to load texture: " << textureFilename << std::endl;
        return;
    }

    shape.setTexture(&texture);
    switch (type) {
    case 0:
        shape.setTextureRect(sf::IntRect(sf::Vector2i(0, 0), sf::Vector2i(20, 21)));
        w = 20;
        h = 21;
        frameNum = 2;
        shape.setSize(sf::Vector2f(40.f, 42.f));
        hp = 2.f;
        speed = 50.f;
        damage = 1;

        hitbox.setSize(sf::Vector2f(30.f, 28.f));
        break;
    }

}

void Enemy::movement(const float& delTime, std::vector<sf::FloatRect*> collisionRects)
{
    if (moveClock.getElapsedTime() >= sf::seconds(3) || stuck) {
        walk = rand() % 3;
        if (walk != 2) {
            // Get random direction
            float x;
            float y;
            int dir_x = rand() % 3;
            int dir_y = rand() % 3;

            switch (dir_x) {
            case 0:
                x = -1;
                dir = 3;
                break;
            case 1:
                x = 1;
                dir = 1;
                break;
            case 2:
                x = 0;
                break;
            }

            switch (dir_y) {
            case 0:
                y = -1;
                dir = 2;
                break;
            case 1:
                y = 1;
                dir = 0;
                break;
            case 2:
                y = 0;
                break;
            }
            if (x != 0 && y != 0) {
                x *= 0.7071f;
                y *= 0.7071f;
            }

            move = sf::Vector2f(x, y);
        }
        moveClock.restart();
    }
        if (walk != 2) {
            // Test Copy
            sf::RectangleShape newS = shape;
            newS.move(move * speed * delTime);

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
                        move.x = 0.f;
                        stuck = true;
                        //shape.setPosition(sf::Vector2f(wLeft - rect.size.x, rect2.position.y));
                    }
                    // Check if it's to the left
                    if (pLeft > wLeft && pRight > wRight && pUp < wDown && pDown > wUp) {
                        move.x = 0.f;
                        stuck = true;
                        //shape.setPosition(sf::Vector2f(wRight, rect2.position.y));
                    }
                    // Check if it's on the bottom
                    if (pUp < wUp && pDown < wDown && pLeft < wRight && pRight > wLeft) {
                        move.y = 0.f;
                        stuck = true;
                        //shape.setPosition(sf::Vector2f(rect2.position.x, wUp- rect.size.y));
                    }
                    // Check if it's on the top
                    if (pUp > wUp && pDown > wDown && pLeft < wRight && pRight > wLeft) {
                        move.y = 0.f;
                        stuck = true;
                        //shape.setPosition(sf::Vector2f(rect2.position.x, wDown));
                    }
                }
            }
            if (move.x != 0 && move.y != 0) stuck = false;
            shape.move(move * speed * delTime);
            hitbox.setPosition(shape.getPosition() + sf::Vector2f(6.f, 12.f));
        }
}

void Enemy::animate()
{
    if (runAnimClock.getElapsedTime() >= sf::milliseconds(500)) {
            frame++;
            if (frame >= frameNum) frame = 0;
            runAnimClock.restart();
    }
    shape.setTextureRect(sf::IntRect(sf::Vector2i(frame * w, dir * h), sf::Vector2i(w, h)));

}
