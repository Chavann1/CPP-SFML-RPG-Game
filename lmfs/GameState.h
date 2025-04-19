#pragma once

#include "State.h"
#include "Player.h"
#include "Door.h"
#include "Room.h"
#include "MenuManager.h"

class GameState : public State
{
private:
	void initKeys();
	Player* player;
	Room* room;
	Door* curDoor;
	float pHp, pM;
	int pX, pY;
	bool paused = false;
public:
	std::stack<State*>& states;
	sf::Font font;
	sf::SoundBuffer hoverBuffer, clickBuffer;
	std::map<int, bool> completion;
	int roomId = 1;
	GameState(sf::RenderWindow* newWin, std::map<std::string, int>* keyNew, int save, std::stack<State*>& states);
	virtual ~GameState();

	void loadRoom(int id, sf::Vector2f playerPos);
	void endState();
	bool update(const float& delTime);
	void initFonts();
	void start();
	void initSounds();
	void render(sf::RenderTarget* target);
	void loadSave(int save);
	virtual void inputUpdate(const float& delTime);
	MenuManager* manager;

};

