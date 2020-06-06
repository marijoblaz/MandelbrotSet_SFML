#pragma once
#include "Button.h"
#include "State.h"

#include <fstream>
#include <queue>

class GameState : public State
{
private: //VARS

	sf::RenderWindow* mWindow;

	//For debouncing buttons
	sf::Clock clock; // starts the clock
	sf::Time elapsed1;
	int interval = 250;

	//Koristim map
	std::map<std::string, Button*> buttons;

	//Koristim multimap
	

	//color presets
	const std::vector<sf::Color> colorsPreset1{
	{0,0,40},
	{51,67,31},
	{111,180,121},
	{62,123,89},
	{43,50,118},
	{0,55,180},
	{20,0,20},
	};
	const std::vector<sf::Color> colorsPreset2{
	{255,0,40},
	{213,67,31},
	{51,255,121},
	{62,123,89},
	{43,50,118},
	{0,55,247},
	{100,0,0},
	};
	const std::vector<sf::Color> colorsPreset3{
	{0,255,40},
	{213,67,31},
	{251,255,121},
	{62,123,89},
	{43,50,118},
	{0,55,247},
	{100,0,0},
	};

	std::vector<sf::Color> colorsPresetActive;

	//Font for buttons
	sf::Font font;

	//Save location
	std::ofstream mySaveFile;

	//bools
	bool autoIterations = true;

	float WIDTH = 1200;
	float HEIGHT = 720;

	//scaled to lie in the Mandelbrot X scale (-2.5, 1))
	double minRe = -2.5, maxRe = 1;
	//scaled to lie in the Mandelbrot X scale (-1, 1))
	double minIm = -1, maxIm = 1;

	//LocationText
	sf::Text locationText;

	//Num of iterations
	int maxIter = 50;

	//Korisitim set
	std::set<int, std::greater <int>> maxIterations;
	sf::Text currentIterationsText;
	sf::Text maxIterationsText;

	//Koristim multyset
	std::multiset<std::vector<double>> locations;
	std::vector<double> locationCord;

	sf::Image mbSetImage;
	sf::Sprite mbSetSprite;
	sf::Texture mbSetTexture;

	std::string get_timestamp();

	void renderMBSet();
	sf::Color getMendelColor(unsigned int x, unsigned int y);
	double map(double x, double in_min, double in_max, double out_min, double out_max);
	sf::Color linear_interpolation(const sf::Color& v, const sf::Color& u, double a);

	//buttons
	void initButtons();
	void initText();
	void renderButtons();
	void updateButtons();
	void updateMaxIterationsText();

	//locations
	void updateLocations();
	void zoomIn(bool overRide);
	void zoomOut(bool overRide);

	//analyse image

	//Using priority_queue to store most intresing places
	std::priority_queue <int> intrestingValues;
	sf::Color piexelColor;
	unsigned long long colorCount = 0;
	sf::Text analysedImageText;
	sf::Text analysedImageText2;
	int getImageAnalyse();


public:

	GameState(sf::RenderWindow* window, std::stack<State*>* states);
	~GameState();

	void render();
	void updateSFMLevents(sf::Event *event);
	void update();
};

