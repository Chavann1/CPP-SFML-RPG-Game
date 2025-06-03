#include "MainMenuState.h"


// CO/DE -STRUCTORS
MainMenuState::MainMenuState(sf::RenderWindow* newWin, std::map<std::string, int>* keyNew, std::stack<State*>& states) : State(newWin, keyNew), states(states) {
	// Initialization
	initFonts();
	initSounds();
	startTimer = 0.25;

	// Create menu manager and menu
	manager = new MenuManager();
	manager->menus.push(new Menu());
	manager->menus.top()->addButton(Button({ 40, 120 }, { 200, 50 }, "New Game", 0, 0, font, hoverBuffer, clickBuffer));
	manager->menus.top()->addButton(Button({ 40, 200 }, { 200, 50 }, "Load Game", 0, 1, font, hoverBuffer, clickBuffer));
	manager->menus.top()->addButton(Button({ 40, 280 }, { 200, 50 }, "Options", 2, 0, font, hoverBuffer, clickBuffer));
	manager->menus.top()->addButton(Button({ 40, 360 }, { 200, 50 }, "Quit", 1, 0, font, hoverBuffer, clickBuffer));

	// Load background image
	State::loadTextureImage(bgTexture, "menu_bg");

	bgShape.setTexture(&bgTexture);
	bgShape.setTextureRect(sf::IntRect(sf::Vector2i(0, 0), sf::Vector2i(640, 512)));
	bgShape.setSize(newWin->getView().getSize());

}

MainMenuState::~MainMenuState()
{
}

// INITIALIZATION
void MainMenuState::initFonts()
{
	if (!this->font.openFromFile("assets/Retro_Gaming.ttf"))
	{
		std::cout << ("Could not load font");
	}
}

void MainMenuState::initSounds()
{
	if (!hoverBuffer.loadFromFile("assets/button.wav"))
	{
		std::cout << ("Could not load sound");
	}
	if (!clickBuffer.loadFromFile("assets/clicked.wav"))
	{
		std::cout << ("Could not load sound");
	}

	if (!music.openFromFile("assets/menu.wav")) std::cout << "Could not load menu music";
	music.setLooping(true);
	music.play();
}

// Currently unused
void MainMenuState::initKeys() {

}

// EXECUTED EVERY FRAME
bool MainMenuState::update(const float& delTime)
{
	if (music.getStatus() != sf::SoundSource::Status::Playing) music.play();

	if (startTimer > 0) {
		startTimer -= delTime;
	}
	else {
		std::pair<int, int> data = manager->update(delTime, *window);
		switch (data.first) {
		case 0:
			states.push(new GameState(window, keyRef, data.second, states));
			music.stop();
			break;
		case 1:
			music.stop();
			return true;
			break;
		case 2:
			manager->menus.push(new Menu());
			manager->menus.top()->addButton(Button({ 13, 120 }, { 200, 50 }, "Reset Window", 3, 0, font, hoverBuffer, clickBuffer));
			manager->menus.top()->addButton(Button({ 226, 120 }, { 200, 50 }, "Volume Up", 4, 0, font, hoverBuffer, clickBuffer));
			manager->menus.top()->addButton(Button({ 226, 200 }, { 200, 50 }, "Volume Down", 5, 0, font, hoverBuffer, clickBuffer));
			manager->menus.top()->addButton(Button({ 439, 120 }, { 200, 50 }, "FPS Up", 6, 0, font, hoverBuffer, clickBuffer));
			manager->menus.top()->addButton(Button({ 439, 200 }, { 200, 50 }, "FPS Down", 7, 0, font, hoverBuffer, clickBuffer));
			manager->menus.top()->addButton(Button({ 220, 280 }, { 200, 50 }, "Back", 9, 0, font, hoverBuffer, clickBuffer));
			break;
		case 3:
			window->setSize(sf::Vector2u(640, 512));
			break;
		case 4:
			if (State::volume < 100) State::volume += 5;
			music.setVolume(State::volume);
			startTimer = 0.1;
			break;
		case 5:
			if (State::volume > 0) State::volume -= 5;
			music.setVolume(State::volume);
			startTimer = 0.1;
			break;
		case 6:
			if (State::framerate < 240) State::framerate += 5;
			window->setFramerateLimit(State::framerate);
			std::cout << "fps: " << State::framerate << "\t";
			startTimer = 0.1;
			break;
		case 7:
			if (State::framerate > 10) State::framerate -= 5;
			window->setFramerateLimit(State::framerate);
			std::cout << "fps: " << State::framerate << "\t";
			startTimer = 0.1;
			break;
		case 9:
			delete manager->menus.top();
			manager->menus.pop();
			startTimer = 0.25;
		}
	}
	return false;
}

void MainMenuState::render(sf::RenderTarget* target)
{
	window->draw(bgShape);
	manager->render(*window);
}

// Currently unused
void MainMenuState::inputUpdate(const float& delTime)
{
}

// OTHER
void MainMenuState::start()
{
	startTimer = 0.25;
}

void MainMenuState::endState()
{
}
