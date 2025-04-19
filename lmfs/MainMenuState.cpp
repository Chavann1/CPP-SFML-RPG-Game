#include "MainMenuState.h"
#include "GameState.h"

MainMenuState::MainMenuState(sf::RenderWindow* newWin, std::map<std::string, int>* keyNew, std::stack<State*>& states) : State(newWin, keyNew), states(states) {
	initFonts();
	startTimer = 0.25;
	manager = new MenuManager();
	manager->menus.push(new Menu());
	manager->menus.top()->addButton(Button({ 100, 100 }, { 200, 50 }, "New Game", 0, 0, font, hoverBuffer, clickBuffer));
	manager->menus.top()->addButton(Button({ 100, 170 }, { 200, 50 }, "Load Game", 0, 1, font, hoverBuffer, clickBuffer));
	manager->menus.top()->addButton(Button({ 100, 240 }, { 200, 50 }, "Quit", 1, 0, font, hoverBuffer, clickBuffer));
	
	/*
	menu = new Menu();
	menu->addButton(Button({ 100, 100 }, { 200, 50 }, "New Game", 0, font, hoverBuffer, clickBuffer));
	menu->addButton(Button({ 100, 170 }, { 200, 50 }, "Load Game", 1, font, hoverBuffer, clickBuffer));
	menu->addButton(Button({ 100, 240 }, { 200, 50 }, "Quit", 2, font, hoverBuffer, clickBuffer));
	*/
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
	if (!this->hoverBuffer.loadFromFile("assets/button.mp3"))
	{
		std::cout << ("Could not load sound");
	}
	clickBuffer.loadFromFile("assets/clicked.mp3");
}

bool MainMenuState::update(const float& delTime)
{
	if (startTimer > 0) {
		startTimer -= delTime;
	}
	else {
		std::pair<int, int> data = manager->update(delTime, *window);
		switch (data.first) {
		case 0:
			states.push(new GameState(window, keyRef, data.second, states));
			break;
		}
	}
	return false;
	//menu->update(*window);
}

void MainMenuState::render(sf::RenderTarget* target)
{
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