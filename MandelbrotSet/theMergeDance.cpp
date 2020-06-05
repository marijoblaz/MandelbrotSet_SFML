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

    if (this->backgroundTexture.loadFromFile("resources/background3.jpg")) {
        this->backgroundSprite.setTexture(this->backgroundTexture);
    }
    this->backgroundSprite.setPosition(0.f, 0.f);

    this->playerText.setFont(font);
    this->playerText.setCharacterSize(25);
    this->playerText.setPosition(sf::Vector2f(10, 100));

}

void theMergeDance::napraviPolje()
{
    for (int i = 0; i < poljeSize; i++)
    {
        this->vektor.push_back(i);
    }
}

void theMergeDance::razbacajPolje()
{
    auto rng = std::default_random_engine{};
    std::shuffle(std::begin(this->vektor), std::end(this->vektor), rng);
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
    if (start) {

        start = false;
    }
}

void theMergeDance::render()
{
    this->mWindow->draw(backgroundSprite);
    this->mWindow->draw(playerText);
    this->renderButtons();

}

void theMergeDance::updateSFMLevents(sf::Event* event)
{
    if (event->type == sf::Event::TextEntered) {

        if (event->text.unicode == '\b') { // handle backspace explicitly
            if (!playerInput.isEmpty())
                playerInput.erase(playerInput.getSize() - 1, 1);
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Enter)) { // handle backspace explicitly
            std::stringstream ss(playerInput);
            ss >> this->poljeSize;
            this->start = true;
        }
        else if ((event->text.unicode > 47 && event->text.unicode < 58) && playerInput.getSize() < 8) { // all other keypresses
            playerInput += static_cast<char>(event->text.unicode);
        }
    }
    playerText.setString("Koliko veliko polje zelite sortirati: " + playerInput);
}
