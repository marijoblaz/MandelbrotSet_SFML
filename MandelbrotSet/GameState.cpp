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

    static const std::vector<sf::Color> colors{
        {0,0,0},
        {213,67,31},
        {251,255,121},
        {62,123,89},
        {43,30,118},
        {0,55,247},
        {100,0,0},
        {0,100,0},
    };

    static const auto max_color = colors.size() - 1;


    double mu = 1.0 * iter / maxIter;

    //scale mu to be in the range of colors
    mu *= max_color;

    auto i_mu = static_cast<size_t>(mu);
    auto color1 = colors[i_mu];
    auto color2 = colors[std::min(i_mu + 1, max_color)];

    sf::Color c = linear_interpolation(color1, color2, mu - i_mu);
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

GameState::GameState(sf::RenderWindow* window, std::stack<State*>* states) : State(window, states)
{
    this->mWindow = window;
    this->mbSetImage.create(WIDTH, HEIGHT, sf::Color::Red);
    this->renderMBSet();
}

GameState::~GameState()
{
}

void GameState::render()
{
    this->mWindow->draw(mbSetSprite);
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
                    maxIter += 20;
                    zoom_x(2);
                }
                else if (event->mouseWheelScroll.delta < 0) {
                    maxIter -= 20;
                    zoom_x(1.0 / 2);
                }
            }
            this->renderMBSet();
        }
    }
}

void GameState::update()
{

}
