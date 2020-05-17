#pragma once
//UI
#include "UI.h"

class Render
{
private: //VARS

	float WIDTH = 1920;
	float HEIGHT = 1080;

	//scaled to lie in the Mandelbrot X scale (-2.5, 1))
	double minRe = -2.5, maxRe = 1;
	//scaled to lie in the Mandelbrot X scale (-1, 1))
	double minIm = -1, maxIm = 1;

	//Num of iterations
	int maxIter = 100;
	double zoom = 1.0;

	sf::RenderWindow mWindow;

	sf::Image mbSetImage;
	sf::Sprite mbSetSprite;
	sf::Texture mbSetTexture;

	UI* ui;

	int scale = 1;

private: //FUNCS

	void updateSFMLEvents();
	void render();
	void update();
	std::string get_timestamp();

	void renderMBSet();
	sf::Color getMendelColor(unsigned int x, unsigned int y);
	double map(double x, double in_min, double in_max, double out_min, double out_max);
	sf::Color linear_interpolation(const sf::Color& v, const sf::Color& u, double a);

public:

	//CORE
	Render();
	~Render();

	void run();
};

