#include "headers/NPC.hpp"
#include <iostream>

NPC::NPC(sf::Texture *texture, float xMax, float yMax, float accel, int xSize, int ySize, std::string m)
{
    setTexture(texture);
    getSprite()->setTexture(*texture); //sets initial texture of sprite as the first texture in list
    setXVel(0.0f);
    setYVel(0.0f);
    setXMax(xMax);
    setYMax(yMax);
    setAccel(accel);
    setXSize(50);
    setYSize(50);

    int line = 10;

    int a = 0, b = 0;
    char c = m[0];
    
    std::string word;
    std::string sentence;

    // text function to not awkwardly cut off words after lineLength characters
    int lineLength = 20;
    for (int i=0; i<m.size(); i++) {
        if (word.size() >= lineLength || m[i] == ' ') {
            sentence += word + ' ';
            word.clear();
            i++;
        }
        if (sentence.length() >= 20) {
            message += sentence + '\n';
            sentence.clear();
        }
        word += m[i];
    }
    if (!word.empty()) {
        sentence += word;
    }
    message += sentence;
    std::cout << message << std::endl;
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

void NPC::animation()
{

}
