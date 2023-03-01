#include "headers/Entity.hpp"

sf::Sprite *Entity::getSprite()
{
    return &sprite;
}

float Entity::getXVel()
{
    return xVel;
}

float Entity::getYVel()
{
    return yVel;
}

float Entity::getXMax()
{
    return xMax;
}

float Entity::getYMax()
{
    return yMax;
}

float Entity::getAccel()
{
    return accel;
}

void Entity::setXVel(float x)
{
    xVel = x;
}

void Entity::setYVel(float y)
{
    yVel = y;
}

void Entity::setXMax(float x)
{
    xMax = x;
}

void Entity::setYMax(float y)
{
    yMax = y;
}

void Entity::setAccel(float a)
{
    accel = a;
}

void Entity::setTextures(std::vector<sf::Texture> *t)
{
    textures = t;
}