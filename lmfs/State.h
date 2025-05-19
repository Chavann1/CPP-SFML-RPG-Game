#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/Network.hpp>
#include <SFML/System.hpp>
#include <SFML/Audio.hpp>
#include <fstream>
#include <filesystem>
#include <vector>
#include <stack>
#include <iostream>
#include <map>
#include <unordered_map>
#include <sstream>
#include <string>
#include <regex>
#include <utility>
#include <cstdlib>
#include <cmath>
#include <iterator>

class State
{
protected:
	sf::RenderWindow* window;
	std::vector<sf::Texture*> textures;
	std::map<std::string, int>* keyRef;
	std::map<std::string, int> curKeys;
	float startTimer;

public:
	// Virtual functions
	State(sf::RenderWindow* newWin, std::map<std::string, int>* keyNew);
	virtual ~State();
	virtual void initKeys() = 0;
	virtual void start() = 0;
	virtual void endState() = 0;
	virtual void initFonts() = 0;
	virtual void initSounds() = 0;
	virtual bool update(const float& delTime) = 0;
	virtual void inputUpdate(const float& delTime) = 0;
	virtual void render(sf::RenderTarget* target = nullptr) = 0;

	// Static functions
	static void loadTextureImage(sf::Texture& texture, std::string filename);

};

