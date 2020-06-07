#pragma once
#include "Button.h"
#include "State.h"
#include "GameEditor.h"

#include <fstream>
#include <queue>
#include <unordered_set>

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

	//Background
	sf::Texture backgroundHelpTexture;
	sf::Sprite backgroundHelpSprite;

	bool helpExit = false;

	//color presets
	const std::vector<sf::Color> colorsPreset1{
	{0, 0, 1},
	{25, 7, 26},
	{9, 1, 47},
	{4, 4, 73},
	{0, 7, 100},
	{12, 44, 138},
	{24, 82, 177},
	{57, 125, 209},
	{134, 181, 229},
	{211, 236, 248},
	{241, 233, 191},
	{248, 201, 95},
	{255, 170, 0},
	{204, 128, 0},
	{153, 87, 0},
	{106, 52, 3}
	};

	const std::vector<sf::Color> colorsPreset2{
	{10, 0, 0},
	{25, 7, 26},
	{9, 1, 47},
	{44, 4, 73},
	{44, 47, 100},
	{12, 44, 138},
	{124, 82, 177},
	{25, 55, 209},
	{134, 121, 29},
	{111, 26, 248},
	{241, 203, 191},
	{148, 31, 95},
	{155, 170, 0},
	{204, 128, 0},
	{153, 87, 0},
	{106, 52, 3}
	};

	const std::vector<sf::Color> colorsPreset3{
	{0, 10, 0},
	{25, 7, 26},
	{9, 1, 47},
	{4, 40, 73},
	{0, 70, 100},
	{12, 40, 38},
	{24, 82, 177},
	{57, 125, 209},
	{34, 191, 29},
	{211, 236, 248},
	{241, 73, 191},
	{248, 201, 95},
	{255, 10, 33},
	{4, 128, 99},
	{53, 127, 66},
	{106, 52, 3}
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

	//Koristim multiset
	std::multiset<std::vector<double>> locations;
	std::vector<double> locationCord;

	sf::Image mbSetImage;
	sf::Sprite mbSetSprite;
	sf::Texture mbSetTexture;

	//RED
	sf::Image mbSetImageScaled;
	sf::Sprite mbSetSpriteScaled;
	sf::Texture mbSetTextureScaled;

	//GREEN
	sf::Image mbSetImageScaled1;
	sf::Sprite mbSetSpriteScaled1;
	sf::Texture mbSetTextureScaled1;

	//BLUE
	sf::Image mbSetImageScaled2;
	sf::Sprite mbSetSpriteScaled2;
	sf::Texture mbSetTextureScaled2;

	sf::Text infoText;

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

	void miniRedImage();
	void miniGreenImage();
	void miniBlueImage();

	//analyse image using multimap Koristim multimap
	std::multimap <int, int> intValueAndIterationMM;

	//Using priority_queue to store most intresing places
	std::priority_queue <int> intrestingValues;

	//Using unordered multiset to save and display r g b values trough out the image
	std::unordered_multiset<int> redValue;
	std::unordered_multiset<int> greenValue;
	std::unordered_multiset<int> BlueValue;

	sf::RectangleShape redBarShape;
	sf::RectangleShape greenBarShape;
	sf::RectangleShape blueBarShape;

	unsigned long long int redValueInt = 0;
	unsigned long long int greenValueInt = 0;
	unsigned long long int blueValueInt = 0;

	sf::Color piexelColor;
	unsigned long long colorCount = 0;
	sf::Text analysedImageText;
	sf::Text analysedImageText2;
	int getImageAnalyse();
	int map2(unsigned long long int x, unsigned long long int in_min, unsigned long long int in_max, unsigned long long int out_min, unsigned long long int out_max);

	void decryptImage();

public:

	GameState(sf::RenderWindow* window, std::stack<State*>* states);
	~GameState();

	void render();
	void updateSFMLevents(sf::Event *event);
	void update();
};

