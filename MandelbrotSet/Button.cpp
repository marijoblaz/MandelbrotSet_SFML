#include "Button.h"

Button::Button(float x, float y, float width, float height, sf::Font* font, std::string text, sf::Color idleColor, sf::Color pressColor, sf::Color hoverColor, sf::RenderWindow* window, short unsigned style)
{

	//Setting up the buttons
	this->window = window;

	this->buttonState = BTN_IDLE;
	this->buttonStyle = style;

	this->font = font;

	this->idleColor = idleColor;
	this->hoverColor = hoverColor;
	this->pressColor = pressColor;

	switch (this->buttonStyle) {
	case BTN_STANDARD:
		this->bShape.setSize(sf::Vector2f(width, height));
		this->bShape.setPosition(sf::Vector2f(x, y));
		this->bShape.setOutlineColor(sf::Color::White);
		this->bShape.setOutlineThickness(1.5);

		this->text.setFont(*this->font);
		this->text.setString(text);
		this->text.setFillColor(sf::Color::White);
		this->text.setLetterSpacing(1.4f);
		this->text.setCharacterSize(25);


		this->text.setPosition(
			sf::Vector2f(
				(this->bShape.getPosition().x + (this->bShape.getGlobalBounds().width / 2.f)) - this->text.getGlobalBounds().width / 2.f - 2.5,
				(this->bShape.getPosition().y + (this->bShape.getGlobalBounds().height / 2.f)) - this->text.getGlobalBounds().height / 2.f - 7.5));

		this->bShape.setFillColor(this->idleColor);
		break;
	case BTN_TOGGLE:
		this->bShapeCirc.setRadius(10);
		this->bShapeCirc.setPosition(sf::Vector2f(x, y));
		this->bShapeCirc.setOutlineColor(sf::Color::White);
		this->bShapeCirc.setOutlineThickness(5);

		this->text.setFont(*this->font);
		this->text.setString(text);
		this->text.setFillColor(sf::Color::White);
		this->text.setLetterSpacing(1.4f);
		this->text.setCharacterSize(25);


		this->text.setPosition(
			sf::Vector2f(
				(this->bShapeCirc.getPosition().x + 40),
				(this->bShapeCirc.getPosition().y + (this->bShapeCirc.getGlobalBounds().height / 2.f)) - this->text.getGlobalBounds().height / 2.f - 12.5));

		this->bShape.setFillColor(this->idleColor);
		break;
	}


}
Button::~Button()
{
}

//Update functions

void Button::updateMousePos()
{
	this->mousePosScreen = sf::Mouse::getPosition();
	this->mousePosWindow = sf::Mouse::getPosition(*this->window);
	this->mousePosView = this->window->mapPixelToCoords(sf::Mouse::getPosition(*this->window));
}

void Button::updatePress()
{
	/* Update the bools for hover and press*/
	this->updateMousePos();
	if (!this->toogle)
		this->buttonState = BTN_IDLE;


	//Hover
	if (this->bShape.getGlobalBounds().contains(mousePosView) || this->bShapeCirc.getGlobalBounds().contains(mousePosView)) {
		if (!this->toogle)
			this->buttonState = BTN_HOVERED;

		//Presed
		if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
			this->buttonState = BTN_PRESSED;
			if (this->buttonStyle == BTN_TOGGLE) {
				this->elapsed1 = clock.getElapsedTime();
				if (this->elapsed1.asMilliseconds() > 250) {
					this->toogle = !this->toogle;
					this->buttonState = BTN_PRESSED;
					//std::cout << toogle << std::endl;
					this->clock.restart();
				}

			}
		}
	}
	switch (this->buttonState)
	{
	case BTN_IDLE:
		this->bShape.setFillColor(this->idleColor);
		this->bShapeCirc.setFillColor(this->idleColor);
		this->text.setFillColor(sf::Color::White);
		break;
	case BTN_HOVERED:
		this->bShape.setFillColor(this->hoverColor);
		this->bShapeCirc.setFillColor(this->hoverColor);
		this->text.setFillColor(sf::Color::White);
		break;
	case BTN_PRESSED:
		this->bShape.setFillColor(this->pressColor);
		this->bShapeCirc.setFillColor(this->pressColor);
		if (this->buttonStyle != BTN_TOGGLE) {
			this->text.setFillColor(sf::Color::Black);
		}
		break;
	default:
		//This should not happend!
		this->bShape.setFillColor(sf::Color::Blue);
		this->bShapeCirc.setFillColor(sf::Color::Blue);
		break;
	}


}
const bool Button::isPressed() const
{
	//returns if buttin is pressed
	if (this->buttonState == BTN_PRESSED || toogle)
		return true;
	else
	{
		return false;
	}
}

//Render function
void Button::render(sf::RenderTarget* target)
{
	target->draw(this->bShape);
	target->draw(this->bShapeCirc);
	target->draw(this->text);
}
