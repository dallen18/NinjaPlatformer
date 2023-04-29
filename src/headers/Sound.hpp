#include <SFML/Audio/Sound.hpp>
#include <SFML/Audio/SoundBuffer.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <vector>

class ActiveSounds
{
    private:
        std::vector<sf::Sound *> sounds;

    public:
        ActiveSounds();
        ~ActiveSounds();

        void addSound(sf::SoundBuffer *buffer);
        void checkSounds();
};
