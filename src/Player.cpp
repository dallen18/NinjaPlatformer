#include "headers/Player.hpp"
#include <iostream>

Player::Player(sf::Texture *_t)
{
    t = *_t;
    s.setTexture(t);
    xVel = 0.0f;
    yVel = 0.0f;
    bottom = false;
    playerBounds = s.getGlobalBounds();
    nextBounds = playerBounds;
    xMax = 10.0f;
    yMax = 10.0f;
    accel = 1.0f;
}

Player::~Player()
{

}

void Player::move(std::vector<sf::RectangleShape> *blockList)
{
    //floatRects contain coordinates and sizes of current state of player and next state
    playerBounds = s.getGlobalBounds();
    nextBounds = playerBounds;

    if(sf::Keyboard::isKeyPressed(sf::Keyboard::D)) //right
    {
        if(xVel < xMax)
        {
            xVel += accel;
        }
    }
    else if(sf::Keyboard::isKeyPressed(sf::Keyboard::A)) //left
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

    bool spacePressed = false;

    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) //up
    {
        if(yVel == 0 && bottom)
        {
            yVel = -yMax;
            spacePressed = true;
            bottom = false;
        }
    }

    if(!spacePressed) //down
    {
        if(yVel < yMax)
        {
            yVel += accel;
        }
    }

    //modifies next state
    nextBounds.left += xVel;
    nextBounds.top += yVel;

    //check collision
    collision(blockList);

    //moves sprite
    s.move(xVel,yVel);
}

void Player::collision(std::vector<sf::RectangleShape> *blockList)
{

    //collision with screen


    //collision with blocks
    for(sf::RectangleShape b : *blockList) //goes through list of blocks
    {
        sf::FloatRect blockBounds = b.getGlobalBounds();

        //collision with bottom of player
        if(playerBounds.top + playerBounds.height <= blockBounds.top
        && nextBounds.top + nextBounds.height > blockBounds.top
        && ((nextBounds.left > blockBounds.left && nextBounds.left < blockBounds.left + blockBounds.height) 
            ||(nextBounds.left + nextBounds.height > blockBounds.left && nextBounds.left + nextBounds.height < blockBounds.left + blockBounds.height)
            ||(nextBounds.left <= blockBounds.left && nextBounds.left + nextBounds.height >= blockBounds.left + blockBounds.height)))
        {
            yVel = 0.0f; //resets y-axis velocity
            s.setPosition(s.getPosition().x, blockBounds.top - playerBounds.height); //sets position to edge of block
            bottom = true; //this boolean is used to check if the player is on the ground and is able to jump. go to move()
        }
        //collision with top of player
        else if(playerBounds.top >= blockBounds.top + blockBounds.height
        && nextBounds.top < blockBounds.top + blockBounds.height
        && ((nextBounds.left > blockBounds.left && nextBounds.left < blockBounds.left + blockBounds.height) 
            ||(nextBounds.left + nextBounds.height > blockBounds.left && nextBounds.left + nextBounds.height < blockBounds.left + blockBounds.height)
            ||(nextBounds.left <= blockBounds.left && nextBounds.left + nextBounds.height >= blockBounds.left + blockBounds.height)))
        {
            yVel = 0.0f;
            s.setPosition(s.getPosition().x, blockBounds.top + blockBounds.height);
        }
        //collision with right of player
        else if(playerBounds.left + playerBounds.width <= blockBounds.left 
        && nextBounds.left + nextBounds.width > blockBounds.left
        && ((nextBounds.top > blockBounds.top && nextBounds.top < blockBounds.top + blockBounds.height) 
            ||(nextBounds.top + nextBounds.height > blockBounds.top && nextBounds.top + nextBounds.height < blockBounds.top + blockBounds.height)
            ||(nextBounds.top <= blockBounds.top && nextBounds.top + nextBounds.height >= blockBounds.top + blockBounds.height)))
        {
            xVel = 0.0f; //resets x-axis velocity
            s.setPosition(blockBounds.left - playerBounds.width, s.getPosition().y);
        }
        //collision with left of player
        else if(playerBounds.left >= blockBounds.left + blockBounds.width
        && nextBounds.left < blockBounds.left + blockBounds.width
        && ((nextBounds.top > blockBounds.top && nextBounds.top < blockBounds.top + blockBounds.height) 
            ||(nextBounds.top + nextBounds.height > blockBounds.top && nextBounds.top + nextBounds.height < blockBounds.top + blockBounds.height)
            ||(nextBounds.top <= blockBounds.top && nextBounds.top + nextBounds.height >= blockBounds.top + blockBounds.height)))
        {
            xVel = 0.0f;
            s.setPosition(blockBounds.left + blockBounds.width, s.getPosition().y);
        }
    }
}

sf::Sprite *Player::getSprite()
{
    return &s;
}

void Player::setTexture(sf::Texture *_t)
{
    t = *_t;
    s.setTexture(t);
}