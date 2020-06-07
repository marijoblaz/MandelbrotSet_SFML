#include "GameEditor.h"

typedef std::unordered_multimap<std::string, int>::iterator umm;

void GameEditor::initButtons()
{
    this->font.loadFromFile("Fonts/arial.ttf");
    //Creating buttons

    umm it = this->colorPresetUMM.begin();
    
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

    colorPickButtons["BLUE"] = new Button(1000, 150, 150, 50,
        &font, it->first,
        sf::Color(0, 0, it->second),
        sf::Color(255, 255, 255),
        sf::Color(0, 0, 100), this->mWindow, BTN_STANDARD); it++;
    
    colorPickButtons["BLUE1"] = new Button(1000, 205, 150, 50,
        &font, it->first,
        sf::Color(0, 0, it->second),
        sf::Color(255, 255, 255),
        sf::Color(0, 0, 170), this->mWindow, BTN_STANDARD); it++;
    
    colorPickButtons["GREEN"] = new Button(1000, 260, 150, 50,
        &font, it->first,
        sf::Color(0, it->second, 0),
        sf::Color(255, 255, 255),
        sf::Color(0, 100, 0), this->mWindow, BTN_STANDARD); it++;
    
    colorPickButtons["STRING"] = new Button(1000, 480, 150, 30,
        &font, "",
        sf::Color(0, 0, 0),
        sf::Color(40, 40, 40),
        sf::Color(0, 0, 0), this->mWindow, BTN_STANDARD); 
    
    colorPickButtons["RGB"] = new Button(1000, 540, 150, 30,
        &font, "",
        sf::Color(0, 0, 0),
        sf::Color(40, 40, 40),
        sf::Color(0, 0, 0), this->mWindow, BTN_STANDARD);

    colorPickButtons["SAVE COLOR"] = new Button(950, 625, 200, 50,
        &font, "SAVE COLOR",
        sf::Color(0, 0, 0),
        sf::Color(40, 40, 40),
        sf::Color(40, 40, 40), this->mWindow, BTN_STANDARD);

    colorPickButtons["LEFT"] = new Button(975, 315, 20, 50,
        &font, "<",
        sf::Color(0, 0, 0),
        sf::Color(40, 40, 40),
        sf::Color(40, 40, 40), this->mWindow, BTN_STANDARD);

    colorPickButtons["RIGHT"] = new Button(1155, 315, 20, 50,
        &font, ">",
        sf::Color(0, 0, 0),
        sf::Color(40, 40, 40),
        sf::Color(40, 40, 40), this->mWindow, BTN_STANDARD);

    colorPickButtons["USERCOLOR"] = new Button(999, 314, 152, 52,
        &font, "",
        sf::Color(0, 0, 0),
        sf::Color(40, 40, 40),
        sf::Color(40, 40, 40), this->mWindow, BTN_STANDARD);

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
    if (colorPickButtons["BLUE1"]->isPressed() && elapsed1.asMilliseconds() > interval) {
        this->changeColor(sf::Color(0, 0, 170));
        this->clock.restart();
    }
    //Plays the game
    if (colorPickButtons["GREEN"]->isPressed() && elapsed1.asMilliseconds() > interval) {
        this->changeColor(sf::Color(0, 90, 0));
        this->clock.restart();
    }

    //Plays the game
    if (colorPickButtons["USERCOLOR"]->isPressed() && elapsed1.asMilliseconds() > interval) {
        this->changeColor(this->userColor);
        this->clock.restart();
    }

    //Plays the game
    if (colorPickButtons["RGB"]->isPressed() && elapsed1.asMilliseconds() > interval) {
        this->inputVector = true;
        this->inputString = false;
        this->clock.restart();
    } 
    //Plays the game
    if (colorPickButtons["STRING"]->isPressed() && elapsed1.asMilliseconds() > interval) {
        this->inputVector = false;
        this->inputString = true;
        this->clock.restart();
    } 
    
    //Plays the game
    if (colorPickButtons["SAVE COLOR"]->isPressed() && elapsed1.asMilliseconds() > interval) {
        this->userStringColorText.setString(this->userEnteredString);
        this->userEnteredString.clear();
        this->parseUserColor();
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
    this->infoText.setString("Pick a color on the image to change it");

    this->infoText2.setFont(this->font);
    this->infoText2.setCharacterSize(20);
    this->infoText2.setPosition(sf::Vector2f(950, 425));
    this->infoText2.setString("CREATE COLOR PRESET");
    
    this->userStringColorText.setFont(this->font);
    this->userStringColorText.setCharacterSize(20);
    this->userStringColorText.setFillColor(sf::Color::Black);
    this->userStringColorText.setOutlineColor(sf::Color::White);
    this->userStringColorText.setOutlineThickness(1);
    this->userStringColorText.setPosition(sf::Vector2f(1050, 330));
    
    this->infoStringText.setFont(this->font);
    this->infoStringText.setCharacterSize(20);
    this->infoStringText.setPosition(sf::Vector2f(1000, 450));
    this->infoStringText.setString("Name:");

    this->infoRGBText.setFont(this->font);
    this->infoRGBText.setCharacterSize(20);
    this->infoRGBText.setPosition(sf::Vector2f(1000, 510));
    this->infoRGBText.setString("(R,G,B):");
    
    this->redColorCount.setFont(this->font);
    this->redColorCount.setCharacterSize(20);
    this->redColorCount.setPosition(sf::Vector2f(10, 135));

    this->greenColorCount.setFont(this->font);
    this->greenColorCount.setCharacterSize(20);
    this->greenColorCount.setPosition(sf::Vector2f(10, 160));
    
    this->blueColorCount.setFont(this->font);
    this->blueColorCount.setCharacterSize(20);
    this->blueColorCount.setPosition(sf::Vector2f(10, 185));

    this->playerText.setFont(this->font);
    this->playerText.setCharacterSize(20);
    this->playerText.setPosition(sf::Vector2f(1005, 547));

    this->playerStringText.setFont(this->font);
    this->playerStringText.setCharacterSize(20);
    this->playerStringText.setPosition(sf::Vector2f(1005, 485));
    
    this->colorFinderShape.setSize(sf::Vector2f(100, 100));
    this->colorFinderShape.setPosition(10, 10);
    this->colorFinderShape.setOutlineColor(sf::Color::White);
    this->colorFinderShape.setOutlineThickness(2);

    this->userColorFinderShape.setSize(sf::Vector2f(150, 50));
    this->userColorFinderShape.setPosition(1000, 315);
    this->userColorFinderShape.setOutlineColor(sf::Color::White);
    this->userColorFinderShape.setOutlineThickness(2);

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
    this->renderButtons();
    this->mWindow->draw(this->RGBText);
    this->mWindow->draw(this->colorFinderShape);
    this->mWindow->draw(this->infoText);
    this->mWindow->draw(this->infoText2);
    this->mWindow->draw(this->infoStringText);
    this->mWindow->draw(this->infoRGBText);
    this->mWindow->draw(this->userColorFinderShape);
    this->mWindow->draw(this->userStringColorText);

    this->mWindow->draw(this->redColorCount);
    this->mWindow->draw(this->greenColorCount);
    this->mWindow->draw(this->blueColorCount);

    this->mWindow->draw(this->playerText);
    this->mWindow->draw(this->playerStringText);
}

void GameEditor::parseUserColor()
{
    std::stringstream ss(this->userEnteredColor);

    for (int i; ss >> i;) {
        this->RGBvalues.push_back(i);
        if (ss.peek() == ',')
            ss.ignore();
    }

    if (!RGBvalues.empty()) {
        this->userColorFinderShape.setFillColor(sf::Color(this->RGBvalues[0], this->RGBvalues[1] , this->RGBvalues[2],255));
        this->userColor = sf::Color(this->RGBvalues[0], this->RGBvalues[1], this->RGBvalues[2], 255);

        for (std::size_t i = 0; i < this->RGBvalues.size(); i++)
            std::cout << this->RGBvalues[i] << std::endl;

    }

    this->RGBvalues.clear();
    this->userEnteredColor.clear();
}

void GameEditor::updateSFMLevents(sf::Event* event)
{
    if (event->type == sf::Event::TextEntered) {

        if (event->text.unicode == '\b') { // handle backspace explicitly
            if (inputVector) {
                if (!playerInput.isEmpty())
                    playerInput.erase(playerInput.getSize() - 1, 1);
            }
            if (inputString) {
                if (!playerStringInput.isEmpty())
                    playerStringInput.erase(playerStringInput.getSize() - 1, 1);
            }

        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Enter)) { // handle backspace explicitly
        }
        else if ((event->text.unicode > 43 && event->text.unicode < 128) && playerInput.getSize() < 12) { // all other keypresses
            if (inputVector) {
                playerInput += static_cast<char>(event->text.unicode);
                std::stringstream ss(playerInput);
                this->userEnteredColor = ss.str();
            }
            if (inputString) {
                playerStringInput += static_cast<char>(event->text.unicode);
                std::stringstream ss(playerStringInput);
                this->userEnteredString = ss.str();
            }
        }
    }
    if (inputVector) {
        playerText.setString(playerInput);
    }
    if (inputString) {
        playerStringText.setString(playerStringInput);
    }
}
