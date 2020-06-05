#pragma once
#include "Button.h"
#include "State.h"

class PodaciOProgrameru : public State
{
private:
	sf::RenderWindow* mWindow;

	sf::Text imePrezimeText;

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

