#include "headers/Player.hpp"
#include <SFML/Graphics/Rect.hpp>
#include <SFML/System/Vector2.hpp>
#include <iostream>
#include <cmath>

/*
Constructor of Player class. Takes the following Parameters:
    -std::vector<sf::Texture> *textures: passes textures that will be used by player
    -float xMax: sets max speed in the x-axis for player
    -float yMax: sets max speed in the y-axis for player
    -float accel: sets acceleration rate for player
*/
Player::Player(sf::Texture *texture, float xMax, float yMax, float accel, int xSize, int ySize, int x, int y)
{   
    setTexture(texture);
    getSprite()->setTexture(*texture);
    getSprite()->setTextureRect(sf::IntRect(0,0,xSize,ySize));
    setXVel(0.0f);
    setYVel(0.0f);
    setXMax(xMax);
    setYMax(yMax);
    setAccel(accel);
    setXSize(xSize);
    setYSize(ySize);
    //setX(x);
    //setY(y);

    contactBottom = false;
    jump = false;
    right = false;
    left = false;
}

Player::~Player()
{ 
    //delete this;
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
        setRight(false);
    }
    else if(left) //left
    {
        if(xVel > -xMax)
        {
            xVel -= accel;
        }
        setLeft(false);
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

    if(getJumping() && contactBottom) //up
    {
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
        setContactBottom(false);
    }

    setXVel(xVel);
    setYVel(yVel); 
}

void Player::createAttack()
{
    sf::Vector2f mousePos = (sf::Vector2f)sf::Mouse::getPosition();
    sf::Vector2f playerPos = {960,540};
    sf::Vector2f difference = mousePos - playerPos;
    float hypotenuse = std::sqrt(std::pow(difference.x,2) + std::pow(difference.y,2));
    float velX = 10 * difference.x / hypotenuse;
    float velY = 10 * difference.y / hypotenuse;
    if(num > 0)
    {
        shurikens.push_back(new Projectile(getTexture(), velX, velY, getX(), getY()));
        num -= 1;
    }
}

std::vector<Projectile*> *Player::getShurikens()
{
    return &shurikens;
}

bool Player::getAttack()
{
    return attack;
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

void Player::setAttack(bool b)
{
    attack = b;
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
