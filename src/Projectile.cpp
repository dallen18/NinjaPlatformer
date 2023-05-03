#include "headers/Projectile.hpp"
#include <SFML/Graphics/Rect.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/System/Vector2.hpp>
#include <iostream>

Projectile::Projectile(sf::Texture *t, float xvel, float yvel, float x, float y)
{
    setX(x);
    setY(y);
    setAccel(.1f);
    setXVel(xvel);
    setYVel(yvel);
    setXMax(10.0f);
    setYMax(10.0f);
    setTexture(t);
    getSprite()->setTexture(*t); 
    getSprite()->setTextureRect(sf::IntRect(0,0,11,11));
    getSprite()->setPosition(x,y);
}

Projectile::~Projectile()
{
    delete this;
}

void Projectile::move()
{
    if(getYVel() < getYMax())
    {
        setYVel(getYVel() + getAccel());
    }
}
