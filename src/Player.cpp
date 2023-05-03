#include "headers/Player.hpp"
#include <SFML/Graphics/Rect.hpp>
#include <SFML/Graphics/View.hpp>
#include <SFML/System/Vector2.hpp>
#include <chrono>
#include <iostream>
#include <cmath>


/*
Constructor of Player class. Takes the following Parameters:
    -std::vector<sf::Texture> *textures: passes textures that will be used by player
    -float xMax: sets max speed in the x-axis for player
    -float yMax: sets max speed in the y-axis for player
    -float accel: sets acceleration rate for player
*/
Player::Player()
{   this->iVariables();   
    this->iTexture();
    this->iSprite();
    this->iAnimations(); 
}

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

void Player::createAttack(const sf::View &view)
{
    if(method == 0)
    {
        sf::Vector2f mousePos = (sf::Vector2f)sf::Mouse::getPosition();
        int position1 = getSprite()->getPosition().x;
        
        mousePos.x = mousePos.x / 2;
        mousePos.y = mousePos.y / 2;
        mousePos += view.getCenter();//sf::Vector2f{getX(),getY()};
        mousePos.x -= 480;
        mousePos.y -= 270;

        sf::Vector2f playerPos = {getX(),getY()};
        sf::Vector2f difference = mousePos - playerPos;
        float hypotenuse = std::sqrt(std::pow(difference.x,2) + std::pow(difference.y,2));
        float velX = 10 * difference.x / hypotenuse;
        float velY = 10 * difference.y / hypotenuse;
        if(num > 0)
        {
            shurikens.push_back(new Projectile(getTexture(), velX, velY, getX(), getY()));
            num -= 1;
        }
        setAttack(false);
    }
}

int Player::getMethod()
{
    return method;
}

void Player::setMethod(int i)
{
    method = i;
}

std::vector<Projectile*> *Player::getShurikens()
{
    return &shurikens;
}

bool Player::getAttack()
{
    if(attack)
    {
        auto curr = std::chrono::steady_clock::now();
        std::chrono::duration<double> elapsed = curr - time;
        if(elapsed.count() > .5)
        {
            setAttack(false);
        }
    }
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
    if(b)
    {
        time = std::chrono::steady_clock::now();
    }
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

void Player::animation()
{
    

}

///Finish later today
//void Player::idle(bool b){
//};

/*
Method is responsible for animating the player sprite. It uses the textures passed in the constructor.
It should have different animation for when character is at a stand-still compared to when it is moving.
*/
void Player::iTexture(){
    if(!this->textureSheet.loadFromFile("resources/Images/Player/playerMegaSheet.png")){
        std::cout<<"texture did not load"<<"\n";
    }
}

void Player::iVariables()
{   
    if(left = true){
         this->aAnimationState = CROUCH_RIGHT;
    }else{
        this->aAnimationState = CROUCH_RIGHT;
    }
}
void Player::iSprite()
{
    if(aAnimationState = ATTACKING_LEFT){
        this->sprite.setTexture(this->textureSheet);
        this->currentFrame = sf::IntRect(0,0,57,38);
        this->sprite.setTextureRect(this->currentFrame);
        this->sprite.setScale(2.0f, 2.0f);
    }
    else if(aAnimationState = ATTACKING_RIGHT){
        this->sprite.setTexture(this->textureSheet);
        this->currentFrame = sf::IntRect(228,0,57,38);
        this->sprite.setTextureRect(this->currentFrame);
        this->sprite.setScale(2.0f, 2.0f);
    }
    else if(aAnimationState = CROUCH_LEFT){
        this->sprite.setTexture(this->textureSheet);
        this->currentFrame = sf::IntRect(456,0,28,30);
        this->sprite.setTextureRect(this->currentFrame);
        this->sprite.setScale(2.0f, 2.0f);
    }
    else if(aAnimationState = CROUCH_RIGHT){
        this->sprite.setTexture(this->textureSheet);
        this->currentFrame = sf::IntRect(624,0,28,30);
        this->sprite.setTextureRect(this->currentFrame);
        this->sprite.setScale(2.0f, 2.0f);
    }
    else if(aAnimationState = IDLE_RIGHT){
        this->sprite.setTexture(this->textureSheet);
        this->currentFrame = sf::IntRect(792,0,23,30);
        this->sprite.setTextureRect(this->currentFrame);
        this->sprite.setScale(2.0f, 2.0f);
    }
    else if(aAnimationState = DYING_RIGHT){
        this->sprite.setTexture(this->textureSheet);
        this->currentFrame = sf::IntRect(905,0,34,37);
        this->sprite.setTextureRect(this->currentFrame);
        this->sprite.setScale(2.0f, 2.0f);
    }
    else if(aAnimationState = DYING_LEFT){
        this->sprite.setTexture(this->textureSheet);
        this->currentFrame = sf::IntRect(1112,0,34,37);
        this->sprite.setTextureRect(this->currentFrame);
        this->sprite.setScale(2.0f, 2.0f);
    }
}

void Player::iAnimations(){
    this->aAnimationTimer.restart();
}

void Player::updateMovement()
{
    this->aAnimationState = IDLE_lEFT;
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A)){
        this->sprite.move(-2.f, 0.f);
        this->aAnimationState = MOVING_LEFT;
        left = true;
    }else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D)){
        this->sprite.move(2.f,0.f);
        this->aAnimationState = MOVING_RIGHT;
        right = true;
    }else if(sf::Mouse::isButtonPressed(sf::Mouse::Button::Left)){
        this->sprite.move(0.f,0.f);
        this->aAnimationState = ATTACKING_LEFT;
    }else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S)){
        this->sprite.move(0.f,0.f);
        this->aAnimationState = CROUCH_LEFT;
    }
}

void Player::update()
{
    this->updateMovement();
    this->updateAnimations();
}

void Player::render(sf::RenderTarget& target){
    target.draw(this->sprite);
}

void Player::updateAnimations()
{
    if(this->aAnimationState == ATTACKING_LEFT)
    {
        if(this->aAnimationTimer.getElapsedTime().asSeconds()>= 0.1f)
        { 
            this->currentFrame.top = 0.f;
            this->currentFrame.left += 57.0f;;
            if(this->currentFrame.left >= 171.0f)
               this->currentFrame.left = 0;

            this->aAnimationTimer.restart();
            this->sprite.setTextureRect(this->currentFrame);
        }
    }
//     else if(this->aAnimationState == ATTACKING_RIGHT)
//     {
//         if(this->aAnimationTimer.getElapsedTime().asSeconds() >= 0.2f)
//         {
//             this->currentFrame.top = 0.f;
//             this->currentFrame.left += 91.f;
//             if(this->currentFrame.left >= 1278.f)
//                this->currentFrame.left = 0;
        
//             this->aAnimationTimer.restart();
//             this->sprite.setTextureRect(this->currentFrame);    
//         }
//     }
//     else if(this->aAnimationState == CROUCH_LEFT)
//     {
//         if(this->aAnimationTimer.getElapsedTime().asSeconds() >= 0.2f)
//         {
//             this->currentFrame.top = 0.f;
//             this->currentFrame.left += 28.f;
//             if(this->currentFrame.left >= 596.f)
//                this->currentFrame.left = 0;
        
//             this->aAnimationTimer.restart();
//             this->sprite.setTextureRect(this->currentFrame);    
//         }else
//             this->aAnimationTimer.restart();
//     }
//     else if(this->aAnimationState == CROUCH_RIGHT)
//     {
//         if(this->aAnimationTimer.getElapsedTime().asSeconds() >= 0.2f)
//         {
//             this->currentFrame.top = 0.f;
//             this->currentFrame.left += 35.f;
//             if(this->currentFrame.left >= 140.f)
//                this->currentFrame.left = 0;
        
//             this->aAnimationTimer.restart();
//             this->sprite.setTextureRect(this->currentFrame);    
//         }else
//             this->aAnimationTimer.restart();
//     }
//     else if(this->aAnimationState == IDLE_RIGHT)
//     {
//         if(this->aAnimationTimer.getElapsedTime().asSeconds() >= 0.2f)
//         {
//             this->currentFrame.top = 0.f;
//             this->currentFrame.left += 35.f;
//             if(this->currentFrame.left >= 140.f)
//                this->currentFrame.left = 0;
        
//             this->aAnimationTimer.restart();
//             this->sprite.setTextureRect(this->currentFrame);    
//         }else
//             this->aAnimationTimer.restart();
//     }
//     else if(this->aAnimationState == DYING_RIGHT)
//     {
//         if(this->aAnimationTimer.getElapsedTime().asSeconds() >= 0.2f)
//         {
//             this->currentFrame.top = 0.f;
//             this->currentFrame.left += 35.f;
//             if(this->currentFrame.left >= 140.f)
//                this->currentFrame.left = 0;
        
//             this->aAnimationTimer.restart();
//             this->sprite.setTextureRect(this->currentFrame);    
//         }else
//             this->aAnimationTimer.restart();
//     }
//     else if(this->aAnimationState == DYING_LEFT)
//     {
//         if(this->aAnimationTimer.getElapsedTime().asSeconds() >= 0.2f)
//         {
//             this->currentFrame.top = 0.f;
//             this->currentFrame.left += 35.f;
//             if(this->currentFrame.left >= 140.f)
//                this->currentFrame.left = 0;
        
//             this->aAnimationTimer.restart();
//             this->sprite.setTextureRect(this->currentFrame);    
//        }
//         else
//             this->aAnimationTimer.restart();
//    }
}


///Measurements for NPC 
// if(this->aAnimationState == IDLE)
//     {
//         if(this->aAnimationTimer.getElapsedTime().asSeconds()>= 0.17f)
//         { 
//             this->currentFrame.top = 0.f;
//             this->currentFrame.left += 91.1f;;
//             if(this->currentFrame.left >= 1278.f)
//                this->currentFrame.left = 0;

//             this->aAnimationTimer.restart();
//             this->sprite.setTextureRect(this->currentFrame);
//         }
//     }
