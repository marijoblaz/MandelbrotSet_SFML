#pragma once
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

class UI
{
private:

	int mag;
	sf::Font font;

	sf::Text magText;
	sf::Text iterText;
	sf::Text posText;


	void initFonts();
	void initText();


public:
	UI();
	~UI();

	void render(sf::RenderTarget &target);
	void update();

	void setMagText(int mag);
	void setIterText(int iter);
	void setPosText(double posX, double posY);

};

