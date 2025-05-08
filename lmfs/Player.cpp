#include "Player.h"

// CO/DE -STRUCTORS
Player::Player(float x, float y, int h, float m, float max) {
    speed = 100.f;
    hp = h;
    money = m;
    pState = idle;
    frame = 1;
    dir = 0;
    max_hp = max;
    runAnimClock.restart();

    damageable = true;

    // Load sprite
    State::loadTextureImage(texture, "player_run");
    /*
    std::string textureFilename = "player_run.png";

    if (!texture.loadFromFile("assets/" + textureFilename)) {
        std::cerr << "Failed to load texture: " << textureFilename << std::endl;
        return;
    }
    */

    State::loadTextureImage(dTexture, "player_death");
    /*
    textureFilename = "player_death.png";

    if (!dTexture.loadFromFile("assets/" + textureFilename)) {
        std::cerr << "Failed to load texture: " << textureFilename << std::endl;
        return;
    }
    */

    // Create player sprite
    shape = new sf::Sprite(texture);
    shape->setOrigin(sf::Vector2f(0.f, 0.f));
    shape->setPosition(sf::Vector2f(x, y));
    shape->setTextureRect(sf::IntRect(sf::Vector2i(0, 0), sf::Vector2i(19, 27)));
    shape->setScale(sf::Vector2f(2.f, 2.f));

    // Create player hitbox
    hitbox.setOrigin(sf::Vector2f(0.f, 0.f));
    hitbox.setPosition(sf::Vector2f(x + 8, y + 16));
    hitbox.setSize(sf::Vector2f(24.f, 34.f));
}
void Player::update()
{
    if (pState == attacking) {
        if (attackClock.getElapsedTime() >= sf::milliseconds(400)) {
            pState = walking;
        }
    }

    // Check collisions with enemies
    sf::FloatRect rect = shape->getGlobalBounds();
    sf::FloatRect eRect;

    if (damageable) {
        if (eManager != nullptr) {
            for (auto p : eManager->enemies) {
                // Look for intersection with enemy
                eRect = p->hitbox.getGlobalBounds();
                if (rect.findIntersection(eRect)) {
                    damageable = false;
                    shape->setColor(sf::Color(255, 255, 255, 128));
                    hurtSound->play();
                    hp -= p->damage;

                    // Update HUD
                    hud->updateHp(hp, max_hp);
                    if (hp <= 0) {
                        // Initialize Game Over
                        shape->setColor(sf::Color(255, 255, 255, 255));
                        pState = dead;
                        shape->setTexture(dTexture);
                        shape->setTextureRect(sf::IntRect(sf::Vector2i(0, 0), sf::Vector2i(24, 24)));
                        runAnimClock.restart();
                        frame = 0;
                    }
                    damageClock.restart();
                }
            }
        }
    }
    else {
        if (pState != dead) {
            // End invincibility frames
            if (damageClock.getElapsedTime() >= sf::seconds(0.75f)) {
                damageable = true;
                shape->setColor(sf::Color(255, 255, 255, 255));
            }
        }
    }
}
Door* Player::movement(sf::Vector2f movement, const float& delTime, std::vector<sf::FloatRect*> collisionRects, std::vector<Door*> doors) {
    // Adjust movement for diagonal directions
    if (movement.x != 0 && movement.y != 0) {
        movement *= 0.7071f;
    }

    // Player bounds shape
    sf::FloatRect oldRect = hitbox.getGlobalBounds();
    float olLeft = oldRect.position.x;
    float olRight = olLeft + oldRect.size.x;
    float olUp = oldRect.position.y;
    float olDown = olUp + oldRect.size.y;

    // Copy of player hitbox for testing collisions
    sf::RectangleShape newS = hitbox;
    newS.move(movement * speed * delTime);
    sf::FloatRect rect = newS.getGlobalBounds();
    float pLeft = rect.position.x;
    float pRight = pLeft + rect.size.x;
    float pUp = rect.position.y;
    float pDown = pUp + rect.size.y;

    // Check collision with walls
    for (auto p : collisionRects) {
        // Check if it's colliding at all
        if (rect.findIntersection(*p)) {
            // If it's colliding check exact collisions
            sf::FloatRect wall = *p;
            float wLeft = wall.position.x;
            float wRight = wLeft + wall.size.x;
            float wUp = wall.position.y;
            float wDown = wUp + wall.size.y;
            // Check if it's to the right
            if (pLeft < wLeft && pRight < wRight && pUp < wDown && pDown > wUp) {
                movement.x = 0.f;
            }
            // Check if it's to the left
            if (pLeft > wLeft && pRight > wRight && pUp < wDown && pDown > wUp) {
                movement.x = 0.f;
            }
            // Check if it's on the bottom
            if (pUp < wUp && pDown < wDown && pLeft < wRight && pRight > wLeft) {
                movement.y = 0.f;
            }
            // Check if it's on the top
            if (pUp > wUp && pDown > wDown && pLeft < wRight && pRight > wLeft) {
                movement.y = 0.f;
            }
        }
    }
    // Check collision with doors
    for (auto p : doors) {
        if (p->open) {
            if (rect.findIntersection(p->collisionBox)) {
                // If we are colliding with a door return the door
                return p;
            }
        }
        else continue;
    }

    // Change states for animation purposes
    if (pState == Player::idle || pState == Player::walking) {
        if (movement.x == 0 && movement.y == 0) {
            pState = idle;
        }
        else {
            pState = walking;
        }

        // Apply  the movement
        shape->move(movement * speed * delTime);
        hitbox.setPosition(shape->getPosition() + sf::Vector2f(8.f, 16.f));
    }
    return nullptr;
}

void Player::animate()
{
    // Set position of rectangle on tilesheet
    if (pState == idle) shape->setTextureRect(sf::IntRect(sf::Vector2i(0, dir * 27), sf::Vector2i(19, 27)));
    else if (pState == walking) {
        if (runAnimClock.getElapsedTime() >= sf::milliseconds(200)) {
            frame++;
            if (frame > 4) frame = 1;
            runAnimClock.restart();
        }

        shape->setTextureRect(sf::IntRect(sf::Vector2i(frame * 19, dir * 27), sf::Vector2i(19, 27)));
    }
    else if (pState == dead) {
        // Animation played on death
        if (runAnimClock.getElapsedTime() >= sf::milliseconds(300)) {
            if (frame < 3) frame++;
            runAnimClock.restart();
        }
        shape->setTextureRect(sf::IntRect(sf::Vector2i(frame * 24, 0), sf::Vector2i(24, 24)));
    }

}

void Player::teleport(sf::Vector2f pos)
{
    // Set position of player and hitbox
    shape->setPosition(pos);
    hitbox.setPosition(shape->getPosition() + sf::Vector2f(8.f, 16.f));
}

void Player::attack() {
    if (pState != dead && pState != attacking) {
        pState = attacking;
        attackClock.restart();
    }
}