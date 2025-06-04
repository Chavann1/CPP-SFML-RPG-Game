#include "Hud.h"

Hud::Hud(float max_hp, float money, const sf::Font& font): moneyNum(font, std::to_string(money).substr(0, 4), 16) {
	std::string textureFilename = "hp_hud_empty.png";

	if (!hpEmptyTexture.loadFromFile("assets/" + textureFilename)) {
		std::cerr << "Failed to load texture: " << textureFilename << std::endl;
		return;
	}

	textureFilename = "hp_hud.png";

	if (!hpFullTexture.loadFromFile("assets/" + textureFilename)) {
		std::cerr << "Failed to load texture: " << textureFilename << std::endl;
		return;
	}

	textureFilename = "money_hud.png";

	if (!moneyTexture.loadFromFile("assets/" + textureFilename)) {
		std::cerr << "Failed to load texture: " << textureFilename << std::endl;
		return;
	}

	int id = 0;
	for (float i = 0; i < max_hp; i += 1) {
		sf::RectangleShape shape;
		shape.setOrigin(sf::Vector2f(0.f, 0.f));
		shape.setTextureRect(sf::IntRect(sf::Vector2i(0, 0), sf::Vector2i(11, 10)));
		shape.setSize(sf::Vector2f(22.f, 20.f));
		shape.setTexture(&hpFullTexture);
		shape.setPosition(sf::Vector2f(16 + 24 * i, 16));
		hearts.push_back(std::make_pair(shape, id));
		id++;
	}

	moneyIcon.setOrigin(sf::Vector2f(0.f, 0.f));
	moneyIcon.setTextureRect(sf::IntRect(sf::Vector2i(0, 0), sf::Vector2i(18, 24)));
	moneyIcon.setSize(sf::Vector2f(36.f, 48.f));
	moneyIcon.setTexture(&moneyTexture);
	moneyIcon.setPosition(sf::Vector2f(18.f, 48.f));

	/*
	moneyNum = new sf::Text(font);
	moneyNum->setString(std::to_string(money).substr(0, 4));
	moneyNum->setCharacterSize(16);
	moneyNum->setOutlineColor(sf::Color::Black);
	moneyNum->setOutlineThickness(2);
	moneyNum->setFillColor(sf::Color::White);
	moneyNum->setOrigin(sf::Vector2f(0, 0));
	moneyNum->setPosition(sf::Vector2f(48.f, 48.f));
	*/
	
	moneyNum.setOutlineColor(sf::Color::Black);
	moneyNum.setOutlineThickness(2);
	moneyNum.setFillColor(sf::Color::White);
	moneyNum.setOrigin(sf::Vector2f(0, 0));
	moneyNum.setPosition(sf::Vector2f(48.f, 48.f));

}

Hud::~Hud()
{
	//delete moneyNum;
}

void Hud::draw(sf::RenderWindow& window)
{
	for (auto p : hearts) {
		window.draw(p.first);
	}
	window.draw(moneyIcon);
	//window.draw(*moneyNum);
	window.draw(moneyNum);
}

void Hud::updateHp(float hp, float max_hp)
{
	for (auto& p : hearts) {
		if (p.second >= hp) {
			p.first.setTexture(&hpEmptyTexture);
		}
		else {
			p.first.setTexture(&hpFullTexture);
		}
	}
}

void Hud::updateMoney(float money)
{
	moneyNum.setString(std::to_string(money).substr(0, 4));
}
