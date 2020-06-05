#include "Menu.h"

void Menu::initFont()
{
    this->font.loadFromFile("Fonts/arial.ttf");
}

void Menu::initButtons()
{
    //Creating buttons

    buttons["START"] = new Button(850, 400, 100, 50,
        &font, "START",
        sf::Color(0, 0, 0),
        sf::Color(255, 255, 255),
        sf::Color(40, 40, 40), this->mWindow, BTN_STANDARD);

    buttons["PODACI O PROGRAMERU"] = new Button(700, 500, 350, 50,
        &font, "PODACI O PROGRAMERU",
        sf::Color(0, 0, 0),
        sf::Color(255, 255, 255),
        sf::Color(40, 40, 40), this->mWindow, BTN_STANDARD);

    buttons["QUIT"] = new Button(850, 600, 100, 50,
        &font, "QUIT",
        sf::Color(0, 0, 0),
        sf::Color(255, 255, 255),
        sf::Color(40, 40, 40), this->mWindow, BTN_STANDARD);
    
    buttons["Lets Bogo!"] = new Button(250, 400, 200, 50,
        &font, "Lets Bogo!",
        sf::Color(0, 0, 0),
        sf::Color(255, 255, 255),
        sf::Color(40, 40, 40), this->mWindow, BTN_STANDARD);

    buttons["Guess the number!"] = new Button(200, 500, 300, 50,
        &font, "Guess the number!",
        sf::Color(0, 0, 0),
        sf::Color(255, 255, 255),
        sf::Color(40, 40, 40), this->mWindow, BTN_STANDARD);

    buttons["The Merge Dance!"] = new Button(200, 600, 300, 50,
        &font, "The Merge Dance!",
        sf::Color(0, 0, 0),
        sf::Color(255, 255, 255),
        sf::Color(40, 40, 40), this->mWindow, BTN_STANDARD);
}

void Menu::renderButtons()
{
    //Rendering the buttons
    for (auto& it : buttons)
    {
        it.second->render(this->mWindow);
    }
}

void Menu::updateButtons()
{
    //Updates all button and handlles funcs
    for (auto& it : buttons)
    {
        //Update pressing and pass the mouse Positions 
        it.second->updatePress();
    }

    //Opens settings
    if (buttons["START"]->isPressed()) {
        this->states->push(new GameState(this->mWindow, this->states));
    }

    //Plays the game
    if (buttons["PODACI O PROGRAMERU"]->isPressed()) {
        this->states->push(new PodaciOProgrameru(this->mWindow, this->states));
    }
    //Plays the game
    if (buttons["QUIT"]->isPressed()) {
        this->endState();
    }
}

void Menu::initGameNameText()
{
    this->gameNameText.setFont(font);
    this->gameNameText.setCharacterSize(100);
    this->gameNameText.setOutlineColor(sf::Color::Black);
    this->gameNameText.setOutlineThickness(8);
    this->gameNameText.setPosition(200.f,70.f);
    this->gameNameText.setString("Mandelbrot Viewer");
}

void Menu::initBackground()
{
    if (this->backgroundTexture.loadFromFile("resources/background.jpg")) {
        this->backgroundTexture.setSmooth(true);
        this->backgroundSprite.setTexture(this->backgroundTexture);
    }
    this->backgroundSprite.setPosition(0.f, 0.f);
}

Menu::Menu(sf::RenderWindow* window, std::stack<State*>* states) : State(window, states)
{
	this->mWindow = window;
    this->initFont();
    this->initButtons();
    this->initGameNameText();
    this->initBackground();
}

Menu::~Menu()
{
    //Rendering the buttons
    for (auto& it : buttons)
    {
        delete it.second;
    }
}

void Menu::render()
{
    this->mWindow->draw(backgroundSprite);
    this->renderButtons();
    this->mWindow->draw(gameNameText);
}

void Menu::update()
{
    this->updateButtons();
}

void Menu::updateSFMLevents(sf::Event* event)
{
}

