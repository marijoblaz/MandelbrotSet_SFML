
#pragma once
#include "State.h"
#include <vector>
#include <algorithm>

class theMergeDance : public State
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
	theMergeDance(sf::RenderWindow* window, std::stack<State*>* states);
	~theMergeDance();

	void update();
	void render();
	void updateSFMLevents(sf::Event* event);
};

