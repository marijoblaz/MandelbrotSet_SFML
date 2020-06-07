#pragma once
#include "State.h"
#include <unordered_set>
#include <unordered_map>

class GameEditor : public State
{
private:

	sf::RenderWindow* mWindow;

	std::map<std::string, Button*> buttons;
	
	sf::Font font;
	//ColorMag
	sf::RectangleShape colorFinderShape;

	//Image
	sf::Image image;

	//bools
	bool colorPicked = false;
	bool firstStart = true;

	//RGB mouse text
	sf::Text RGBText;
	sf::Text infoText;

	sf::Sprite mbSetSprite;
	sf::Texture mbSetTexture;

	//For debouncing buttons
	sf::Clock clock; // starts the clock
	sf::Time elapsed1;
	int interval = 250;

	//Mouse pos
	sf::Vector2i mousePosScreen;
	sf::Vector2i mousePosWindow;
	sf::Vector2f mousePosView;

	//Koritisim unordered_set. 
	std::unordered_set <int> redColorSet;
	std::unordered_set <int> greenColorSet;
	std::unordered_set <int> blueColorSet;

	sf::Text redColorCount;
	sf::Text greenColorCount;
	sf::Text blueColorCount;

	//Koristim unordered map za color picking
	std::unordered_map<std::string, Button*> colorPickButtons;

	void initButtons();
	void renderButtons();
	void updateButtons();
	void updateMousePos();
	void updateRGBPostions();

	sf::Color pickedColor;
	void changeColor(sf::Color color);

	void initText();
	void countColors();

public:
	GameEditor(sf::RenderWindow* window, std::stack<State*>* states);
	~GameEditor();

	void update();
	void render();
	void updateSFMLevents(sf::Event* event);
};

