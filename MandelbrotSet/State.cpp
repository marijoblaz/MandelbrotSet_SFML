#include "State.h"

State::State(sf::RenderWindow* window, std::stack<State*>* states)
{
	//Constructor
	//Init vars
	this->window = window;
	this->states = states;

	this->quit = false;
	this->pause = false;
}
State::~State()
{
}

//Getters and setters
const bool& State::getQuit()
{
	return this->quit;
}

//Call functions
void State::endState()
{
	this->quit = true;
}
