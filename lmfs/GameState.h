#pragma once

#include "State.h"

class GameState : public State
{
private:
	void initKeys();
public:
	GameState(sf::RenderWindow* newWin, std::map<std::string, int>* keyNew);
	virtual ~GameState();

	void endState();
	void update(const float& delTime);
	void render(sf::RenderTarget* target);
	virtual void inputUpdate(const float& delTime);

};

