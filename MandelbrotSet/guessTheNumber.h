
#pragma once
#include "State.h"
#include <vector>
#include <algorithm>
#include <sstream> 
#include <random>
#include <chrono>

class guessTheNumber : public State
{
private:

	sf::RenderWindow* mWindow;
	std::map<std::string, Button*> buttons;

	//Font for buttons
	sf::Font font;

	//Background
	sf::Texture backgroundTexture;
	sf::Sprite backgroundSprite;

	//Input
	sf::String playerInput;
	sf::Text infoText;
	sf::Text actualTimeText;
	sf::Text missedTimeText;
	int guessTime = 0;
	int actualTime = 0;
	sf::Text playerText;
	bool trazi = false;


	//Random num and Text
	int randNum = 0;
	sf::Text generatedRandNumText;
	std::vector<int> vektorIntova;

	//InputBackgroun
	sf::RectangleShape inputBackground;
	sf::RectangleShape inputBackground2;
	sf::RectangleShape inputBackground3;
	sf::RectangleShape inputBackground4;

	void initButtons();
	void renderButtons();
	void updateButtons();
	void initShapes();
	void napuniVektor();
	void razbacajVektor();
	void sortirajVektor();
	void trazimSedam();

public:
	guessTheNumber(sf::RenderWindow* window, std::stack<State*>* states);
	~guessTheNumber();

	void update();
	void render();
	void updateSFMLevents(sf::Event* event);
};

