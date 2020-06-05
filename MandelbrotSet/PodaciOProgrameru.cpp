#include "PodaciOProgrameru.h"

PodaciOProgrameru::PodaciOProgrameru(sf::RenderWindow* window, std::stack<State*>* states) : State(window, states)
{
	this->mWindow = window;
}

PodaciOProgrameru::~PodaciOProgrameru()
{
}

void PodaciOProgrameru::update()
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Escape)) { this->endState(); }
}

void PodaciOProgrameru::render()
{
}

void PodaciOProgrameru::updateSFMLevents(sf::Event* event)
{
}

bool PodaciOProgrameru::getQuit()
{
	return this->meQuit;
}

void PodaciOProgrameru::setQuit(bool quit)
{
}
