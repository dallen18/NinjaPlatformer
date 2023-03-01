#include <SFML/Graphics.hpp>
#ifndef _Entity
    #include "Entity.hpp"
#endif

// class Player
// {
//     private:
//         sf::Texture t;
//         sf::Sprite s;
//         float xVel;
//         float yVel;
//         bool bottom;
//         sf::FloatRect playerBounds;
//         sf::FloatRect nextBounds;
//         float xMax;
//         float yMax;
//         float accel;

//     public:
//         Player(sf::Texture *_t);
//         ~Player();
//         sf::Sprite *getSprite();
//         void setTexture(sf::Texture *_t);
//         void move(std::vector<sf::RectangleShape> *blockList);
//         void collision(std::vector<sf::RectangleShape> *blockList);
// };

class Player : public Entity
{
    private:
        bool contactBottom;

    public:
        //constructor
        Player(std::vector<sf::Texture> *textures, float xMax, float yMax, float accel);

        //getter methods
        bool getContactBottom();

        //setter methods
        void setContactBottom(bool b);

        //other methods
        void animation();
};