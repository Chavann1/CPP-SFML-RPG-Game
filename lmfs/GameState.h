#pragma once

#include "State.h"
//#include "Player.h"
#include "Door.h"
#include "Room.h"
#include "Hud.h"
#include "MenuManager.h"
#include "Textbox.h"

class GameState : public State
{
private:
	// Variables
	Player* player;
	Room* room;
	Door* curDoor;
	Textbox* textbox;
	float pHp, pM;
	//int pX, pY;
	float pX, pY;
	enum Game_State { active, paused, over, waiting };
	Game_State gState;
	int save;
	bool darknessOn;
	sf::Clock inDelay;

	// Methods
	void initKeys();
	/*
	void initFonts();
	void initSounds();
	*/

public:
	// Variables
	std::stack<State*>& states;
	MenuManager* manager;
	Hud* hud;
	std::map<int, bool> completion;
	std::map<int, int> npcStates;
	sf::Font font;
	sf::SoundBuffer hoverBuffer, clickBuffer, hurtBuffer;
	sf::Texture gameOverTexture;
	sf::RectangleShape pauseBg;
	sf::RenderTexture darkness;
	sf::RectangleShape gameOverShape;
	sf::Music music;
	sf::Music gameOverMusic;
	int roomId = 1;
	int musicId;

	// Co/De -structors
	virtual ~GameState();
	GameState(sf::RenderWindow* newWin, std::map<std::string, int>* keyNew, int save, std::stack<State*>& states);

	// Initialization
	void initFonts();
	void initSounds();

	// Eecuted every frame
	virtual void inputUpdate(const float& delTime);
	void render(sf::RenderTarget* target);
	bool update(const float& delTime);

	// Other
	void clear();
	void playMusic();
	void start();
	void endState();
	void loadSave(int save);
	void saveSave(int save);
	void loadRoom(int id, sf::Vector2f playerPos);
};

