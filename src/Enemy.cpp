#include "headers/Enemy.hpp"
#include <cmath>
#include <iostream>
#include <chrono>

/*
Constructor of Player class. Takes the following Parameters:
    -std::vector<sf::Texture> *textures: passes textures that will be used by player
    -float xMax: sets max speed in the x-axis for player
    -float yMax: sets max speed in the y-axis for player
    -float accel: sets acceleration rate for player

*/
Enemy::Enemy(sf::Texture *texture, float xMax, float yMax, float accel, int xSize, int ySize, bool j)
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
    setJumping(j);
    setContactBottom(true);
} 

Enemy::Enemy(){
    this->Sprite();
    this->Texture();
    this->variables();
    this->animations();
}
    
   // animation(this->getTexture(),0.5f, 0.5f, true);


Enemy::~Enemy()
{
    delete this;
}

std::string Enemy::getClass()
{
    return "Enemy";
}

bool Enemy::getContactBottom()
{
    return contactBottom;
}

bool Enemy::getJumping()
{
    return jumping;
}

bool Enemy::getAlive()
{
    return alive;
}

void Enemy::setContactBottom(bool b)
{
    contactBottom = b;
}

void Enemy::setJumping(bool b)
{
    jumping = b;
}

void Enemy::setAlive(bool b)
{
    alive = b;
}

void Enemy::move()
{
    if(std::abs(getXVel()) < getXMax())
    {
        setXVel(getXVel() + getAccel());
    }

    if(getContactBottom() && getJumping())
    {
        setYVel(-getYMax());
        setContactBottom(false);
    }
    else
    {
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
}

void Enemy::dyingTexture(){
    if(!this->dieTexture.loadFromFile("resources/Images/Enemies/bug/bug_death.png")){
        std::cout <<"could not load"<< "\n";
    }
}

void Enemy::variables(){
    this->animationState = ENEMY_MOVING_LEFT;
}

/*
Method is responsible for animating the player sprite. It uses the textures passed in the constructor.
It should have different animation for when character is at a stand-still compared to when it is moving.
*/

void Enemy::UpdateAnimation(){
    if(this->animationState == ENEMY_MOVING_LEFT && this->alive == true){
        if(this->enAnimationTimer.getElapsedTime().asSeconds() >= 0.4f)
        {
            this->currentFrame.left += 35.f;
            if(this->currentFrame.left >= 140.f)
               this->currentFrame.left = 0;
        }
            this->enAnimationTimer.restart();
            this->getSprite()->setTextureRect(this->currentFrame);    
    }else if(this->animationState == ENEMY_MOVING_RIGHT && this->alive == true){
        if(this->enAnimationTimer.getElapsedTime().asSeconds() >= 0.4f)
        {
            this->currentFrame.left += 35.f;
            if(this->currentFrame.left >= 140.f)
               this->currentFrame.left = 0;
        }
            this->enAnimationTimer.restart();
            this->getSprite()->setTextureRect(this->currentFrame);    
    }else{
        this->enAnimationTimer.restart();
    }
}



void Enemy::update(){
    this->UpdateAnimation();
}

void Enemy::Texture(){

}

void Enemy::render(sf::RenderTarget & target){
    target.draw(this->sprite);
}

void Enemy::Sprite(){
    this->sprite.setTexture(this->dieTexture);
    this->currentFrame =sf::IntRect(0,0,35,35);
    this->sprite.setTextureRect(sf::IntRect(0,0,35,35));
    this->sprite.setTextureRect(this->currentFrame);
    this->sprite.setScale(2.5f,2.5f);
}

void Enemy::animations(){
    this->enAnimationTimer.restart();
}









