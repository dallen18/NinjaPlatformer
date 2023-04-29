#include "headers/Sound.hpp"
#include <SFML/Audio/Sound.hpp>
#include <SFML/Audio/SoundBuffer.hpp>
#include <memory>

ActiveSounds::ActiveSounds()
{

}

ActiveSounds::~ActiveSounds()
{

}

void ActiveSounds::addSound(sf::SoundBuffer *buffer)
{
    sounds.push_back(std::make_unique<sf::Sound>());
    sounds.back()->setBuffer(*buffer);
    sounds.back()->play();
}

void ActiveSounds::checkSounds()
{
    for(int i = 0; i < sounds.size(); i++)
    {
        if(sounds.at(i)->getStatus() == sf::Sound::Stopped)
        {
            sounds.erase(sounds.begin() + i);
        }
    }
}
