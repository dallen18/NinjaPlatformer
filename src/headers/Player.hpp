#include <SFML/Graphics.hpp>

class Player
{
    private:
        sf::Texture t;
        sf::Sprite s;
        float v;

    public:
        Player(sf::Texture *_t);
        ~Player();
        sf::Sprite *getSprite();
        float getVelocity();
        void setTexture(sf::Texture *_t);
        void setVelocity(float v);
};