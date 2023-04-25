#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Window/Window.hpp>
#ifndef _Player
    #include "Player.hpp"
#endif

class Hud
{
    private:
        Player *player;
        sf::Texture *heartTexture;

    public:
        Hud(Player *p, sf::Texture *t);
        ~Hud();
        void draw(sf::RenderWindow *w);
};
