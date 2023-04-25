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
