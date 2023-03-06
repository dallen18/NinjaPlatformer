#include "headers/Menu.hpp"

Menu::Menu(std::string _title, std::vector<Button> *_buttons, sf::Font *_font)
{
    title.setFont(*_font);

    title.setString(_title);

    title.setCharacterSize(60);

    title.setFillColor(sf::Color::Blue);

    buttons = _buttons;

    rectHeight += title.getGlobalBounds().height;

    rectHeight += 35;

    for(Button btn : *buttons)
    {
        rectHeight += btn.getRect()->getGlobalBounds().height;
    }

    float y = 540 - rectHeight / 2 + 15;

    for(int i = 0; i < buttons->size(); i++)
    {
        buttons->at(i).setPosition(960 -  buttons->at(i).getRect()->getGlobalBounds().width / 2, y);
        y +=  buttons->at(i).getRect()->getGlobalBounds().height;
    }
}

Menu::~Menu()
{

}

void Menu::draw(sf::RenderWindow *w)
{
    sf::Vector2u windowSize= w->getSize();

    sf::RectangleShape menuRect(sf::Vector2f(windowSize.x,windowSize.y));

    menuRect.setFillColor(sf::Color(0,0,0,200));

    title.setPosition(windowSize.x / 2 - title.getGlobalBounds().width / 2, windowSize.y / 2 - rectHeight / 2 - title.getCharacterSize());

    sf::RectangleShape bar(sf::Vector2f(400,5.0f));

    bar.setFillColor(sf::Color::White);

    bar.setPosition(windowSize.x / 2 - bar.getSize().x / 2, windowSize.y / 2 - rectHeight / 2 + 15);

    w->draw(menuRect);

    w->draw(title);

    w->draw(bar);

    for(Button btn : *buttons)
    {
        btn.draw(w);
    }
}