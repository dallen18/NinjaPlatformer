#include "headers/NPC.hpp"

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
    std::string word;
    std::string sentence;

    for(int i = 0; i < m.size(); i++)
    {

    }

    for(int i = 1; i < m.size() + 1; i++)
    {
        message.push_back(m.at(i - 1));
        if(i % 20 == 0)
        {
            message.push_back('\n');
        }
    }
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
