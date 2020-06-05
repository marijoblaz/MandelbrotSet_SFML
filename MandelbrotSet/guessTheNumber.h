
#pragma once
#include "State.h"
#include <vector>
#include <algorithm>

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


	void initButtons();
	void renderButtons();
	void updateButtons();
	void initShapes();

public:
	guessTheNumber(sf::RenderWindow* window, std::stack<State*>* states);
	~guessTheNumber();

	void update();
	void render();
	void updateSFMLevents(sf::Event* event);
};

