#include "UI.h"

void UI::initFonts()
{
	if (font.loadFromFile("fonts/arial.ttf")) {
		this->magText.setFont(font);
		this->iterText.setFont(font);
		this->posText.setFont(font);
	}
}

void UI::initText()
{
	this->magText.setCharacterSize(30);
	this->iterText.setCharacterSize(30);
	this->posText.setCharacterSize(30);

	this->magText.setPosition(sf::Vector2f(100,100));
	this->iterText.setPosition(sf::Vector2f(100,140));
	this->posText.setPosition(sf::Vector2f(100,180));
}

UI::UI()
{
	this->initFonts();
	this->initText();
}

UI::~UI()
{
}

void UI::render(sf::RenderTarget& target)
{
	target.draw(this->magText);
	target.draw(this->iterText);
	target.draw(this->posText);
}

void UI::update()
{
}

void UI::setIterText(int iter)
{
	this->iterText.setString("Iterations per pixel: " + std::to_string(iter));
}

void UI::setPosText(double posX, double posY)
{
	this->posText.setString("X: " + std::to_string(posX) + "/" + "Y: " + std::to_string(posY));
}

void UI::setMagText(int mag)
{
	this->magText.setString("Zoom level: "+ std::to_string(mag));
}
