
#pragma once
#include "State.h"
#include <vector>
#include <algorithm>
#include <sstream> 
#include <random>
#include <chrono>

//merge sa predavanja
#include "merge_sort.h"


/*

Funkcionalnost 43.	 (Bodova: 6) Dodajte na početni ekran novu opciju „Mini igra 3: The Merge Dance“ koja korisnika vodi na novi ekran. 
Dolaskom na taj ekran, pitajte korisnika da upiše broj koliko veliko polje želi sortirati. 
Nakon što upiše broj, napravite polje tražene veličine, razbacajte vrijednosti pa ga sortirajte 
merge sortom (koristite implementaciju s predavanja) i nacrtajte (animirajte) sadržaj stoga. 
Primjerice, neka kvadratić predstavlja jedan stackframe; svaki put kad se napravi poziv rekurzivne funkcije, s
tavite jedan kvadratić na stog, a svaki put kad se završi poziv rekurzivne funkcije, skinite jedan kvadratić sa stoga. 
Ako animacija ide prebrzo, usporite je malo.

*/

class theMergeDance : public State
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
	sf::Text playerText;

	int poljeSize = 0;
	std::vector<int> vektor;

	//bools
	bool start = false;

	void initButtons();
	void renderButtons();
	void updateButtons();
	void initShapes();

	void napraviPolje();
	void razbacajPolje();

public:
	theMergeDance(sf::RenderWindow* window, std::stack<State*>* states);
	~theMergeDance();

	void update();
	void render();
	void updateSFMLevents(sf::Event* event);
};

