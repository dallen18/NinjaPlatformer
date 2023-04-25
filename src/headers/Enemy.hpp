#include <SFML/Graphics.hpp>
#ifndef _Entity
    #include "Entity.hpp"
#endif

class Enemy : public Entity
{
    private:
        bool contactBottom; 
        bool jumping;
    public:
        Enemy(sf::Texture *texture, float xMax, float yMax, float accel, int xSize, int ySize, bool j);
        ~Enemy();

        std::string getClass();

        void setContactBottom(bool b);
        void setJumping(bool b); 

        bool getContactBottom();
        bool getJumping();

        void move();

        void animation();
};
