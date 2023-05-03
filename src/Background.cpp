#include "headers/Background.hpp"
#include <SFML/Window/Window.hpp>
#include <iostream>

Background::Background(Player *p,sf::Texture *a,sf::Texture *b,sf::Texture *c)
{
    backgroundTexturea = a;
    backgroundTextureb = b;
    backgroundTexturec = c;
    player = p;
}

Background::~Background()
{

}

void Background::draw(sf::RenderWindow *w)
{
    sf::RectangleShape backgrounda(sf::Vector2f(1920,1129.4));
    sf::RectangleShape backgroundb(sf::Vector2f(1836,1080));
    sf::RectangleShape backgroundc(sf::Vector2f(1836,1080));

    sf::View view = w->getView();

    backgrounda.setTexture(backgroundTexturea);
    backgroundb.setTexture(backgroundTextureb);
    backgroundc.setTexture(backgroundTexturec);

    int position1 = player->getSprite()->getPosition().x;
    int positiona;
    int positionb;
    int positionc;

    if(position1 < 480)
    {
        positiona = position1-960;
        positionb = positiona;
        positionc=positiona;
    }
    else{
        positiona=position1-960;
        positionb=position1*.9-912;
        positionc = position1*.8-864;
    }
    backgrounda.setPosition(positiona,-270);
    backgroundb.setPosition(positionb,-270);
    backgroundc.setPosition(positionc,-270);
     w->draw(backgrounda);
     w->draw(backgroundb);
     w->draw(backgroundc);

}
