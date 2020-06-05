#pragma once
#include "State.h"
#include <vector>
#include <algorithm>

/*

Funkcionalnost 41.	 (Bodova: 5) Dodajte na početni ekran novu opciju „Mini igra 1: Lets Bogo!“ koja korisnika vodi na novi ekran. 
Dolaskom na taj ekran, prikažite korisniku tri elementa. 
Kad korisnik odabere opciju (gumb ili što god odaberete), presložite te elemente slučajnim rasporedom. 
U trenutku kad su sva četiri elementa sortirana, prikažite korisniku poruku da je pobijedio, 
ispišite u koliko pokušaja i vratite ga na početni ekran.

*/

class letsBogo : public State
{
private:

	sf::RenderWindow* mWindow;
	std::map<std::string, Button*> buttons;
	sf::Font font;

	//Background
	sf::Texture backgroundTexture;
	sf::Sprite backgroundSprite;

	//Background
	sf::RectangleShape backShape;

	//Text
	sf::Text winText;
	sf::Text numOfTriesText;
	sf::Text InfoText;

	sf::RectangleShape arr[4];
	sf::RectangleShape shape1;
	sf::RectangleShape shape2;
	sf::RectangleShape shape3;
	sf::RectangleShape shape4;

	//Bogosort array

	std::vector<int> v;
	sf::Clock clock; // starts the clock
	sf::Time elapsed1;
	sf::Time elapsed2;
	int interval = 200;
	int interval2 = 3;

	int numOfTries = 0;

	int shapeHeight1;
	int shapeHeight2;
	int shapeHeight3;
	int shapeHeight4;

	bool win = false;


	void initButtons();
	void renderButtons();
	void updateButtons();
	void initShapes();
	void updateShapes();
	void generateShapeHeights();
	bool isSortedAscending(std::vector<int>& v);

public:
	letsBogo(sf::RenderWindow* window, std::stack<State*>* states);
	~letsBogo();

	void update();
	void render();
	void updateSFMLevents(sf::Event* event);
};

