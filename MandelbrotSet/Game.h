#pragma once

#include "Menu.h"

class Game
{
private: //VARS

	float WIDTH = 1200;
	float HEIGHT = 720;

	Menu *menu = NULL;

	//bools
	bool menuStart = true;
	bool gameStart = false;
	bool podaciOProgrameruStart = false;

	sf::RenderWindow mWindow;
	sf::Event event;

	//States [MainMenu, , Game]
	std::stack<State*> states;


private: //FUNCS

	void updateSFMLEvents();
	void render();
	void update();
	void initStates();

public:

	//CORE
	Game();
	~Game();

	void run();
};

