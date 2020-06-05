#pragma once
//UI
#include "GameState.h"
#include "PodaciOProgrameru.h"
#include "State.h"


class Menu : public State
{
private:

	std::map<std::string, Button*> buttons;

	sf::RenderWindow* mWindow;
	sf::Font font;

	//Text
	sf::Text gameNameText;

	//Background
	sf::Texture backgroundTexture;
	sf::Sprite backgroundSprite;

	//Quit
	bool meQuit = false;
	bool startGame = false;
	bool startPodacioProgrameru = false;

	void initFont();
	void initButtons();
	void renderButtons();
	void updateButtons();
	void initGameNameText();
	void initBackground();


public:
	Menu(sf::RenderWindow* window, std::stack<State*>* states);
	~Menu();

	void render();
	void update();

	//inde
	void updateSFMLevents(sf::Event* event);
};

