#include "headers/Button.hpp"
#include <iostream>

Button::Button(std::string _id, std::string _text, sf::Font *_font)
{
    rect.setSize(sf::Vector2f(250.0f,50.0f));
    rect.setFillColor(sf::Color::Transparent);
    id = _id;
    
    text.setFont(*_font);

    text.setString(_text);

    text.setCharacterSize(30);

    text.setFillColor(sf::Color::Blue);
}

Button::~Button()
{

}

void Button::highlightButton(sf::RenderWindow *w)
{
    //creates white dot next to button
    sf::CircleShape circle(5.0f);
    circle.setFillColor(sf::Color::White);
    circle.setPosition(text.getPosition().x - 15.0f,text.getPosition().y + circle.getRadius() * 2.5);
    w->draw(circle);
}

sf::RectangleShape *Button::getRect()
{
    return &rect;
}

std::string Button::getID()
{
    return id;
}

void Button::setPosition(float x, float y)
{
    rect.setPosition(x,y);
    text.setPosition(x + rect.getGlobalBounds().width / 2 - text.getGlobalBounds().width / 2,y);
}

void Button::draw(sf::RenderWindow *w)
{
    w->draw(rect);
    w->draw(text);
}