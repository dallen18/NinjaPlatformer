#include "headers/Player.hpp"
#include <iostream>

/*
Constructor of Player class. Takes the following Parameters:
    -std::vector<sf::Texture> *textures: passes textures that will be used by player
    -float xMax: sets max speed in the x-axis for player
    -float yMax: sets max speed in the y-axis for player
    -float accel: sets acceleration rate for player

*/
Player::Player(std::vector<sf::Texture> *textures, float xMax, float yMax, float accel, int xSize, int ySize)
{   
    setTextures(textures);
    getSprite()->setTexture(textures->front()); //sets initial texture of sprite as the first texture in list
    setXVel(0.0f);
    setYVel(0.0f);
    setXMax(xMax);
    setYMax(yMax);
    setAccel(accel);
    setXSize(xSize);
    setYSize(ySize);

    contactBottom = false;
    jump = false;
    right = false;
    left = false;
}

void Player::move()
{
    float xVel = getXVel();
    float yVel = getYVel();
    float xMax = getXMax();
    float yMax = getYMax();
    float accel = getAccel();

    if(right) //right
    {
        if(xVel < xMax)
        {
            xVel += accel;
        }
    }
    else if(left) //left
    {
        if(xVel > -xMax)
        {
            xVel -= accel;
        }
    }
    else
    {
        if(xVel > 0)
        {
            xVel -= accel;
        }
        else if(xVel < 0)
        {
            xVel += accel;
        }
    }

    if(getJumping()) //up
    {
        // if(yVel == 0 && getContactBottom())
        // {
        //     yVel = -yMax;
        //     setContactBottom(false);
        // }
        yVel = -yMax;
        setContactBottom(false);
        setJumping(false);
    }
    else //down
    {
        if(yVel < yMax)
        {
            yVel += accel;
        }
    }

    setXVel(xVel);
    setYVel(yVel);
}

bool Player::getContactBottom()
{
    return contactBottom;
}

bool Player::getJumping()
{
    return jump;
}

bool Player::getRight()
{
    return right;
}

bool Player::getLeft()
{
    return left;
}

int Player::getHealth()
{
    return health;
}

void Player::setJumping(bool b)
{
    jump = b;
}

void Player::setRight(bool b)
{
    right = b;
}

void Player::setLeft(bool b)
{
    left = b;
}

void Player::setContactBottom(bool b)
{
    contactBottom = b;
}

void Player::setHealth(int h)
{
    health = h;
}

void Player::decreaseHealth()
{
    if(health != 0)
    {
        health -= 1;
    }
}

/*
Method is responsible for animating the player sprite. It uses the textures passed in the constructor.
It should have different animation for when character is at a stand-still compared to when it is moving.
*/
void Player::animation()
{

}
