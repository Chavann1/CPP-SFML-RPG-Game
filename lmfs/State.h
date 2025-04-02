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

class State
{
protected:
	sf::RenderWindow* window;
	std::vector<sf::Texture*> textures;
	std::map<std::string, int>* keyRef;
	std::map<std::string, int> curKeys;

public:
	State(sf::RenderWindow* newWin, std::map<std::string, int>* keyNew);
	virtual ~State();
	virtual void initKeys() = 0;
	virtual void endState() = 0;
	virtual void update(const float& delTime)=0;
	virtual void inputUpdate(const float& delTime) = 0;
	virtual void render(sf::RenderTarget* target = nullptr)=0;

};

