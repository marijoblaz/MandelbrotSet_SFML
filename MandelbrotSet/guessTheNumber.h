
#pragma once
#include "State.h"
#include <vector>
#include <algorithm>
#include <sstream> 
#include <random>
#include <chrono>
/*

Funkcionalnost 42.	 (Bodova: 6) Dodajte na početni ekran novu opciju „Mini igra 2: 
Guess the number“ koja korisnika vodi na novi ekran. Dolaskom na taj ekran, generirajte jedan slučajni broj n između 1 i 100.000.000 
te pitajte korisnika da upiše koliko milisekundi misli da će trajati razbacivanje, sortiranje i binarno pretraživanje polja veličine n u potrazi za brojem 7.
Kad korisnik upiše vrijednost, generirajte polje s vrijednostima od 1 do n, razbacajte ga, sortirajte ga te binarnim pretraživanjem i pronađite broj 7. 
Ispišite korisniku kolika je razlika između njegove pogođene vrijednosti trajanja i konkretnog trajanja.


*/

class guessTheNumber : public State
{
private:

	sf::RenderWindow* mWindow;
	std::map<std::string, Button*> buttons;

	//Font for buttons
	sf::Font font;

	//Background
	sf::Texture backgroundTexture;
	sf::Sprite backgroundSprite;

	//Input
	sf::String playerInput;
	sf::Text infoText;
	sf::Text actualTimeText;
	sf::Text missedTimeText;
	int guessTime = 0;
	int actualTime = 0;
	sf::Text playerText;
	bool trazi = false;


	//Random num and Text
	unsigned long long randNum = 0;
	sf::Text generatedRandNumText;
	std::vector<int> vektorIntova;

	//InputBackgroun
	sf::RectangleShape inputBackground;
	sf::RectangleShape inputBackground2;
	sf::RectangleShape inputBackground3;
	sf::RectangleShape inputBackground4;

	void initButtons();
	void renderButtons();
	void updateButtons();
	void initShapes();
	void napuniVektor();
	void razbacajVektor();
	void sortirajVektor();
	void trazimSedam();
	long generate1();

public:
	guessTheNumber(sf::RenderWindow* window, std::stack<State*>* states);
	~guessTheNumber();

	void update();
	void render();
	void updateSFMLevents(sf::Event* event);
};

