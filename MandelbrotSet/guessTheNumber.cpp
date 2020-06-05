#include "guessTheNumber.h"


void guessTheNumber::initButtons()
{
    this->font.loadFromFile("Fonts/arial.ttf");
    //Creating buttons

    buttons["BACK"] = new Button(1050, 625, 100, 50,
        &font, "BACK",
        sf::Color(0, 0, 0),
        sf::Color(255, 255, 255),
        sf::Color(40, 40, 40), this->mWindow, BTN_STANDARD);

    this->playerText.setFont(font);
    this->playerText.setCharacterSize(25);
    this->playerText.setPosition(sf::Vector2f(10, 100));    
    
    this->actualTimeText.setFont(font);
    this->actualTimeText.setCharacterSize(25);
    this->actualTimeText.setPosition(sf::Vector2f(10, 180)); 

    this->missedTimeText.setFont(font);
    this->missedTimeText.setCharacterSize(25);
    this->missedTimeText.setPosition(sf::Vector2f(10, 220));
    
    this->infoText.setFont(font);
    this->infoText.setCharacterSize(25);
    this->infoText.setPosition(sf::Vector2f(10, 140));
    this->infoText.setString("Pritisni ENTER nakon unosa!");

    this->generatedRandNumText.setFont(font);
    this->generatedRandNumText.setCharacterSize(25);
    this->generatedRandNumText.setPosition(sf::Vector2f(10, 60));

    this->inputBackground.setFillColor(sf::Color::Black);
    this->inputBackground.setSize(sf::Vector2f(120.f, 40.f));
    this->inputBackground.setPosition(sf::Vector2f(1020,95));
    this->inputBackground.setOutlineColor(sf::Color::White);
    this->inputBackground.setOutlineThickness(2);

    this->inputBackground2.setFillColor(sf::Color::Black);
    this->inputBackground2.setSize(sf::Vector2f(160.f, 40.f));
    this->inputBackground2.setPosition(sf::Vector2f(450,55));
    this->inputBackground2.setOutlineColor(sf::Color::White);
    this->inputBackground2.setOutlineThickness(2);




}

void guessTheNumber::renderButtons()
{
    //Rendering the buttons
    for (auto& it : buttons)
    {
        it.second->render(this->mWindow);
    }
}

void guessTheNumber::updateButtons()
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

void guessTheNumber::initShapes()
{

    if (this->backgroundTexture.loadFromFile("resources/background4.jpg")) {
        this->backgroundSprite.setTexture(this->backgroundTexture);
    }
    this->backgroundSprite.setPosition(0.f, 0.f);

}

void guessTheNumber::napuniVektor()
{
    for (unsigned long long i = 0; i < randNum; i++)
    {
        this->vektorIntova.push_back(i);
    }
}

void guessTheNumber::razbacajVektor()
{
    auto rng = std::default_random_engine{};
    std::shuffle(std::begin(vektorIntova), std::end(vektorIntova), rng);
}

void guessTheNumber::sortirajVektor()
{
    std::sort(std::begin(vektorIntova), std::end(vektorIntova));
}

void guessTheNumber::trazimSedam()
{
    std::binary_search(vektorIntova.begin(), vektorIntova.end(), 7);
}

long guessTheNumber::generate1()
{
    static const int p6 = 1e6;
    static const int p5 = 1e5;
    static const int p4 = 1e4;
    static const int p3 = 1e3;
    static const int p2 = 1e2;
    static const int p1 = 1e1;

    static int digit[7];

    digit[6] = rand() % 30 + 1;

    for (int i = 5; i >= 0; i--)
        digit[i] = rand() % 10 + 1;

    return digit[6] * p6
        + digit[5] * p5
        + digit[4] * p4
        + digit[3] * p3
        + digit[2] * p2
        + digit[1] * p1
        + digit[0];
}



guessTheNumber::guessTheNumber(sf::RenderWindow* window, std::stack<State*>* states) : State(window, states)
{
    this->mWindow = window;
    this->initButtons();
    this->initShapes();

    this->randNum = generate1()/2;
    this->generatedRandNumText.setString("Slucajni broj n izmedu 1 i 100.000.000: "+std::to_string(randNum));
}

guessTheNumber::~guessTheNumber()
{
    //Deleting
    for (auto& it : buttons)
    {
        delete it.second;
    }
}

void guessTheNumber::update()
{
    this->updateButtons();

  
    if (this->trazi) {
        auto begin = std::chrono::high_resolution_clock::now();
        this->napuniVektor();
        this->razbacajVektor();
        this->sortirajVektor();
        this->trazimSedam();
        auto end = std::chrono::high_resolution_clock::now();
        this->actualTime = std::chrono::duration_cast<std::chrono::milliseconds>(end - begin).count();
        this->actualTimeText.setString("Trajalo je: " + std::to_string(actualTime) + "ms");
        this->missedTimeText.setString("Fulali ste za: " + std::to_string(std::abs(actualTime - guessTime)) + "ms");
        this->trazi = false;

        //Clear
        this->vektorIntova.clear();
        //draw
        this->inputBackground3.setFillColor(sf::Color::Black);
        this->inputBackground3.setSize(sf::Vector2f(120.f, 30.f));
        this->inputBackground3.setPosition(sf::Vector2f(125, 180));
        this->inputBackground3.setOutlineColor(sf::Color::White);
        this->inputBackground3.setOutlineThickness(2);

        this->inputBackground4.setFillColor(sf::Color::Black);
        this->inputBackground4.setSize(sf::Vector2f(120.f, 30.f));
        this->inputBackground4.setPosition(sf::Vector2f(155, 220));
        this->inputBackground4.setOutlineColor(sf::Color::White);
        this->inputBackground4.setOutlineThickness(2);

    }

}

void guessTheNumber::render()
{
    this->mWindow->draw(backgroundSprite);
    this->mWindow->draw(this->inputBackground);
    this->mWindow->draw(this->inputBackground2);
    this->mWindow->draw(this->inputBackground3);
    this->mWindow->draw(this->inputBackground4);
    this->mWindow->draw(playerText);
    this->mWindow->draw(actualTimeText);
    this->mWindow->draw(missedTimeText);
    this->mWindow->draw(infoText);
    this->mWindow->draw(generatedRandNumText);
    this->renderButtons();

}

void guessTheNumber::updateSFMLevents(sf::Event* event)
{
    if (event->type == sf::Event::TextEntered) {
       
        if (event->text.unicode == '\b') { // handle backspace explicitly
            if(!playerInput.isEmpty())
                playerInput.erase(playerInput.getSize() - 1, 1);
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Enter)) { // handle backspace explicitly
            std::stringstream ss(playerInput);
            ss >> this->guessTime;
            this->trazi = true;
        }
        else if ((event->text.unicode > 47 && event->text.unicode < 58) &&  playerInput.getSize() < 8){ // all other keypresses
            playerInput += static_cast<char>(event->text.unicode);
        }
    }
    playerText.setString("Razbacivanje, sortiranje i binarno pretrazivanje polja velicine n za potragom broja 7! (ms): " + playerInput);
}
