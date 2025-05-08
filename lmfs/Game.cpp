#include "Game.h"

// Constructors
Game::Game()
{
    initWindow();
    initKeybinds();
    initStates();
}

Game::~Game()
{
    delete this->window;

    // Clear states stack
    while (!states.empty()) {
        delete states.top();
        states.pop();
    }
}

// WINDOW INITIALIZATION
void Game::initWindow()
{

    fs::path winSet = "config/window.ini";

    // If file with window settings does not exist create one
    if (!std::filesystem::exists(winSet)) {
        std::ofstream file(winSet);
        // Default settings
        file << "Window\n";
        file << 640 << "\n";
        file << 512 << "\n";
        file << 60;
        file.close();
    }

    // Open file
    std::ifstream setFile(winSet);


    // Variables to read values into
    std::string line = "default";
    unsigned int width = 640;
    unsigned int height = 512;
    unsigned int framerate = 60;

    // Reading
    getline(setFile, line);
    setFile >> width >> height >> framerate;

    setFile.close();

    float w, h;
    w = width;
    h = height;

    // Creating view and window
    mainView = new sf::View(sf::FloatRect(sf::Vector2f(0, 0), sf::Vector2f(w, h)));
    window = new sf::RenderWindow(sf::VideoMode({ width, height }), line);
    window->setView(*mainView);
    window->setFramerateLimit(framerate);
    window->setFramerateLimit(60);

    // Window icon
    sf::Image icon;
    icon.loadFromFile("assets/icon.png");
    window->setIcon(icon.getSize(), icon.getPixelsPtr());

}

void Game::initStates()
{
    states.push(new MainMenuState(window, &this->keyRef, states));
}

void Game::initKeybinds()
{
    fs::path keySet = "config/keybinds.ini";

    // If file doesn't exist, set default
    if (!std::filesystem::exists(keySet)) {
        std::ofstream file(keySet);
        // Default keybinds
        file << "UP 22\nDOWN 18\nLEFT 0\nRIGHT 3\nESC 36\nATK 25\nINT 23";
        file.close();
    }

    std::ifstream setFile(keySet);
    if (setFile.is_open()) {
        // Reading keybinds into map
        std::string key;
        int val;
        while (setFile >> key >> val) {
            keyRef[key] = val;
            std::cout << "KEY " << key << " SET TO VALUE " << keyRef[key] << std::endl;
        }
    }

    setFile.close();
}

// METHODS
void Game::update()
{
    if (!states.empty()) {
        // Running the top state's update code, if it return true it means the state is finished ad we remove it
        bool end = states.top()->update(delTime);
        if (end) popState();
        if (!states.empty()) states.top()->inputUpdate(delTime);
    }
}

void Game::run()
{
    // Main game loop, runs everything
    while (window->isOpen())
    {
        clockUpdate();
        eventUpdate();
        update();
        render();
    }
}

void Game::render()
{
    // Clear window
    window->clear();

    // Running the state's rendering code, which will give everything to the window
    if (!states.empty()) {
        states.top()->render(window);
    }

    // Draw
    window->display();

}

void Game::popState()
{
    // First check if it's not empty
    if (!states.empty()) {
        states.top()->endState();
        delete states.top();
        states.pop();
        // Check if it's not empty after deletion
        if (!states.empty()) states.top()->start();
        else close();
    }
    else {
        close();
    }
}

void Game::close() {
    window->close();
}

void Game::eventUpdate()
{
    // MAIN LOOP
    while (const std::optional event = window->pollEvent())
    {
        // Closing window
        if (event->is<sf::Event::Closed>()) {
            popState();
        }

    }
}

void Game::clockUpdate()
{
    delTime = clock.restart().asSeconds();
}
