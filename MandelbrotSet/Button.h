#pragma once

#include <iostream>
#include <ctime>
#include <cstdlib>
#include <stack>

#include <string>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <cstdlib>
#include <complex>
#include <vector>
#include <stdio.h>

//Time for save
#include <iomanip>
#include <sstream>
#include <chrono>
#include <ctime>

enum button_states
{
	BTN_IDLE = 0,
	BTN_PRESSED,
	BTN_HOVERED
};

enum button_style
{
	BTN_STANDARD = 0,
	BTN_TOGGLE
};

class Button
{
private:

	short unsigned buttonState;
	short unsigned buttonStyle;

	bool toogle = false;

	sf::Clock clock; // starts the clock
	sf::Time elapsed1;

	sf::RenderWindow* window;

	//init standard shape
	sf::RectangleShape bShape;

	//init toogle shape
	sf::CircleShape bShapeCirc;

	//init text/font
	sf::Font* font;
	sf::Text text;


	//Button colors
	sf::Color idleColor;
	sf::Color hoverColor;
	sf::Color pressColor;

	//Mouse pos
	sf::Vector2i mousePosScreen;
	sf::Vector2i mousePosWindow;
	sf::Vector2f mousePosView;


public:
	Button(float x, float y, float width, float height, sf::Font* font, std::string text, sf::Color idleColor, sf::Color pressColor, sf::Color hoverColor, sf::RenderWindow* window, short unsigned style);
	virtual ~Button();

	//funs
	void render(sf::RenderTarget* target);
	void updateMousePos();
	void updatePress();

	//getter
	const bool isPressed() const;

};

