#include "State.h"
#include "GameState.h"

State::State(sf::RenderWindow* newWin, std::map<std::string, int>* keyNew)
{
	window = newWin;
	keyRef = keyNew;
}

State::~State()
{
}
