#include "headers/Sound.hpp"
#include <SFML/Audio/Sound.hpp>
#include <SFML/Audio/SoundBuffer.hpp>

ActiveSounds::ActiveSounds()
{

}

ActiveSounds::~ActiveSounds()
{

}

void ActiveSounds::addSound(sf::SoundBuffer *buffer)
{
    sf::Sound *sound = new sf::Sound;
    sounds.push_back(sound);
    sound->setBuffer(*buffer);
    sound->play();
}

void ActiveSounds::checkSounds()
{
    for(int i = 0; i < sounds.size(); i++)
    {
        if(sounds.at(i)->getStatus() == sf::Sound::Stopped)
        {
            delete sounds.at(i);
            sounds.erase(sounds.begin() + i);
        }
    }
}
