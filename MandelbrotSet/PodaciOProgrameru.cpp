#include "PodaciOProgrameru.h"

PodaciOProgrameru::PodaciOProgrameru(sf::RenderWindow* window, std::stack<State*>* states) : State(window, states)
{
	this->mWindow = window;

    this->music.setVolume(50);
    if (this->music.openFromFile("resources/music.ogg")) this->music.play();

    this->font.loadFromFile("Fonts/arial.ttf");


    this->imePrezimeText.setFont(this->font);
    this->imePrezimeText.setCharacterSize(100);
    this->imePrezimeText.setOutlineColor(sf::Color::Black);
    this->imePrezimeText.setOutlineThickness(8);
    this->imePrezimeText.setPosition(275.f, 0.f);

    if (this->backgroundTexture.loadFromFile("resources/background5.jpg")) {
        this->backgroundSprite.setTexture(this->backgroundTexture);
    }
    this->backgroundSprite.setPosition(0.f, 0.f);


    buttons["BACK"] = new Button(1050, 625, 100, 50,
        &font, "BACK",
        sf::Color(20, 20, 20),
        sf::Color(255, 255, 255),
        sf::Color(60, 60, 60), this->mWindow, BTN_STANDARD);
}

PodaciOProgrameru::~PodaciOProgrameru()
{
    //Deleting
    for (auto& it : buttons)
    {
        delete it.second;
    }
}

void PodaciOProgrameru::update()
{
    this->elapsed1 = clock.getElapsedTime();

    //End exit
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Escape)) { this->endState(); }

    //startAnimation
    if (elapsed1.asMilliseconds() > interval) {
        if (animDown) {
            this->startAnim++;
            this->imePrezimeText.setString("Marijo Blazevic");
        }
        else
        {
            this->startAnim--;
            this->imePrezimeText.setString("Programer...");
        }
        

        if (this->imePrezimeText.getPosition().y > this->mWindow->getSize().y - 100) {
            this->animDown = false;
           
        }

        if (this->imePrezimeText.getPosition().y + 25 <= 0) {

            this->animDown = true;
            
        }

        this->imePrezimeText.setPosition(275.f, this->startAnim);
        clock.restart();
    }

    //Updates all button and handlles funcs
    for (auto& it : buttons)
    {   
        //Update pressing and pass the mouse Positions 
        it.second->updatePress();
    }

    //Opens settings
    if (buttons["BACK"]->isPressed()) {
        this->endState();
    }


}

void PodaciOProgrameru::render()
{
    this->mWindow->draw(this->backgroundSprite);
    this->mWindow->draw(this->imePrezimeText);

    //Rendering the buttons
    for (auto& it : buttons)
    {
        it.second->render(this->mWindow);
    }
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
