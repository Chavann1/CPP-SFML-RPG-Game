#include "Game.h"

int main()
{
    sf::Font font;
    font.openFromFile("assets\\Retro_Gaming.ttf");
    Game game;
    game.run();
    
    /*
    window.setFramerateLimit(framerate);

    unsigned int width = 640;
    unsigned int height = 360;
    unsigned int framerate = 60;

    // CREATE SHAPE
    sf::RectangleShape shape;
    shape.setSize(sf::Vector2f(80, 40));
    shape.setOrigin(shape.getGeometricCenter());
    shape.setPosition({width/2.0f, height/2.0f});
    shape.setFillColor(sf::Color::Green);


    while (window.isOpen())
    {
        // MAIN LOOP
        while (const std::optional event = window.pollEvent())
        {
            // CLOSING WINDOW
            if (event->is<sf::Event::Closed>()) {
                window.close();
            }

            }
        }

        // CLEAR WINDOW
        window.clear();
        // DRAW
        window.draw(shape);
        window.display();
        
    }*/
 }

