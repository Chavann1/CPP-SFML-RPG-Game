#include <SFML/Graphics.hpp>

int main()
{
    // INITIAL SETUP
    unsigned int width = 640;
    unsigned int height = 360;
    unsigned int framerate = 60;
    sf::RenderWindow window(sf::VideoMode({ width, height }), "Window Application");
    window.setFramerateLimit(framerate);

    // CREATE SHAPE
    sf::CircleShape shape(100.f);
    shape.setOrigin(shape.getGeometricCenter());
    shape.setPosition({width/2.0f, height/2.0f});
    shape.setFillColor(sf::Color::Green);

    while (window.isOpen())
    {
        while (const std::optional event = window.pollEvent())
        {
            // CLOSING WINDOW
            if (event->is<sf::Event::Closed>()) {
                window.close();
            }
            else if (const auto* keyPressed = event->getIf<sf::Event::KeyPressed>()) {
                if (keyPressed->scancode == sf::Keyboard::Scancode::Escape) {
                    window.close();
                }
            }
        }

        // CLEAR WINDOW
        window.clear();
        // DRAW
        window.draw(shape);
        window.display();
    }
}