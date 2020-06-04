#pragma once
//UI
#include <iostream>
#include <string>
#include <SFML/Graphics.hpp>
#include <cstdlib>
#include <complex>
#include <vector>
#include <stdio.h>

//Time for save
#include <iomanip>
#include <sstream>
#include <chrono>
#include <ctime>

class Menu
{
private:

	sf::RenderWindow* mWindow;
	sf::Font font;

	void initFont();
	void initButtons();
	void renderButtons();
	void updateButtons();

public:
	Menu(sf::RenderWindow* window);
	~Menu();

	void render();
	void update(sf::RenderTarget* target);
};

