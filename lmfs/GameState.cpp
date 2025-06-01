#include "GameState.h"

// CO/DE -STRUCTORS
GameState::GameState(sf::RenderWindow* newWin, std::map<std::string, int>* keyNew, int save, std::stack<State*>& states) : State(newWin, keyNew), states(states), save(save)
{
	// Initialization functions
	initKeys();
	initFonts();
	initSounds();
	loadSave(save);

	// Create Player
	player = new Player(pX, pY, pHp, pM, 10.f);
	player->hurtSound = new sf::Sound(hurtBuffer);

	loadRoom(roomId, sf::Vector2f(pX, pY));
	darknessOn = room->darknessOn;
	musicId = room->musicId;
	playMusic();
	manager = new MenuManager();

	// Create Hud
	hud = new Hud(10.f, pM, font);
	player->hud = hud;
	hud->updateHp(pHp, 10.f);

	// Create overlay, which is visible when paused
	float wid, hei;
	wid = window->getSize().x;
	hei = window->getSize().y;
	pauseBg.setSize(sf::Vector2f(wid, hei));
	pauseBg.setFillColor(sf::Color(0, 0, 0, 128));
	pauseBg.setOrigin(sf::Vector2f(0, 0));
	pauseBg.setPosition(sf::Vector2f(0, 0));

	// Other
	textbox = new Textbox(font, sf::Vector2f(wid, hei / 3), sf::Vector2f(0.f, hei*2/3));
	darkness.resize(window->getSize());
	darkness.clear(sf::Color(0, 0, 0, 128));

	// Initialize game over screen image
	std::string textureFilename = "game_over.png";
	if (!gameOverTexture.loadFromFile("assets/" + textureFilename)) {
		std::cerr << "Failed to load texture: " << textureFilename << std::endl;
		return;
	}

	gameOverShape.setTexture(&gameOverTexture);
	gameOverShape.setTextureRect(sf::IntRect(sf::Vector2i(0, 0), sf::Vector2i(182, 37)));
	gameOverShape.setSize(sf::Vector2f(364.f, 74.f));
	gameOverShape.setPosition(sf::Vector2f(160.f, 50.f));

	inDelay.restart();
	gState = active;
}

GameState::~GameState()
{
	//delete player;
}

// INITIALIZATION METHODS
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

void GameState::initFonts()
{
	if (!this->font.openFromFile("assets/Retro_Gaming.ttf"))
	{
		std::cout << ("Could not load font");
	}
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

	//if (!music.openFromFile("assets/level_1.wav")) std::cout << "Could not load level music";
	//music.setLooping(true);
	//music.play();
}

// FUNCTIONS EXECUTED EVERY FRAME
bool GameState::update(const float& delTime)
{
	// If Game is not over keep playing music
	if (gState != over) {
		if (music.getStatus() != sf::SoundSource::Status::Playing) music.play();
	}
	if (gState == paused) {
		// Manage returns from the pause menu
		std::pair<int, int> data = manager->update(delTime, *window);

		switch (data.first) {
		// MENU
		case 0:
			return true;
			break;
		// SAVE
		case 1:
			saveSave(save);
			break;
		default:
			break;
		}
	} else if (gState == active) {
		player->update();
		if (room->update(delTime)) {
			completion[roomId] = true;
		}
	} else  if (gState == over){
		// Manage returns from game over menu
		std::pair<int, int> data = manager->update(delTime, *window);
		switch (data.first) {
		// MENU
		case 0:
			// End Game, return to main menu
			return true;
			break;
		// RESTART
		case 1:
			// Cleanup
			delete player;
			completion.clear();
			while (!(manager->menus.empty())) {
				delete manager->menus.top();
				manager->menus.pop();
			}

			// Initialize music
			//if (!music.openFromFile("assets/level_1.wav")) std::cout << "Could not load level music";
			//music.setLooping(true);
			//music.play();

			// Reload save
			loadSave(save);

			// Create Player
			player = new Player(pX, pY, pHp, pM, 10.f);
			player->hurtSound = new sf::Sound(hurtBuffer);

			hud->updateHp(pHp, 10.f);

			// Reload room
			loadRoom(roomId, sf::Vector2f(pX, pY));
			darknessOn = room->darknessOn;
			musicId = room->musicId;
			playMusic();
			player->hud = hud;
			gState = active;
			break;
		default:
			break;
		}
	}

	// If player death animation finished, initiate game over
	if (player->pState == Player::dead && player->frame >= 3) {
		if (gState != over) {
			gState = over;
			music.stop();
			if (!music.openFromFile("assets/game_over.wav")) std::cout << "Could not load game over music";
			music.setLooping(true);
			music.play();
			manager->menus.push(new Menu());
			manager->menus.top()->addButton(Button({ 220, 200 }, { 200, 50 }, "Restart", 1, 0, font, hoverBuffer, clickBuffer));
			manager->menus.top()->addButton(Button({ 220, 300 }, { 200, 50 }, "Menu", 0, 0, font, hoverBuffer, clickBuffer));
		}
	}
	return false;
}

void GameState::render(sf::RenderTarget* target)
{
	
	room->render(*window);
	// Debugging draws
	//window->draw((player->hitbox));
	if (player->sword != nullptr) {
		//window->draw(player->sword->szejp);
	}

	window->draw(*(player->shape));
	player->animate();

	if (gState == paused || gState == over) {
		window->draw(pauseBg);
	}
	if (gState == over) {
		window->draw(gameOverShape);
	}
	
	if (darknessOn) {
		// Darkness effect
		darkness.clear(sf::Color(0, 0, 0, 96));
		darkness.draw(player->lightHole2, sf::BlendNone);
		room->addLights(darkness);
		darkness.draw(player->lightHole, sf::BlendNone);
		darkness.display();
		sf::Sprite darknessSprite(darkness.getTexture());
		window->draw(darknessSprite, sf::BlendAlpha);
	}

	if (!manager->menus.empty()) manager->render(*window);
	if (hud != nullptr) hud->draw(*window);
	if (textbox != nullptr) textbox->draw(*window);

}

void GameState::inputUpdate(const float& delTime)
{
	if (startTimer < 0) {
		if (gState == active) {
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(curKeys["ESC"]))) {
				manager->menus.push(new Menu());
				manager->menus.top()->addButton(Button({ 220, 100 }, { 200, 50 }, "Menu", 0, 0, font, hoverBuffer, clickBuffer));
				manager->menus.top()->addButton(Button({ 220, 200 }, { 200, 50 }, "Save", 1, 0, font, hoverBuffer, clickBuffer));

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
					darknessOn = room->darknessOn;
					if (musicId != room->musicId) {
						musicId = room->musicId;
						playMusic();
					}
				}
				// PLAYER ATTACK
				if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(curKeys["ATK"]))) {
					player->attack();
				}
				// INTERACTION
				if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(curKeys["INT"]))) {
					if (inDelay.getElapsedTime() >= sf::milliseconds(200)) {
						for (const auto& p : room->interacts) {
							if (player->interactCheck(p->getBounds())) {
								gState = waiting;
								inDelay.restart();
								p->interact(*player, *textbox);
							}
						}
					}
				}
			}
		}
		else if (gState == paused) {
			// Clearing pause menu
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(curKeys["ESC"]))) {
				while (!(manager->menus.empty())) {
					delete manager->menus.top();
					manager->menus.pop();
				}
				gState = active;
				start();
			}
		}
		else if (gState == waiting) {
			if (inDelay.getElapsedTime() >= sf::milliseconds(200)) {
				if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(curKeys["INT"]))) {
					textbox->next();
					if (textbox->isFinished()) gState = active;
					inDelay.restart();
				}
			}
		}
	}
	else {
		startTimer -= delTime;
	}
}

// OTHER FUNCTIONS
void GameState::loadRoom(int id, sf::Vector2f playerPos)
{
	player->teleport(playerPos);
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

void GameState::loadSave(int save)
{
	std::string name = "data/saves/save" + std::to_string(save) + ".txt";
	std::ifstream inFile(name);

	std::regex rexp("\\d+");
	if (inFile.is_open()) {
		inFile >> roomId >> pHp >> pM >> pX >> pY;
		std::string line;
		while (inFile >> line) {
			if (line == "end") break;
			// Check if they are numbers
			if (std::regex_match(line, rexp)) {
				completion[std::stoi(line)] = true;
			}
		}
	}
	else std::cout << "Failed to open file " << name;
	inFile.close();
}

void GameState::saveSave(int save)
{
	std::string name = "data/saves/save" + std::to_string(1) + ".txt";
	std::ofstream outFile;
	outFile.open(name, std::ofstream::out | std::ofstream::trunc);

	if (outFile.is_open()) {
		// room id, hp, money, x, y
		outFile << roomId << std::endl;
		outFile << player->hp << std::endl;
		outFile << player->money << std::endl;
		outFile << player->shape->getPosition().x << std::endl;
		outFile << player->shape->getPosition().y << std::endl;

		for (auto p : completion) {
			if (p.second == true) {
				outFile << p.first << std::endl;
			}
		}
		outFile << "end";
	}
	else std::cout << "Failed to open file " << name;
	outFile.close();
}

void GameState::clear()
{
	//delete player;
	completion.clear();
	while (!(manager->menus.empty())) {
		delete manager->menus.top();
		manager->menus.pop();
	}
}

void GameState::playMusic()
{
	switch (musicId) {
	case 0:
		if (!music.openFromFile("assets/outside.wav")) std::cout << "Could not load level music";
		break;
	default:
		if (!music.openFromFile("assets/level_1.wav")) std::cout << "Could not load level music";
		break;
	}
	music.setLooping(true);
	music.play();
}

// TO BE REMOVED
void GameState::start()
{
	startTimer = 0.25;
}