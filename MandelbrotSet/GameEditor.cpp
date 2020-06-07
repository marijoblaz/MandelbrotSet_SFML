#include "GameEditor.h"


void GameEditor::initButtons()
{
    this->font.loadFromFile("Fonts/arial.ttf");
    //Creating buttons
    
    buttons["BACK"] = new Button(1050, 50, 100, 50,
        &font, "BACK",
        sf::Color(20, 20, 20),
        sf::Color(255, 255, 255),
        sf::Color(60, 60, 60), this->mWindow, BTN_STANDARD); 
    
    
    buttons["SAVE IMAGE"] = new Button(50, 650, 200, 50,
        &font, "SAVE IMAGE",
        sf::Color(20, 20, 20),
        sf::Color(255, 255, 255),
        sf::Color(60, 60, 60), this->mWindow, BTN_STANDARD);

    colorPickButtons["BLUE"] = new Button(1050, 150, 100, 50,
        &font, "PRESET",
        sf::Color(0, 0, 90),
        sf::Color(255, 255, 255),
        sf::Color(0, 0, 100), this->mWindow, BTN_STANDARD); 
    
    colorPickButtons["RED"] = new Button(1050, 205, 100, 50,
        &font, "PRESET",
        sf::Color(90, 0, 0),
        sf::Color(255, 255, 255),
        sf::Color(100, 0, 0), this->mWindow, BTN_STANDARD);

    colorPickButtons["GREEN"] = new Button(1050, 260, 100, 50,
        &font, "PRESET",
        sf::Color(0, 90, 0),
        sf::Color(255, 255, 255),
        sf::Color(0, 100, 0), this->mWindow, BTN_STANDARD);

}

void GameEditor::renderButtons()
{
    //Rendering the buttons
    for (auto& it : buttons)
    {
        it.second->render(this->mWindow);
    }

    //Rendering the buttons
    for (auto& it : colorPickButtons)
    {
        it.second->render(this->mWindow);
    }
}

void GameEditor::updateButtons()
{
    this->elapsed1 = clock.getElapsedTime();

    //Updates all button and handlles funcs
    for (auto& it : buttons)
    {
        //Update pressing and pass the mouse Positions 
        it.second->updatePress();
    } 
    
    //Updates all button and handlles funcs
    for (auto& it : colorPickButtons)
    {
        //Update pressing and pass the mouse Positions 
        it.second->updatePress();
    }


    //Plays the game
    if (buttons["BACK"]->isPressed() && elapsed1.asMilliseconds() > interval) {
        this->endState();
        this->clock.restart();
    }

    //Plays the game
    if (colorPickButtons["BLUE"]->isPressed() && elapsed1.asMilliseconds() > interval) {
        this->changeColor(sf::Color(0, 0, 90));
        this->clock.restart();
    } 
    //Plays the game
    if (colorPickButtons["RED"]->isPressed() && elapsed1.asMilliseconds() > interval) {
        this->changeColor(sf::Color(90, 0, 0));
        this->clock.restart();
    }
    //Plays the game
    if (colorPickButtons["GREEN"]->isPressed() && elapsed1.asMilliseconds() > interval) {
        this->changeColor(sf::Color(0, 90, 0));
        this->clock.restart();
    }
}

void GameEditor::updateMousePos()
{
    this->mousePosScreen = sf::Mouse::getPosition();
    this->mousePosWindow = sf::Mouse::getPosition(*this->mWindow);
    this->mousePosView = this->mWindow->mapPixelToCoords(sf::Mouse::getPosition(*this->mWindow));

    //this->RGBText.setString(std::to_string());

}

void GameEditor::updateRGBPostions()
{
    this->RGBText.setPosition(this->mousePosView.x + 10, this->mousePosView.y + 10);
    //std::cout << this->image.getPixel(10, 10).g << std::endl;

    if ((int)this->mousePosView.y > 1 && (int)this->mousePosView.y < 719) {
        if ((int)this->mousePosView.x > 1 && (int)this->mousePosView.x < 1200) {
            int redColor = this->image.getPixel((int)this->mousePosView.x, (int)this->mousePosView.y).r;
            int greenColor = this->image.getPixel((int)this->mousePosView.x, (int)this->mousePosView.y).g;
            int blueColor = this->image.getPixel((int)this->mousePosView.x, (int)this->mousePosView.y).b;
            //std::cout << "R: "<< redColor<< "G: "<< greenColor << "B: "<< blueColor << std::endl;
            this->RGBText.setString("R: " + std::to_string(redColor) + "\n" + "G: " + std::to_string(greenColor) + "\n" "B: " + std::to_string(blueColor));
            if(!this->colorPicked) this->colorFinderShape.setFillColor(sf::Color(redColor, greenColor, blueColor, 255));
            if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && elapsed1.asMilliseconds() > interval) {
                this->pickedColor = sf::Color(redColor, greenColor, blueColor, 255);
                this->colorPicked = !this->colorPicked;
                this->clock.restart();
            }
        }
    }
}

void GameEditor::changeColor(sf::Color color)
{
    for (int x = 0; x < 1200; x++)
    {
        for (int y = 0; y < 720; y++)
        {
            if (this->image.getPixel(x, y) == this->pickedColor) {
                this->image.setPixel(x, y, color);
            }
        }
    }
}

void GameEditor::initText()
{
    this->RGBText.setFont(this->font);
    this->RGBText.setCharacterSize(20);

    this->infoText.setFont(this->font);
    this->infoText.setCharacterSize(30);
    this->infoText.setPosition(sf::Vector2f(130, 10));
    this->infoText.setString("Pick a color to change");
    
    this->redColorCount.setFont(this->font);
    this->redColorCount.setCharacterSize(20);
    this->redColorCount.setPosition(sf::Vector2f(10, 135));

    this->greenColorCount.setFont(this->font);
    this->greenColorCount.setCharacterSize(20);
    this->greenColorCount.setPosition(sf::Vector2f(10, 160));
    
    this->blueColorCount.setFont(this->font);
    this->blueColorCount.setCharacterSize(20);
    this->blueColorCount.setPosition(sf::Vector2f(10, 185));
    

    this->colorFinderShape.setSize(sf::Vector2f(100, 100));
    this->colorFinderShape.setPosition(10, 10);
    this->colorFinderShape.setOutlineColor(sf::Color::White);
    this->colorFinderShape.setOutlineThickness(2);


}

void GameEditor::countColors()
{
    for (int x = 0; x < 1200; x++)
    {
        for (int y = 0; y < 720; y++)
        {
            int redColor = this->image.getPixel(x, y).r;
            int greenColor = this->image.getPixel(x,y).g;
            int blueColor = this->image.getPixel(x, y).b;

            if (redColor > 0) {
                this->redColorSet.insert(redColor);
            }
            if (greenColor > 0) {
                 this->greenColorSet.insert(greenColor);
            }
            if (blueColor > 0) {
                this->blueColorSet.insert(blueColor);

            }

        }
    }

    this->redColorCount.setString("R count: " + std::to_string(this->redColorSet.size()));
    this->greenColorCount.setString("G count: " + std::to_string(this->greenColorSet.size()));
    this->blueColorCount.setString("B count: " + std::to_string(this->blueColorSet.size()));

    this->redColorSet.clear();
    this->greenColorSet.clear();
    this->blueColorSet.clear();

}

GameEditor::GameEditor(sf::RenderWindow* window, std::stack<State*>* states) : State(window, states)
{
    this->mWindow = window;

    this->initButtons();
    this->initText();
}

GameEditor::~GameEditor()
{
    //Deleting
    for (auto& it : buttons)
    {
        delete it.second;
    }
}

void GameEditor::update()
{
    if (this->firstStart) {
        this->image = this->states->top()->getImage();
        this->firstStart = false;
    }
    this->mbSetTexture.loadFromImage(this->image);
    this->mbSetSprite.setTexture(mbSetTexture);

    this->updateButtons();
    this->updateMousePos();
    this->updateRGBPostions();
    this->countColors();
}

void GameEditor::render()
{
    this->mWindow->draw(this->mbSetSprite);
    this->mWindow->draw(this->RGBText);
    this->mWindow->draw(this->colorFinderShape);
    this->mWindow->draw(this->infoText);

    this->mWindow->draw(this->redColorCount);
    this->mWindow->draw(this->greenColorCount);
    this->mWindow->draw(this->blueColorCount);
    this->renderButtons();
}

void GameEditor::updateSFMLevents(sf::Event* event)
{
}
