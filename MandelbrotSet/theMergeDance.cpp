#include "theMergeDance.h"


void theMergeDance::initButtons()
{
    this->font.loadFromFile("Fonts/arial.ttf");
    //Creating buttons

    buttons["BACK"] = new Button(1050, 625, 100, 50,
        &font, "BACK",
        sf::Color(0, 0, 0),
        sf::Color(255, 255, 255),
        sf::Color(40, 40, 40), this->mWindow, BTN_STANDARD);

}

void theMergeDance::renderButtons()
{
    //Rendering the buttons
    for (auto& it : buttons)
    {
        it.second->render(this->mWindow);
    }
}

void theMergeDance::updateButtons()
{
    //Updates all button and handlles funcs
    for (auto& it : buttons)
    {
        //Update pressing and pass the mouse Positions 
        it.second->updatePress();
    }

    //Plays the game
    if (buttons["BACK"]->isPressed()) {
        this->endState();
    }
}

void theMergeDance::initShapes()
{

    if (this->backgroundTexture.loadFromFile("resources/background.jpg")) {
        this->backgroundTexture.setSmooth(true);
        this->backgroundSprite.setTexture(this->backgroundTexture);
    }
    this->backgroundSprite.setPosition(0.f, 0.f);

}


theMergeDance::theMergeDance(sf::RenderWindow* window, std::stack<State*>* states) : State(window, states)
{
    this->mWindow = window;
    this->initButtons();
    this->initShapes();
}

theMergeDance::~theMergeDance()
{
    //Deleting
    for (auto& it : buttons)
    {
        delete it.second;
    }
}

void theMergeDance::update()
{
    this->updateButtons();
}

void theMergeDance::render()
{
    this->mWindow->draw(backgroundSprite);
    this->renderButtons();

}

void theMergeDance::updateSFMLevents(sf::Event* event)
{
}
