#include <SFML/Graphics.hpp>

class Player
{
    private:
        sf::Texture t;
        sf::Sprite s;
        float xVel;
        float yVel;
        bool bottom;
        sf::FloatRect playerBounds;
        sf::FloatRect nextBounds;
        float xMax;
        float yMax;
        float accel;

    public:
        Player(sf::Texture *_t);
        ~Player();
        sf::Sprite *getSprite();
        float getXVelocity();
        float getYVelocity();
        void setTexture(sf::Texture *_t);
        void move(std::vector<sf::RectangleShape> *blockList);
        void collision(std::vector<sf::RectangleShape> *blockList);
        void setXVelocity(float v);
        void setYVelocity(float v);
};