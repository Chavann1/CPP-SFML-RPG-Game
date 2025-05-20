#include "Enemy.h"

// CO/DE -STRUCTORS
Enemy::Enemy(const sf::Vector2f& pos, int type, int dropId, int dropCount, bool priority) : type(type), shape(texture) {
    // Initialize the enemy
    shape.setPosition(pos);
    shape.setOrigin(sf::Vector2f(0.f, 0.f));
    loadSprite();

    // Restart clocks
    damageClock.restart();
    moveClock.restart();
    runAnimClock.restart();
    dir = 0;
    frame = 0;

    State::loadTextureImage(deathTexture, "enemy_death");
    eState = walking;
    damageable = true;
}

Enemy::~Enemy()
{
}

void Enemy::dealDamage(float damage, float x, float y)
{
    if (damageable) {
        hp -= damage;
        damageClock.restart();
        damageable = false;
        //shape.setFillColor(sf::Color::Black);
        shape.setColor(sf::Color(255, 255, 255, 128));
        eState = stunned;

        if (hp <= 0) {
            //shape.setFillColor(sf::Color::White);
            shape.setColor(sf::Color(255, 255, 255, 255));
            eState = dead;
            frame = 0;
            //shape.setTexture(&deathTexture);
            shape.setTexture(deathTexture);
            shape.setTextureRect(sf::IntRect(sf::Vector2i(0, 0), sf::Vector2i(34, 32)));
        }
    }
}

void Enemy::loadSprite()
{

    State::loadTextureImage(texture, "enemy_" + std::to_string(type));

    //shape.setTexture(&texture);
    shape.setTexture(texture);
    switch (type) {
    case 0:
        shape.setTextureRect(sf::IntRect(sf::Vector2i(0, 0), sf::Vector2i(20, 21)));
        //shape.setSize(sf::Vector2f(40.f, 42.f));
        shape.setScale(sf::Vector2f(2.f, 2.f));
        hitbox.setSize(sf::Vector2f(30.f, 28.f));
        // Initialize enemy internal variables
        w = 20;
        h = 21;
        frameNum = 2;

        // Initialize enemy gameplay statistics
        hp = 2.f;
        speed = 50.f;
        damage = 1.f;
        moveCounter = 3;
        break;
    case 1:
        shape.setTextureRect(sf::IntRect(sf::Vector2i(0, 0), sf::Vector2i(20, 21)));
        //shape.setSize(sf::Vector2f(40.f, 42.f));
        shape.setScale(sf::Vector2f(2.f, 2.f));
        hitbox.setSize(sf::Vector2f(30.f, 28.f));
        // Initialize enemy internal variables
        w = 20;
        h = 21;
        frameNum = 2;

        // Initialize enemy gameplay statistics
        hp = 4.f;
        speed = 100.f;
        damage = 2.f;
        moveCounter = 1;
        break;
    }

}

void Enemy::movement(const float& delTime, std::vector<sf::FloatRect*> collisionRects, sf::Vector2f pPos)
{
    if (eState != dead) {
        if (damageClock.getElapsedTime() >= sf::milliseconds(500)) {
            damageable = true;
            //shape.setFillColor(sf::Color::White);
            shape.setColor(sf::Color(255, 255, 255, 255));
            eState = walking;
        }
    }
    if (eState == walking) {
        if (moveClock.getElapsedTime() >= sf::seconds(moveCounter) || stuck) {
            walk = rand() % 3;
            // 2 in 3 chance to move
            if (walk != 2) {
                switch (type) {
                case 0:
                    // Get a random direction
                    move = randomDirection(dir);
                    break;
                case 1:
                    move = playerDirection(pPos);
                    break;
                }
            }
            moveClock.restart();
        }
        if (walk != 2) {
            // Test copy of the shape
            sf::RectangleShape newS = hitbox;
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
                    }
                    // Check if it's to the left
                    if (pLeft > wLeft && pRight > wRight && pUp < wDown && pDown > wUp) {
                        move.x = 0.f;
                        stuck = true;
                    }
                    // Check if it's on the bottom
                    if (pUp < wUp && pDown < wDown && pLeft < wRight && pRight > wLeft) {
                        move.y = 0.f;
                        stuck = true;
                    }
                    // Check if it's on the top
                    if (pUp > wUp && pDown > wDown && pLeft < wRight && pRight > wLeft) {
                        move.y = 0.f;
                        stuck = true;
                    }
                }
            }
            if (move.x != 0 && move.y != 0) stuck = false;
            shape.move(move * speed * delTime);
            hitbox.setPosition(shape.getPosition() + sf::Vector2f(6.f, 12.f));
        }
    }
}

void Enemy::animate()
{
    if (eState == walking) {
        if (runAnimClock.getElapsedTime() >= sf::milliseconds(500)) {
            frame++;
            if (frame >= frameNum) frame = 0;
            runAnimClock.restart();
        }
        shape.setTextureRect(sf::IntRect(sf::Vector2i(frame * w, dir * h), sf::Vector2i(w, h)));
    }
    else if (eState == dead) {
        if (runAnimClock.getElapsedTime() >= sf::milliseconds(250)) {
            if (frame < 4) frame++;
            else deathComplete = true;
            runAnimClock.restart();
        }
        shape.setTextureRect(sf::IntRect(sf::Vector2i(frame*34, 0), sf::Vector2i(34, 32)));
    }

}

sf::Vector2f Enemy::playerDirection(sf::Vector2f pPos) {
    float dx = shape.getPosition().x - pPos.x;
    float dy = shape.getPosition().y - pPos.y;

    float length = std::sqrt(dx * dx + dy * dy);
    if (length == 0.0f) return { 0.0f, 0.0f };

    // Normalize direction vector
    float nx = -dx / length;
    float ny = -dy / length;

    return sf::Vector2f(nx, ny);
}

sf::Vector2f Enemy::randomDirection(int& directionVar) {
    // Get random direction
    float x;
    float y;
    int dir_x = rand() % 3;
    int dir_y = rand() % 3;

    switch (dir_x) {
    case 0:
        x = -1;
        directionVar = 3;
        break;
    case 1:
        x = 1;
        directionVar = 1;
        break;
    case 2:
        x = 0;
        break;
    }

    switch (dir_y) {
    case 0:
        y = -1;
        directionVar = 2;
        break;
    case 1:
        y = 1;
        directionVar = 0;
        break;
    case 2:
        y = 0;
        break;
    }
    if (x != 0 && y != 0) {
        x *= 0.7071f;
        y *= 0.7071f;
    }

    return sf::Vector2f(x, y);
}