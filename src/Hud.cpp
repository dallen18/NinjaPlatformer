#include "headers/Hud.hpp"
#include <SFML/Window/Window.hpp>
#include <iostream>

Hud::Hud(Player *p, sf::Texture *t)
{
    player = p;
    heartTexture = t;
}

Hud::~Hud()
{

}

void Hud::draw(sf::RenderWindow *w)
{
    //draws hearts
    for(int i = 0; i < player->getHealth(); i++)
    {
        sf::Vector2u textureSize = heartTexture->getSize();
        sf::RectangleShape heart(sf::Vector2f(64,64));
        heart.setTexture(heartTexture);
        sf::View view = w->getView();
        //heart.setPosition((view.getCenter().x - view.getSize().x / 2 + (i + 1) * 64)-48, 400);
        heart.setPosition(view.getCenter().x - view.getSize().x / 2 + (i + 1) * 64, view.getCenter().y - view.getSize().y / 2 + 100);
        w->draw(heart);
    }
}
