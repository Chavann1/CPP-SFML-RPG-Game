#include "Game.h"

// CON AND DE "STRUCTORS"
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

    getline(setFile, line);
    setFile >> width >> height >> framerate;

    setFile.close();
    float w, h;
    w = width;
    h = height;
    mainView = new sf::View(sf::FloatRect(sf::Vector2f(0, 0), sf::Vector2f(w, h)));

	window = new sf::RenderWindow(sf::VideoMode({ width, height }), line);
    window->setView(*mainView);
    window->setFramerateLimit(framerate);
    //this->window = new sf::RenderWindow(sf::VideoMode({ 640, 460 }), "line");
    window->setFramerateLimit(60);
    sf::Image icon;
    icon.loadFromFile("assets/icon.png");
    window->setIcon(icon.getSize(), icon.getPixelsPtr());
    
}

void Game::initStates()
{
    //states.push(new GameState(window, &this->keyRef, 1));
    states.push(new MainMenuState(window, &this->keyRef, states));
}

void Game::initKeybinds()
{
    fs::path keySet = "config/keybinds.ini";
    if (!std::filesystem::exists(keySet)) {
        std::ofstream file(keySet);
        file << "UP 22\nDOWN 18\nLEFT 0\nRIGHT 3\nESC 36\nATK 25\nINT 23";
        file.close();
    }

    // Open file
    std::ifstream setFile(keySet);
    if (setFile.is_open()) {
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
        bool end = states.top()->update(delTime);
        if (end) popState();
        if (!states.empty()) states.top()->inputUpdate(delTime);
    }
}

void Game::run()
{

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

    if (!states.empty()) {
        states.top()->render(window);
    }

    // Draw
    window->display();

}

void Game::popState()
{
    // First check if it's not empty
    if(!states.empty()) {
        states.top()->endState();
        delete states.top();
        states.pop();
        // Check if it's not empty after deletion
        if (!states.empty()) states.top()->start();
        else close();
    } else {
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
