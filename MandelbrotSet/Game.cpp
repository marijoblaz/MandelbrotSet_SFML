#include "Game.h"


void Game::updateSFMLEvents()
{
    
    while (this->mWindow.pollEvent(this->event))
    {
        if (event.type == sf::Event::Closed)
            this->mWindow.close();
        if (!this->states.empty())
            this->states.top()->updateSFMLevents(&this->event);

    }
}

void Game::render()
{
    //Clearing the screen with blank default color
    this->mWindow.clear();


    //If there are states active - render them (passing the window)
    if (!this->states.empty())
        this->states.top()->render();

    //Final displaying of a game (flushing the buffer to display)
    this->mWindow.display();
}

void Game::update()
{
    this->updateSFMLEvents();
    //Checking & updating stack states
    if (!this->states.empty())
    {
        //Calling update only if game is not poused (Works only in GameState)
        //if (!this->states.top()->getPause()) {
        this->states.top()->update();


        //If state wants to quit
        if (this->states.top()->getQuit())
        {
            //deleting the top state 
            delete this->states.top();
            this->states.pop();
        }
    }

    //If there is no states active end the App
    else if (this->states.empty())
    {
        //App end
        std::cout << "Ending app\n";
        this->mWindow.close();
    }
    
}


Game::Game() : mWindow(sf::VideoMode(WIDTH, HEIGHT), "MandelbrotSet", sf::Style::Close)
{

    this->mWindow.setFramerateLimit(120);

    this->initStates();

}

void Game::initStates()
{
    //Pushing the MainMenu state to stack
    this->states.push(new Menu(&this->mWindow, &this->states));
}

void Game::run()
{
	while (this->mWindow.isOpen())
	{
		this->updateSFMLEvents();
		this->update();
		this->render();
	}
}

Game::~Game()
{
    delete menu;
}