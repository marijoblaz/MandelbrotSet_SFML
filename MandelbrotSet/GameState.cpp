#include "GameState.h"
#pragma warning(disable : 4996) //_CRT_SECURE_NO_WARNINGS



std::string GameState::get_timestamp()
{
    time_t rawtime;
    struct tm* timeinfo;
    char buffer[80];

    time(&rawtime);
    timeinfo = localtime(&rawtime);

    strftime(buffer, 80, "%d-%m-%Y %H-%M-%S", timeinfo);
    return std::string(buffer);
}

void GameState::renderMBSet()
{
    for (unsigned int x = 0; x < WIDTH; x++) for (unsigned y = 0; y < HEIGHT; y++)
    {
        mbSetImage.setPixel(x, y, this->getMendelColor(x, y));
    }

    this->mbSetTexture.loadFromImage(mbSetImage);
    this->mbSetSprite.setTexture(mbSetTexture);
}

sf::Color GameState::getMendelColor(unsigned int x, unsigned int y) {
    //Mapping
    double cr = map(x, 0, WIDTH, minRe, maxRe);
    double ci = map(y, 0, HEIGHT, minIm, maxIm);

    double re = 0, im = 0;


    unsigned int iter;
    for (iter = 0; iter < maxIter; iter++)
    {
        double tr = re * re - im * im + cr;
        im = 2 * re * im + ci;
        re = tr;

        if (re * re + im * im > 2) break;

    }
    if (iter == maxIter)
        iter = 0;

    static const auto max_color = colorsPresetActive.size() - 1;


    double mu = 1.0 * iter / maxIter;

    //scale mu to be in the range of colors
    mu *= max_color;

    auto i_mu = static_cast<size_t>(mu);
    auto color1 = colorsPresetActive[i_mu];
    auto color2 = colorsPresetActive[std::min(i_mu + 1, max_color)];

    sf::Color c = linear_interpolation(color1, color2, mu - i_mu);
    return c;
}

double GameState::map(double x, double in_min, double in_max, double out_min, double out_max)
{
    return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}

sf::Color GameState::linear_interpolation(const sf::Color& v, const sf::Color& u, double a)
{
    auto const b = 1 - a;
    return sf::Color(b * v.r + a * u.r, b * v.g + a * u.g, b * v.b + a * u.b);
}

void GameState::initButtons()
{
    this->font.loadFromFile("Fonts/arial.ttf");
    //Creating buttons

    buttons["BACK"] = new Button(1050, 635, 100, 50,
        &font, "BACK",
        sf::Color(0, 0, 0),
        sf::Color(255, 255, 255),
        sf::Color(40, 40, 40), this->mWindow, BTN_STANDARD);

    buttons["SAVE LOCATION"] = new Button(50, 635, 250, 50,
        &font, "SAVE LOCATION",
        sf::Color(0, 0, 0),
        sf::Color(255, 255, 255),
        sf::Color(40, 40, 40), this->mWindow, BTN_STANDARD);

    buttons["ANALYSE"] = new Button(50, 525, 250, 50,
        &font, "ANALYSE",
        sf::Color(0, 30, 0),
        sf::Color(255, 255, 255),
        sf::Color(0, 155, 0), this->mWindow, BTN_STANDARD);

    buttons["EDITOR"] = new Button(50, 470, 250, 50,
        &font, "EDITOR",
        sf::Color(0, 0, 30),
        sf::Color(255, 255, 255),
        sf::Color(0, 0, 155), this->mWindow, BTN_STANDARD);

    buttons["SAVE IMAGE"] = new Button(50, 580, 250, 50,
        &font, "SAVE IMAGE",
        sf::Color(0, 0, 0),
        sf::Color(255, 255, 255),
        sf::Color(40, 40, 40), this->mWindow, BTN_STANDARD);

    buttons["AUTO"] = new Button(300, 20, 300, 50,
        &font, "DISABLE AUTO ITERATION",
        sf::Color(0, 0, 0),
        sf::Color(0, 255, 0),
        sf::Color(40, 40, 40), this->mWindow, BTN_TOGGLE);

    buttons["PLUS"] = new Button(1150, 50, 30, 50,
        &font, "+",
        sf::Color(0, 0, 0),
        sf::Color(0, 255, 0),
        sf::Color(40, 40, 40), this->mWindow, BTN_STANDARD);

    buttons["MINUS"] = new Button(1150, 105, 30, 50,
        &font, "-",
        sf::Color(0, 0, 0),
        sf::Color(0, 255, 0),
        sf::Color(40, 40, 40), this->mWindow, BTN_STANDARD);
}

void GameState::initText()
{
    this->maxIterationsText.setFont(this->font);
    this->maxIterationsText.setCharacterSize(20);
    this->maxIterationsText.setColor(sf::Color::White);
    this->maxIterationsText.setPosition(10, 10);

    this->currentIterationsText.setFont(this->font);
    this->currentIterationsText.setCharacterSize(20);
    this->currentIterationsText.setColor(sf::Color::White);
    this->currentIterationsText.setPosition(10, 40);

    this->analysedImageText.setFont(this->font);
    this->analysedImageText.setCharacterSize(20);
    this->analysedImageText.setColor(sf::Color::White);
    this->analysedImageText.setPosition(10, 70);

    this->analysedImageText2.setFont(this->font);
    this->analysedImageText2.setCharacterSize(20);
    this->analysedImageText2.setColor(sf::Color::White);
    this->analysedImageText2.setPosition(10, 95);

    this->locationText.setFont(this->font);
    this->locationText.setCharacterSize(20);
    this->locationText.setColor(sf::Color::White);
    this->locationText.setPosition(500, 680);
}

void GameState::renderButtons()
{
    //Rendering the buttons
    for (auto& it : buttons)
    {
        it.second->render(this->mWindow);
    }
}

void GameState::updateButtons()
{
    this->elapsed1 = clock.getElapsedTime();

    //Updates all button and handlles funcs
    for (auto& it : buttons)
    {
        //Update pressing and pass the mouse Positions 
        it.second->updatePress();
    }

    //Backs
    if (buttons["BACK"]->isPressed()) {
        this->endState();
    }

    //Saves
    if (buttons["SAVE IMAGE"]->isPressed()) {
        this->mbSetImage.saveToFile("image" + this->get_timestamp() + ".png");
        
    }

    //Saves
    if (buttons["ANALYSE"]->isPressed() && elapsed1.asMilliseconds() > interval) {
        this->intValueAndIterationMM.insert(std::pair <int, int>(getImageAnalyse(), this->maxIter));
        this->intrestingValues.push(getImageAnalyse());
        this->analysedImageText.setString("Most interesting image at: "+std::to_string(intrestingValues.top())+"%");
        this->analysedImageText2.setString("Current image interest at: "+std::to_string(getImageAnalyse())+"%");
        //std::cout << "PC: " << getImageAnalyse() << std::endl;
        clock.restart();
    }
    
    //Inc
    if (buttons["PLUS"]->isPressed() && elapsed1.asMilliseconds() > interval) {
        this->zoomIn(true);
        this->renderMBSet();
        clock.restart();
    } 

    //Dec
    if (buttons["MINUS"]->isPressed() && elapsed1.asMilliseconds() > interval) {
        this->zoomOut(true);
        this->renderMBSet();
        clock.restart();
    } 
    
    //Auto mod
    if (buttons["AUTO"]->isPressed()) {
        this->autoIterations = false;
    }
    else {

        this->autoIterations = true;
    }

    //Save loc
    if (buttons["SAVE LOCATION"]->isPressed() && elapsed1.asMilliseconds() > interval) {
        this->updateLocations();
        
        clock.restart();
    }

    //Save loc
    if (buttons["EDITOR"]->isPressed() && elapsed1.asMilliseconds() > interval) {
        this->states->push(new GameEditor(this->mWindow, this->states));
        this->states->top()->setImage(&this->mbSetImage);
        clock.restart();
    }
}

void GameState::updateMaxIterationsText()
{
    this->locationText.setString(std::to_string(this->minRe) + ", " + 
        std::to_string(this->maxRe) + ", " +
        std::to_string(this->minIm) + ", " +
        std::to_string(this->maxIm));

    if (!this->maxIterations.empty()) { this->maxIterationsText.setString("Max iteration: " + std::to_string(*this->maxIterations.begin())); }
}

void GameState::updateLocations()
{

    this->locationCord.push_back(this->minRe);
    this->locationCord.push_back(this->maxRe);
    this->locationCord.push_back(this->minIm);
    this->locationCord.push_back(this->maxIm);

    this->locations.insert(this->locationCord);
    this->locationCord.clear();

    this->mySaveFile.open("saved_locations.txt");
    for (auto& i : this->locations)
    {
        this->mySaveFile << i.at(0)<<", " << i.at(1) << ", " << i.at(2) << ", " << i.at(3) << std::endl;
    }
    this->mySaveFile.close();
    
}

void GameState::zoomIn(bool overRide)
{
    if (autoIterations || overRide) {
        maxIter += 10;
        this->maxIterations.insert(maxIter);
        this->currentIterationsText.setString("Curr iteration: " + std::to_string(maxIter));
    }
    
}

void GameState::zoomOut(bool overRide)
{
    if (autoIterations || overRide) {
        if (maxIter > 10) {
            maxIter -= 10;
            this->maxIterations.insert(maxIter);
            this->currentIterationsText.setString("Curr iteration: " + std::to_string(maxIter));
        }
    }
   
}

int GameState::getImageAnalyse()
{

    for (int i = 0; i < WIDTH; i++)
    {
        for (int j = 0; j < HEIGHT; j++)
        {
            this->piexelColor = this->mbSetImage.getPixel(i,j);
            colorCount += (unsigned long long)this->piexelColor.r + (unsigned long long)this->piexelColor.g + (unsigned long long)this->piexelColor.b;
        }

    }

    long long x = colorCount;
    long long in_min = 0; 
    long long in_max = 660960000;
    long long out_min = 0;
    long long out_max = 100;
    
    
    this->colorCount = 0;
    return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;;
}

GameState::GameState(sf::RenderWindow* window, std::stack<State*>* states) : State(window, states)
{
    this->mWindow = window;
    this->mbSetImage.create(WIDTH, HEIGHT, sf::Color::Red);
    this->colorsPresetActive = this->colorsPreset1;
    this->renderMBSet();
    this->initButtons();
    this->initText();
}

GameState::~GameState()
{
}

void GameState::render()
{
    this->mWindow->draw(mbSetSprite);
    this->renderButtons();
    this->mWindow->draw(this->maxIterationsText);
    this->mWindow->draw(this->currentIterationsText);
    this->mWindow->draw(this->locationText);
    this->mWindow->draw(this->analysedImageText);
    this->mWindow->draw(this->analysedImageText2);
}

void GameState::updateSFMLevents(sf::Event* event)
{
    if (event->type == sf::Event::KeyPressed) {
        //move delta
        double w = (maxRe - minRe) * 0.05;
        double h = (maxIm - minIm) * 0.05;

        if (event->key.code == sf::Keyboard::A) { minRe -= w, maxRe -= w; }
        if (event->key.code == sf::Keyboard::D) { minRe += w, maxRe += w; }
        if (event->key.code == sf::Keyboard::W) { minIm -= h, maxIm -= h; }
        if (event->key.code == sf::Keyboard::S) { minIm += h, maxIm += h; }

        if (event->key.code == sf::Keyboard::R) { minRe = -2.5, maxRe = 1, minIm = -1, maxIm = 1; this->maxIter = 50; }
        if (event->key.code == sf::Keyboard::O) {
            
        }

        if (event->key.code == sf::Keyboard::Escape) { this->endState(); }

        if (event->key.code == sf::Keyboard::E) {
            this->mbSetImage.saveToFile("MBset" + this->get_timestamp() + ".png");
        }
        this->renderMBSet();
    }
    //Set Iteration level by mouse wheel
        //the more iteration level the better image result
    if (event->type == sf::Event::MouseWheelScrolled)
    {

        if (event->MouseWheelScrolled)
        {
            auto zoom_x = [&](double z)
            {
                //mouse point will be new center point

                double cr = minRe + (maxRe - minRe) * event->mouseWheelScroll.x / WIDTH;
                double ci = minIm + (maxIm - minIm) * event->mouseWheelScroll.y / HEIGHT;

                //zoom
                double tminr = cr - (maxRe - minRe) / 2 / z;
                maxRe = cr + (maxRe - minRe) / 2 / z;
                minRe = tminr;

                double tmini = ci - (maxIm - minIm) / 2 / z;
                maxIm = ci + (maxIm - minIm) / 2 / z;
                minIm = tmini;
            };

            if (event->mouseWheelScroll.wheel == sf::Mouse::VerticalWheel)
            {
                if (event->mouseWheelScroll.delta > 0) {
                    this->zoomIn(false);
                    zoom_x(2);
                }
                else if (event->mouseWheelScroll.delta < 0) {
                    this->zoomOut(false);
                    zoom_x(1.0 / 2);
                }
            }
            this->renderMBSet();
        }
    }
}

void GameState::update()
{
    this->updateButtons();
    this->updateMaxIterationsText();
}
