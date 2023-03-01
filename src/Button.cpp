#include "headers/Button.hpp"

Button::Button(std::string _id, std::string _text)//, std::function<void()> _action)
{
    rect.setSize(sf::Vector2f(50.0f,50.0f));
    rect.setFillColor(sf::Color::Red);
    text.setString(_text);
    id = _id;

    //action() = _action();
}

Button::~Button()
{

}

sf::RectangleShape *Button::getRect()
{
    return &rect;
}

std::string Button::getID()
{
    return id;
}