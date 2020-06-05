#pragma once
//UI
#include "GameState.h"
#include "PodaciOProgrameru.h"
#include "State.h"
#include "guessTheNumber.h"
#include "theMergeDance.h"

//Minigames
#include "letsBogo.h"


class Menu : public State
{
private:


	/*
	
	Funkcionalnost 34.	 (Bodova: 2) Osmislite prikladnu funkcionalnost u igri u kojoj koristite map.

							Map koristim kao spremink za buttone
	*/
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

