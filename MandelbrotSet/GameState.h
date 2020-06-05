#pragma once
#include "Button.h"
#include "State.h"

class GameState : public State
{
private: //VARS

	sf::RenderWindow* mWindow;

	float WIDTH = 1200;
	float HEIGHT = 720;

	//scaled to lie in the Mandelbrot X scale (-2.5, 1))
	double minRe = -2.5, maxRe = 1;
	//scaled to lie in the Mandelbrot X scale (-1, 1))
	double minIm = -1, maxIm = 1;

	//Num of iterations
	int maxIter = 127;
	double zoom = 1.0;


	sf::Image mbSetImage;
	sf::Sprite mbSetSprite;
	sf::Texture mbSetTexture;

	std::string get_timestamp();

	void renderMBSet();
	sf::Color getMendelColor(unsigned int x, unsigned int y);
	double map(double x, double in_min, double in_max, double out_min, double out_max);
	sf::Color linear_interpolation(const sf::Color& v, const sf::Color& u, double a);

public:

	GameState(sf::RenderWindow* window, std::stack<State*>* states);
	~GameState();

	void render();
	void updateSFMLevents(sf::Event *event);
	void update();
};

