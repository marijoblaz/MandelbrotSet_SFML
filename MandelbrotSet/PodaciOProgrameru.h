#pragma once
#include "Button.h"
#include "State.h"

/*


Funkcionalnost 32.	 
(Bodova: 3) Odabirom prikaza podataka o programeru koji je napravio igru, potrebno je napraviti sljedeće: 

a) prikazati animirano ime i prezime programera,
b) pustiti pozadinsku glazbu, 
c) implementirati povratak na početni ekran.




*/

class PodaciOProgrameru : public State
{
private:
	std::map<std::string, Button*> buttons;

	sf::RenderWindow* mWindow;

	sf::Font font;
	sf::Text imePrezimeText; 

	sf::Clock clock; // starts the clock
	sf::Time elapsed1;
	int interval = 5;
	bool animDown = true;
	sf::Music music;


	//Background
	sf::Texture backgroundTexture;
	sf::Sprite backgroundSprite;

	int startAnim = 0;

	bool meQuit = false;

public:
	PodaciOProgrameru(sf::RenderWindow* window, std::stack<State*>* states);
	~PodaciOProgrameru();

	void update();
	void render();
	void updateSFMLevents(sf::Event* event);
	bool getQuit();
	void setQuit(bool quit);

};

