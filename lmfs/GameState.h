#pragma once

#include "State.h"
#include "Player.h"
#include "Door.h"
#include "Room.h"
#include "Hud.h"
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
	enum Game_State { active, paused, over };
	Game_State gState;
	//bool paused = false;
public:
	std::stack<State*>& states;
	sf::Font font;
	sf::SoundBuffer hoverBuffer, clickBuffer, hurtBuffer;
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
	sf::Texture gameOverTexture;
	sf::RectangleShape pauseBg;
	sf::RectangleShape gameOverShape;
	MenuManager* manager;
	sf::Music music;
	sf::Music gameOverMusic;
	Hud* hud;
};

