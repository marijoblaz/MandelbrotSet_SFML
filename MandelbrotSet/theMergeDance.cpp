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
    this->playerText.setPosition(sf::Vector2f(50, 60));
    
    this->infoText1.setFont(font);
    this->infoText1.setCharacterSize(25);
    this->infoText1.setPosition(sf::Vector2f(460, 560));
    this->infoText1.setString("STACK ilustracija"); 

    this->infoText2.setFont(font);
    this->infoText2.setCharacterSize(20);
    this->infoText2.setPosition(sf::Vector2f(10, 630));
    this->infoText2.setString("Nakon sto upisete broj, napravimo polje trazene velicine, razbacamo vrijednosti\npa ga sortiramo merge sortom (koristimo implementaciju s predavanja) i\nnacrtamo (animiramo) sadrzaj stoga.");

    this->kvadraticStogShape.setFillColor(sf::Color::Red);
    this->kvadraticStogShape.setSize(sf::Vector2f(280, 20));

    this->stackBackgrundShape.setFillColor(sf::Color::Black);
    this->stackBackgrundShape.setOutlineColor(sf::Color::White);
    this->stackBackgrundShape.setOutlineThickness(2);
    this->stackBackgrundShape.setSize(sf::Vector2f(300, 400));
    this->stackBackgrundShape.setPosition(sf::Vector2f(400, 150));

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

void theMergeDance::printV(std::vector<int> v)
{
    for (int i = 0; i < v.size(); i++) std::cout << v[i] << " ";
    std::cout << std::endl;
}

void theMergeDance::animirajStack()
{
    if (!vektorKvadraticaPomocni.empty()) {
        if (elapsed1.asMilliseconds() > interval) {
            
            if (kvadraticiVektor.size() < vektorKvadraticaPomocni[0]) {
                this->kvadraticiVektor.push_back(kvadraticStogShape);
                this->kvadraticiVektor.at(kvadraticiVektor.size() - 1).setPosition(sf::Vector2f(410, 540 - vektorKvadraticaPomocni[0] * 30 ));
                //std::cout << vektorKvadraticaPomocni[0] << std::endl;
                //std::cout << this->kvadraticiVektor.at(kvadraticiVektor.size() - 1).getPosition().y << std::endl;
            }
            if (kvadraticiVektor.size() > vektorKvadraticaPomocni[0]) {

                this->kvadraticiVektor.pop_back();
                //this->kvadraticiVektor.at(kvadraticiVektor.size() - 1).setPosition(sf::Vector2f(600, kvadraticiVektor.size() * 30));
            }
            if (kvadraticiVektor.size() == vektorKvadraticaPomocni[0]) {
                //std::cout << "brisem: " << vektorKvadraticaPomocni.at(0);
                vektorKvadraticaPomocni.erase(vektorKvadraticaPomocni.begin());
            }
            clock.restart();
        }
    }
}


std::vector<int> theMergeDance::merge_sort(std::vector<int> m)
{
  
    if (m.size() <= 1) {
        if (stackCounter > 0) {
            this->stackCounter--;
            this->vektorKvadraticaPomocni.push_back(stackCounter);
        }
        return m;
    }

    std::vector<int> left, right, result;
    //Trazim sredinu
    int middle = ((int)m.size() + 1) / 2;

    //Pravim pola vektora
    for (int i = 0; i < middle; i++) {
        left.push_back(m[i]);
    }
    //Pravim drugu polovicu vektora
    for (int i = middle; i < (int)m.size(); i++) {
        right.push_back(m[i]);
    }

    this->stackCounter++;
    this->vektorKvadraticaPomocni.push_back(stackCounter);

    //Opet zovem funkciju rekurzivno i dijelim polovicu na pola
    left = merge_sort(left);

    //Isto i sa desnom polovicom dijelim je opet na pola
    right = merge_sort(right);

    //Sve dok ne dodemo do jednog elementa onda ih spajamo
    result = merge(left, right);

    return result;

}

std::vector<int> theMergeDance::merge(std::vector<int> left, std::vector<int> right)
{
    std::vector<int> result;
    while ((int)left.size() > 0 || (int)right.size() > 0) {
        if ((int)left.size() > 0 && (int)right.size() > 0) {
            if ((int)left.front() <= (int)right.front()) {
                result.push_back((int)left.front());
                left.erase(left.begin());
            }
            else {
                result.push_back((int)right.front());
                right.erase(right.begin());
            }
        }
        else if ((int)left.size() > 0) {
            for (int i = 0; i < (int)left.size(); i++)
                result.push_back(left[i]);
            break;
        }
        else if ((int)right.size() > 0) {
            for (int i = 0; i < (int)right.size(); i++)
                result.push_back(right[i]);
            break;
        }
    }
    return result;
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
    this->elapsed1 = clock.getElapsedTime();
    this->updateButtons();



    if (start) {

        this->napraviPolje();
        this->razbacajPolje();
        this->vektor = this->merge_sort(this->vektor);
        this->showFinish = true;

        //this->printV(this->vektor);
        //this->printV(this->vektorKvadraticaPomocni);

        this->vektor.clear();
        start = false;
    }

    if (showFinish) {

        //setting the speed
        if (this->poljeSize > 100) this->interval = 200;
        if (this->poljeSize < 100) this->interval = 500;

        animirajStack();
    }

}

void theMergeDance::render()
{
    this->mWindow->draw(backgroundSprite);
    this->mWindow->draw(playerText);
    this->mWindow->draw(stackBackgrundShape);
    this->mWindow->draw(infoText1);
    this->mWindow->draw(infoText2);
    for (int i = 0; i < kvadraticiVektor.size(); i++)
    {
        this->mWindow->draw(kvadraticiVektor[i]);
    }
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
        else if ((event->text.unicode > 47 && event->text.unicode < 58) && playerInput.getSize() < 5) { // all other keypresses
            playerInput += static_cast<char>(event->text.unicode);
        }
    }
    playerText.setString("Koliko veliko polje zelite sortirati: " + playerInput);
}
