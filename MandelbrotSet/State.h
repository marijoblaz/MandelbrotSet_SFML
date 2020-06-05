#pragma once

#include "Button.h"

class State
{
protected:

	//Container for pointer states
	std::stack<State*>* states;

	//Init vars
	sf::RenderWindow* window;

	bool quit;
	bool pause;

public:
	State(sf::RenderWindow* window, std::stack<State*>* states);
	virtual ~State();

	//Getters
	const bool& getQuit();


	void endState();

	//Virutal functions
	virtual void update() = 0;
	virtual void render() = 0;
	virtual void updateSFMLevents(sf::Event* event) = 0;
};

