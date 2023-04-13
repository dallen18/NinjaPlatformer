#include "headers/Menu.hpp"

Menu::Menu(std::string _title, std::vector<Button> *_buttons, sf::Font *_font)
{
    title.setFont(*_font);

    title.setString(_title);

    title.setCharacterSize(60);

    title.setFillColor(sf::Color::Blue);

    buttons = _buttons;
}

Menu::~Menu()
{

}

void Menu::draw(sf::RenderWindow *w)
{
    sf::Vector2f windowSize = w->getView().getSize();

    sf::Vector2f windowPosition = w->getView().getCenter() - windowSize / 2.0f;

    sf::RectangleShape menuRect(sf::Vector2f(windowSize.x,windowSize.y));

    menuRect.setFillColor(sf::Color(0,0,0,200));

    menuRect.setPosition(windowPosition);

    title.setPosition(windowPosition.x + windowSize.x / 2 - title.getGlobalBounds().width / 2, windowPosition.y + windowSize.y / 2 - 150);

    for(int i = 0; i < buttons->size(); i++)
    {
        buttons->at(i).setPosition(windowPosition.x + windowSize.x / 2 -  buttons->at(i).getRect()->getGlobalBounds().width / 2, windowPosition.y + windowSize.y / 2 + 50 * (i - 1));
    }

    w->draw(menuRect);

    w->draw(title);

    for(Button btn : *buttons)
    {
        btn.draw(w);
    }
}