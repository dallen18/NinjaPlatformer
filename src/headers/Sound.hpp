#include <SFML/Audio/Sound.hpp>
#include <SFML/Audio/SoundBuffer.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <vector>
#include <memory>

class ActiveSounds
{
    private:
        std::vector<std::unique_ptr<sf::Sound>> sounds;

    public:
        ActiveSounds();
        ~ActiveSounds();

        void addSound(sf::SoundBuffer *buffer);
        void checkSounds();
};
