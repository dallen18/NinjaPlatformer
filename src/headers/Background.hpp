#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Window/Window.hpp>
#ifndef _Player
    #include "Player.hpp"
#endif

class Background
{
    private:
   
        sf::Texture *backgroundTexturea;
        sf::Texture *backgroundTextureb;
        sf::Texture *backgroundTexturec;
        Player *player;

    public:
        Background(Player *p,sf::Texture *a,sf::Texture *b,sf::Texture *c);
        ~Background();
        void draw(sf::RenderWindow *w);
};
