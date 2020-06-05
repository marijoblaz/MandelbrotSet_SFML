#include "letsBogo.h"


void letsBogo::initButtons()
{
    this->font.loadFromFile("Fonts/arial.ttf");
    //Creating buttons

    buttons["BOGOSORT"] = new Button(500, 600, 200, 50,
        &font, "BOGOSORT",
        sf::Color(20, 20, 20),
        sf::Color(255, 255, 255),
        sf::Color(60, 60, 60), this->mWindow, BTN_STANDARD);

    buttons["BACK"] = new Button(1050, 625, 100, 50,
        &font, "BACK",
        sf::Color(20, 20, 20),
        sf::Color(255, 255, 255),
        sf::Color(60, 60, 60), this->mWindow, BTN_STANDARD);

}

void letsBogo::renderButtons()
{
    //Rendering the buttons
    for (auto& it : buttons)
    {
        it.second->render(this->mWindow);
    }
}

void letsBogo::updateButtons()
{
    //Updates all button and handlles funcs
    for (auto& it : buttons)
    {
        //Update pressing and pass the mouse Positions 
        it.second->updatePress();
    }

    //Opens settings
    if (buttons["BOGOSORT"]->isPressed() && !win) {
        //this->shuffle(this->arr, 3);
        if (elapsed1.asMilliseconds() > interval) {
            next_permutation(v.begin(), v.end());

            this->updateShapes();
            this->numOfTries++;
            this->numOfTriesText.setString(std::to_string(numOfTries));
            clock.restart();
        }
        

    }

    //Plays the game
    if (buttons["BACK"]->isPressed()) {
        this->endState();
    }
}

void letsBogo::initShapes()
{
    this->backShape.setSize(sf::Vector2f(600, 350));
    this->backShape.setPosition(sf::Vector2f(300, 150));
    this->backShape.setFillColor(sf::Color::Black);

    this->numOfTriesText.setFont(font);
    this->numOfTriesText.setCharacterSize(40);
    this->numOfTriesText.setOutlineColor(sf::Color::Black);
    this->numOfTriesText.setPosition(750.f, 600.f);
    this->numOfTriesText.setString(std::to_string(numOfTries));

    this->InfoText.setFont(font);
    this->InfoText.setCharacterSize(30);
    this->InfoText.setPosition(80.f, 550.f);
    this->InfoText.setString("BOGOSORT - U trenutku kad su sva cetiri elementa sortirana pobijedili ste");

    if (this->backgroundTexture.loadFromFile("resources/background2.png")) {
        this->backgroundSprite.setTexture(this->backgroundTexture);
    }
    this->backgroundSprite.setPosition(0.f, 0.f);

    //Add shapes to array of shapes
    this->arr[0] = this->shape1;
    this->arr[1] = this->shape2;
    this->arr[2] = this->shape3;
    this->arr[3] = this->shape4;

    for (int i = 0; i < 4; i++){
        this->arr[i].setFillColor(sf::Color::Red);
        this->arr[i].setRotation(180);
    }

    this->arr[0].setSize(sf::Vector2f(30, shapeHeight1));
    this->arr[1].setSize(sf::Vector2f(30, shapeHeight2));
    this->arr[2].setSize(sf::Vector2f(30, shapeHeight3));
    this->arr[3].setSize(sf::Vector2f(30, shapeHeight3));

    this->arr[0].setPosition(sf::Vector2f(480, 450));
    this->arr[1].setPosition(sf::Vector2f(580, 450));
    this->arr[2].setPosition(sf::Vector2f(680, 450));
    this->arr[3].setPosition(sf::Vector2f(780, 450));

}

void letsBogo::updateShapes()
{
    this->arr[0].setSize(sf::Vector2f(30, v[0]));
    this->arr[1].setSize(sf::Vector2f(30, v[1]));
    this->arr[2].setSize(sf::Vector2f(30, v[2]));
    this->arr[3].setSize(sf::Vector2f(30, v[3]));
}

void letsBogo::generateShapeHeights()
{
    this->shapeHeight1 = rand() % 200 + 50;
    this->shapeHeight2 = rand() % 200 + 50;
    this->shapeHeight3 = rand() % 200 + 50;
    this->shapeHeight4 = rand() % 200 + 50;

}

bool letsBogo::isSortedAscending(std::vector<int>& v)
{
    for (unsigned i = 0; i < v.size() - 1; i++)
    {
        if (v[i] > v[i + 1])
        {
            return false;
        }
    }
    return true;
}


letsBogo::letsBogo(sf::RenderWindow* window, std::stack<State*>* states) : State(window, states)
{
	this->mWindow = window;
    this->initButtons();
    this->generateShapeHeights();
    this->initShapes();

    this->v.push_back(shapeHeight1);
    this->v.push_back(shapeHeight2);
    this->v.push_back(shapeHeight3);
    this->v.push_back(shapeHeight4);

}

letsBogo::~letsBogo()
{
    //Deleting
    for (auto& it : buttons)
    {
        delete it.second;
    }
}

void letsBogo::update()
{
    this->elapsed1 = clock.getElapsedTime();
    this->updateButtons();

    if (isSortedAscending(v)) {
        this->elapsed2 = clock.getElapsedTime();

        this->winText.setFont(font);
        this->winText.setCharacterSize(80);
        this->winText.setOutlineColor(sf::Color::Black);
        this->winText.setOutlineThickness(4);
        this->winText.setPosition(450.f, 40.f);
        this->winText.setString("You Win!");

        this->win = true;

        if (elapsed2.asSeconds() > interval2) {
            this->endState();
            clock.restart();
        }
    }

}

void letsBogo::render()
{
    this->mWindow->draw(backgroundSprite);
    this->mWindow->draw(backShape);
    this->mWindow->draw(numOfTriesText);
    this->mWindow->draw(InfoText);

    this->renderButtons();

    for (int i = 0; i < 4; i++)
    {
        this->mWindow->draw(arr[i]);
    }
    if(win) this->mWindow->draw(winText);
}

void letsBogo::updateSFMLevents(sf::Event* event)
{
}
