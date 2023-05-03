#include "headers/NPC.hpp"
#include <iostream>

NPC::NPC()
{   this->iVariables();   
    this->iTexture();
    this->iSprite();
    this->iAnimations(); 
}

NPC::NPC(sf::Texture *texture, float xMax, float yMax, float accel, int xSize, int ySize, std::string m)
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

    int line = 10;

    int a = 0, b = 0;
    char c = m[0];
    
    std::string word;
    std::string sentence;

    //int count=3;

    /*for (int i = 0; i < message.size(); i += 10) {
        word = message.substr(i, 10);
        sentence += word + '\n';
    }

    std::cerr << sentence << std::endl;*/
    //std::cout << m << std::endl;

    int lineLength = 15;
    for (int i=0; i<m.size(); i++) {
        if (word.size() >= lineLength || m[i] == ' ') {
            sentence += word + ' ';
            word.clear();
            i++;
        }
        if (sentence.length() >= 15) {
            message += sentence + '\n';
            sentence.clear();
        }
        word += m[i];
    }
    if (!word.empty()) {
        sentence += word;
    }
    std::cout << message << std::endl;
    
    //std::cout << sentence << std::endl;


    //std::cout.flush();

    //message.push_back('\n');

    /*for(int i=0; i < m.size(); i++)
    {
        
        if (m[i] == ' ') {
            //count++;
            /*for (int j=i; j < m.size(); j++) {
                count++;
                if (m[j] == ' ') {
                    
                    break;
                }
            }
            // substring is (where to start, how long)
            /*if (i >= 40) {
             count = 0;
            }
            word = message.substr(i, count);
           // word = message.substr(1, std::min(count, static_cast<int>(message.length()) - 1));
            sentence += word + " ";
            word.clear();
           
            //count=0;
            //now you gotta go past the word
            //i += 3;
            if (sentence.size() > 10) {
                message += sentence;
                message.push_back('\n');
                sentence.clear();
            }
        }
       
    }*/
}
NPC::~NPC()
{

}

std::string NPC::getString()
{
    return message;
}

std::string NPC::getClass()
{
    return "NPC";
}

void NPC::move()
{

}

//loads merchant texture
void NPC::iTexture(){
    if(!this->merchantTexture.loadFromFile("resources/Images/Player/Merchant.png"))
    {
        std::cout<<"texture did not load"<<"\n";
    }
}

void NPC::iVariables()
{   
    this->nAnimationState = MERCH_IDLE;
}

void NPC::update()
{
    this->updateMovement();
    this->updateAnimations();
}

void NPC::render(sf::RenderTarget& target){
    target.draw(this->sprite);
}

/*
Sets texture to the sprite and start postion, height and width
*/
void NPC::iSprite()
{
    this->sprite.setTexture(this->merchantTexture);
    this->currentFrame = sf::IntRect(0,0,91.1,70);
    this->sprite.setTextureRect(this->currentFrame);
    this->sprite.setScale(2.0f, 2.0f);
}

void NPC::iAnimations(){
    this->nAnimationTimer.restart();
}

void NPC::updateMovement(){
    this->nAnimationState = MERCH_IDLE;
}

/*
Method that sets measurements for NPC, moves across the texture with a 91.1f windows, 
every .17 seconds it iterates through to the next frame
*/
void NPC::updateAnimations()
{
if(this->nAnimationState == MERCH_IDLE)
    {
        if(this->nAnimationTimer.getElapsedTime().asSeconds()>= 0.17f)
        { 
            this->currentFrame.top = 0.f;
            this->currentFrame.left += 91.1f;
            if(this->currentFrame.left >= 1278.f)
               this->currentFrame.left = 0;

            this->nAnimationTimer.restart();
            this->sprite.setTextureRect(this->currentFrame);
        }
    }
}


