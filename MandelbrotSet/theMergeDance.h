
#pragma once
#include "State.h"
#include <vector>
#include <algorithm>
#include <sstream> 
#include <random>
#include <chrono>


/*

Funkcionalnost 43.	 (Bodova: 6) Dodajte na početni ekran novu opciju „Mini igra 3: The Merge Dance“ koja korisnika vodi na novi ekran. 
Dolaskom na taj ekran, pitajte korisnika da upiše broj koliko veliko polje želi sortirati. 
Nakon što upiše broj, napravite polje tražene veličine, razbacajte vrijednosti pa ga sortirajte 
merge sosavanja) i nacrtajte (animirajte) sadržaj stoga. 
Primjerice, neka kvadratić predstavlja jedan stackframe; svaki put kad se napravi poziv rekurzivne funkcije, s
tavite jedan kvadratić na stog, a svaki put kad se završi poziv rekurzivne funkcije, skinite jedan kvadratić sa stoga. 
Ako animacija ide prebrzo, usporite je malo.

*/

class theMergeDance : public State
{
private:

	sf::RenderWindow* mWindow;
	std::map<std::string, Button*> buttons;

	//FOr slowing down anim
	sf::Clock clock; // starts the clock
	sf::Time elapsed1;
	int interval = 100;

	//Font for buttons
	sf::Font font;

	//Background
	sf::Texture backgroundTexture;
	sf::Sprite backgroundSprite;

	//StackBackgorung
	sf::RectangleShape stackBackgrundShape;

	//Tiles
	sf::RectangleShape kvadraticStogShape;
	std::vector<int> vektorKvadraticaPomocni;

	std::vector<sf::RectangleShape> kvadraticiVektor;

	//Input
	sf::String playerInput;
	sf::Text playerText;

	//Info
	sf::Text infoText1;
	sf::Text infoText2;

	int poljeSize = 0;
	std::vector<int> vektor;

	//bools
	bool start = false;
	bool showFinish = false;

	int stackCounter = 0;

	void initButtons();
	void renderButtons();
	void updateButtons();
	void initShapes();

	void napraviPolje();
	void razbacajPolje();
	void printV(std::vector<int> v);
	
	void animirajStack();

	//merge_sort sa predavanja modificiran
	std::vector<int> merge_sort(std::vector<int> m);
	std::vector<int> merge(std::vector<int> left, std::vector<int> right);

public:
	theMergeDance(sf::RenderWindow* window, std::stack<State*>* states);
	~theMergeDance();

	void update();
	void render();
	void updateSFMLevents(sf::Event* event);
};

