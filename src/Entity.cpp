#include "headers/Entity.hpp"
#include <SFML/Graphics/Texture.hpp>

float Entity::getX()
{
    return x;
}

float Entity::getY()
{
    return y;
}

void Entity::setX(float v)
{
    x = v;
}

void Entity::setY(float v)
{
    y = v;
}

sf::Sprite *Entity::getSprite()
{
    return &sprite;
}

sf::Texture *Entity::getTexture()
{
    return texture;
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

int Entity::getXSize()
{
    return xSize;
}

int Entity::getX()
{
    return x;
}

int Entity::getY()
{
    return y;
}

int Entity::getYSize()
{
    return ySize;
}

std::string Entity::getClass()
{
    return "Entity";
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

void Entity::setXSize(int s)
{
    xSize = s;
}

void Entity::setYSize(int s)
{
    ySize = s;
}

void Entity::setTexture(sf::Texture *t)
{
    texture = t;
}

void Entity::setX(int m)
{
    x = m;
}

void Entity::setY(int m)
{
    y = m;
}

void Entity::animation()
{
    
}

void Entity::move()
{
   
}
