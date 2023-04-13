#include "headers/Enemy.hpp"
#include <cmath>
#include <iostream>

/*
Constructor of Player class. Takes the following Parameters:
    -std::vector<sf::Texture> *textures: passes textures that will be used by player
    -float xMax: sets max speed in the x-axis for player
    -float yMax: sets max speed in the y-axis for player
    -float accel: sets acceleration rate for player

*/
Enemy::Enemy(sf::Texture *texture, float xMax, float yMax, float accel, int xSize, int ySize)
{   
    setTexture(texture);
    getSprite()->setTexture(*texture); //sets initial texture of sprite as the first texture in list
    setXVel(0.0f);
    setYVel(0.0f);
    setXMax(xMax);
    setYMax(yMax);
    setAccel(accel);
    setXSize(xSize);
    setYSize(ySize);
    getSprite()->setTextureRect(sf::IntRect(0,0,xSize,ySize));
}

Enemy::~Enemy()
{
    delete this;
}

std::string Enemy::getClass()
{
    return "Enemy";
}

void Enemy::move()
{
    if(std::abs(getXVel()) < getXMax())
    {
        setXVel(getXVel() + getAccel());
    }

    if(getYVel() < getYMax())
    {
        int accel = getAccel();
        if(accel < 0)
        {
            accel *= -1;
        }
        setYVel(getYVel() + accel); 
    }
}

/*
Method is responsible for animating the player sprite. It uses the textures passed in the constructor.
It should have different animation for when character is at a stand-still compared to when it is moving.
*/
void Enemy::animation()
{

}
