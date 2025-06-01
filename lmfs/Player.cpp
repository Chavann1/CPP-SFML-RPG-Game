#include "Player.h"

// CO/DE -STRUCTORS
Player::Player(float x, float y, int h, float m, float max) {
    speed = 120.f;
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

    State::loadTextureImage(dTexture, "player_death");
    State::loadTextureImage(aTexture, "player_attack");

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

    // Set light circle properties
    lightHole.setRadius(64.f);
    lightHole.setFillColor(sf::Color(0, 0, 0, 0));
    lightHole2.setRadius(80.f);
    lightHole2.setFillColor(sf::Color(0, 0, 0, 24));
}
Player::~Player()
{
    //delete eManager;
    //delete hud;
    //delete shape;
    //delete hurtSound;
}
void Player::update()
{
    if (pState == attacking) {
        if (sword != nullptr) {
            sword->update();
        }
        if (attackClock.getElapsedTime() >= sf::milliseconds(400)) {
            // Finish attack
            // delete sword
            delete sword;
            sword = nullptr;
            // reset player sprite
            sf::Vector2f pos = shape->getPosition() + sf::Vector2f(20.f, 12.f);
            shape->setTexture(texture);
            shape->setTextureRect(sf::IntRect(sf::Vector2i(frame * 19, dir * 27), sf::Vector2i(19, 27)));
            shape->setPosition(pos);
            pState = walking;
        }
    }

    // Check collisions with enemies
    sf::FloatRect rect = hitbox.getGlobalBounds();
    sf::FloatRect eRect;

    if (damageable) {
        if (eManager != nullptr) {
            for (auto p : eManager->enemies) {
                // Look for intersection with enemy
                if (p->eState != Enemy::dead) {
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
        lightHole.setPosition(hitbox.getPosition() - sf::Vector2f(50.f, 48.f));
        lightHole2.setPosition(hitbox.getPosition()-sf::Vector2f(66.f, 64.f));
        if(eManager != nullptr) eManager->pPos = shape->getPosition();
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
    else if (pState == attacking) {
        // Animation played on death
        if (runAnimClock.getElapsedTime() >= sf::milliseconds(75)) {
            if (frame < 3) frame++;
            runAnimClock.restart();
        }
        shape->setTextureRect(sf::IntRect(sf::Vector2i(frame * 40, dir*40), sf::Vector2i(40, 40)));
    }


}

void Player::teleport(sf::Vector2f pos)
{
    // Set position of player and hitbox
    shape->setPosition(pos);
    hitbox.setPosition(shape->getPosition() + sf::Vector2f(8.f, 16.f));
    lightHole.setPosition(hitbox.getPosition() - sf::Vector2f(82.f, 80.f));
    lightHole2.setPosition(hitbox.getPosition() - sf::Vector2f(114.f, 112.f));
}

void Player::attack() {
    if (pState != dead && pState != attacking) {
        // Change sprite
        frame = 0;
        shape->setTexture(aTexture);
        shape->setTextureRect(sf::IntRect(sf::Vector2i(frame * 40, dir * 40), sf::Vector2i(40, 40)));
        sf::Vector2f pos = shape->getPosition() - sf::Vector2f(20.f, 12.f);
        shape->setPosition(pos);
        
        // Change state and create sword hitbox object
        pState = attacking;
        sword = new Sword(eManager, hitbox.getPosition().x, hitbox.getPosition().y, dir, 1.f);
        attackClock.restart();
    }
}

bool Player::interactCheck(sf::FloatRect box)
{
    float x = 0;
    float y = 0;
    float wid = 1;
    float hei = 1;
    switch (dir) {
    case 0:
        x = shape->getPosition().x;
        y = shape->getPosition().y + 24.f;
        wid = 28.f;
        hei = 32.f;
        break;
    case 1:
        x = shape->getPosition().x + 24.f;
        y = shape->getPosition().y;
        wid = 32.f;
        hei = 28.f;
        break;
    case 2:
        x = shape->getPosition().x;
        y = shape->getPosition().y - 32.f;
        wid = 28.f;
        hei = 32.f;
        break;
    case 3:
        x = shape->getPosition().x - 32.f;
        y = shape->getPosition().y;
        wid = 32.f;
        hei = 28.f;
        break;
    }

    sf::FloatRect temp(sf::Vector2f(x, y), sf::Vector2f(wid, hei));
    if (temp.findIntersection(box)) return true;
    return false;
}
