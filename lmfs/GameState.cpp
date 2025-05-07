#include "GameState.h"

void GameState::initKeys()
{
	curKeys["UP"] = keyRef->at("UP");
	curKeys["DOWN"] = keyRef->at("DOWN");
	curKeys["LEFT"] = keyRef->at("LEFT");
	curKeys["RIGHT"] = keyRef->at("RIGHT");
	curKeys["ESC"] = keyRef->at("ESC");
	curKeys["ATK"] = keyRef->at("ATK");
	curKeys["INT"] = keyRef->at("INT");
}

GameState::GameState(sf::RenderWindow* newWin, std::map<std::string, int>* keyNew, int save, std::stack<State*>& states) : State(newWin, keyNew), states(states)
{
	initKeys();
	initFonts();
	initSounds();
	loadSave(save);
	player = new Player(pX, pY, pHp, pM, 10.f);
	player->hurtSound = new sf::Sound(hurtBuffer);
	//room = new Room("data/rooms/room1.txt", "data/rooms/roomtext1.txt");
	loadRoom(roomId, sf::Vector2f(pX, pY));
	manager = new MenuManager();

	hud = new Hud(10.f, pM, font);
	player->hud = hud;

	float wid, hei;
	wid = window->getSize().x;
	hei = window->getSize().y;
	pauseBg.setSize(sf::Vector2f(wid, hei));
	pauseBg.setFillColor(sf::Color(0, 0, 0, 128));
	pauseBg.setOrigin(sf::Vector2f(0, 0));
	pauseBg.setPosition(sf::Vector2f(0, 0));

	std::string textureFilename = "game_over.png";
	if (!gameOverTexture.loadFromFile("assets/" + textureFilename)) {
		std::cerr << "Failed to load texture: " << textureFilename << std::endl;
		return;
	}

	gameOverShape.setTexture(&gameOverTexture);
	gameOverShape.setTextureRect(sf::IntRect(sf::Vector2i(0, 0), sf::Vector2i(182, 37)));
	//gameOverShape.setSize(newWin->getView().getSize());
	gameOverShape.setSize(sf::Vector2f(364.f, 74.f));
	gameOverShape.setPosition(sf::Vector2f(160.f, 50.f));
}

GameState::~GameState()
{
	delete player;
}

void GameState::loadRoom(int id, sf::Vector2f playerPos)
{
	player->teleport(playerPos);
	//player->pState = Player::wait;
	roomId = id;
	std::string name1, name2;
	name1 = "data/rooms/room" + std::to_string(id) + ".txt";
	name2 = "data/rooms/roomtext" + std::to_string(id) + ".txt";
	bool completed = true;
	if (completion.find(id) == completion.end()) {
		completed = false;
	}
	if (room != nullptr) delete room;
	room = new Room(name1, name2, completed);
	player->eManager = room->getEManager();
}

void GameState::endState()
{
}

bool GameState::update(const float& delTime)
{
	if (gState != over) {
		if (music.getStatus() != sf::SoundSource::Status::Playing) music.play();
	}
	if (gState == paused) {
		std::pair<int, int> data = manager->update(delTime, *window);
		switch (data.first) {
		case 0:
			return true;
			break;
		}
	} else if (gState == active) {
		player->update();
		if (room->update(delTime)) {
			completion[roomId] = true;
		}
	} else {
		std::pair<int, int> data = manager->update(delTime, *window);
		switch (data.first) {
		case 0:
			return true;
			break;
		}
	}
	if (player->pState == Player::dead && player->frame >= 3) {
		if (gState != over) {
			gState = over;
			music.stop();
			if(!music.openFromFile("assets/game_over.wav")) std::cout << "Could not load game over music";
			music.setLooping(true);
			music.play();
			manager->menus.push(new Menu());
			manager->menus.top()->addButton(Button({ 220, 200 }, { 200, 50 }, "Restart", 0, 0, font, hoverBuffer, clickBuffer));
			manager->menus.top()->addButton(Button({ 220, 300 }, { 200, 50 }, "Menu", 0, 0, font, hoverBuffer, clickBuffer));
		}
	}
	return false;
}

void GameState::initFonts()
{
	if (!this->font.openFromFile("assets/Retro_Gaming.ttf"))
	{
		std::cout << ("Could not load font");
	}
}

void GameState::start()
{
	startTimer = 0.25;
}

void GameState::initSounds()
{
	if (!hoverBuffer.loadFromFile("assets/button.wav"))
	{
		std::cout << ("Could not load sound");
	}
	if (!clickBuffer.loadFromFile("assets/clicked.wav"))
	{
		std::cout << ("Could not load sound");
	}
	if (!hurtBuffer.loadFromFile("assets/player_hurt.wav"))
	{
		std::cout << ("Could not load sound");
	}

	if (!music.openFromFile("assets/level_1.wav")) std::cout << "Could not load level music";
	music.setLooping(true);
	music.play();
}

void GameState::render(sf::RenderTarget* target)
{
	
	room->render(*window);
	// remove * if reverted
	window->draw(*(player->shape));
	player->animate();
	if (gState == paused || gState == over) {
		window->draw(pauseBg);
	}
	if (gState == over) {
		window->draw(gameOverShape);
	}
	if(!manager->menus.empty()) manager->render(*window);
	hud->draw(*window);
}

void GameState::loadSave(int save)
{
	std::string name = "data/saves/save" + std::to_string(save)+ ".txt";
	std::ifstream inFile(name);

	std::regex rexp("\\d+");
	if (inFile.is_open()) {
		inFile >> roomId >> pHp >> pM >> pX >> pY;
		std::string line;
		while (inFile >> line) {
			if (line == "end") break;
			if (std::regex_match(line, rexp)) {
				completion[std::stoi(line)] = true;
			}
		}
	}
	else std::cout << "Failed to open file " << name;

}

void GameState::inputUpdate(const float& delTime)
{
	if (startTimer < 0) {
		if (gState == active) {
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(curKeys["ESC"]))) {
				manager->menus.push(new Menu());
				manager->menus.top()->addButton(Button({ 220, 100 }, { 200, 50 }, "Menu", 0, 0, font, hoverBuffer, clickBuffer));
				manager->menus.top()->addButton(Button({ 220, 200 }, { 200, 50 }, "Save", 0, 0, font, hoverBuffer, clickBuffer));
				
				//paused = true;
				gState = paused;
				start();
			}
			// PLAYER CONTROLS
			if (player->pState != Player::dead) {
				sf::Vector2f vec;
				if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(curKeys["UP"]))) {
					vec.y = -1;
					player->dir = 2;
				}
				if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(curKeys["DOWN"]))) {
					vec.y = 1;
					player->dir = 0;
				}
				if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(curKeys["LEFT"]))) {
					vec.x = -1;
					player->dir = 3;
				}
				if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(curKeys["RIGHT"]))) {
					vec.x = 1;
					player->dir = 1;
				}
				curDoor = player->movement(vec, delTime, room->getCollisionRects(), room->doors);
				if (curDoor != nullptr) {
					loadRoom(curDoor->destinationRoomId, curDoor->destinationPosition);
				}
				// PLAYER ATTACK
				if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(curKeys["ATK"]))) {
					player->attack();
				}
			}
		}
		else if(gState == paused){
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(curKeys["ESC"]))) {
				while (!(manager->menus.empty())) {
					delete manager->menus.top();
					manager->menus.pop();
				}
				//paused = false;
				gState = active;
				start();
			}
		}
	}
	else {
		startTimer -= delTime;
	}
}
