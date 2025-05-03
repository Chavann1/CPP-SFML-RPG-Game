#include "MainMenuState.h"
#include "GameState.h"

MainMenuState::MainMenuState(sf::RenderWindow* newWin, std::map<std::string, int>* keyNew, std::stack<State*>& states) : State(newWin, keyNew), states(states) {
	initFonts();
	initSounds();
	startTimer = 0.25;
	manager = new MenuManager();
	manager->menus.push(new Menu());
	manager->menus.top()->addButton(Button({ 40, 120 }, { 200, 50 }, "New Game", 0, 0, font, hoverBuffer, clickBuffer));
	manager->menus.top()->addButton(Button({ 40, 200 }, { 200, 50 }, "Load Game", 0, 1, font, hoverBuffer, clickBuffer));
	manager->menus.top()->addButton(Button({ 40, 280 }, { 200, 50 }, "Quit", 1, 0, font, hoverBuffer, clickBuffer));
	/*
	menu = new Menu();
	menu->addButton(Button({ 100, 100 }, { 200, 50 }, "New Game", 0, font, hoverBuffer, clickBuffer));
	menu->addButton(Button({ 100, 170 }, { 200, 50 }, "Load Game", 1, font, hoverBuffer, clickBuffer));
	menu->addButton(Button({ 100, 240 }, { 200, 50 }, "Quit", 2, font, hoverBuffer, clickBuffer));
	*/

	std::string textureFilename = "menu_bg.png";

	if (!bgTexture.loadFromFile("assets/" + textureFilename)) {
		std::cerr << "Failed to load texture: " << textureFilename << std::endl;
		return;
	}

	bgShape.setTexture(&bgTexture);
	bgShape.setTextureRect(sf::IntRect(sf::Vector2i(0, 0), sf::Vector2i(640, 512)));
	bgShape.setSize(newWin->getView().getSize());

}

MainMenuState::~MainMenuState()
{
}

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
		}
	}
	return false;
	//menu->update(*window);
}

void MainMenuState::render(sf::RenderTarget* target)
{
	window->draw(bgShape);
	manager->render(*window);
	//menu->draw(*window);
}

void MainMenuState::start()
{
	startTimer = 0.25;
}

void MainMenuState::inputUpdate(const float& delTime)
{
}

void MainMenuState::endState()
{
}

void MainMenuState::initKeys() {

}