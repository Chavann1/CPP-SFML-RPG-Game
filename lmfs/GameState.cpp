#include "GameState.h"

void GameState::initKeys()
{
	curKeys["UP"] = keyRef->at("UP");
	curKeys["DOWN"] = keyRef->at("DOWN");
	curKeys["LEFT"] = keyRef->at("LEFT");
	curKeys["RIGHT"] = keyRef->at("RIGHT");
}

GameState::GameState(sf::RenderWindow* newWin, std::map<std::string, int>* keyNew) : State(newWin, keyNew)
{
	initKeys();
}

GameState::~GameState()
{
}

void GameState::endState()
{
}

void GameState::update(const float& delTime)
{
	
}

void GameState::render(sf::RenderTarget* target)
{
}

void GameState::inputUpdate(const float& delTime)
{
	
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(curKeys["UP"]))) {
		std::cout << "UP ";
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(curKeys["DOWN"]))) {
		std::cout << "DOWN ";
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(curKeys["LEFT"]))) {
		std::cout << "LEFT ";
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(curKeys["RIGHT"]))){
		std::cout << "RIGHT ";
	}
}
