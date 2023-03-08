#include <SFML/Graphics.hpp>
#ifndef _Entity
    #include "Entity.hpp"
#endif

class Player : public Entity
{
    private:
        bool contactBottom;
        
        //input
        bool jumping = false;

    public:
        //constructor
        Player(std::vector<sf::Texture> *textures, float xMax, float yMax, float accel);

        //getter methods
        bool getContactBottom();
        bool getJumping();

        //setter methods
        void setContactBottom(bool b);
        void setJumping(bool b); //sets spacePressed to true if space bar is pressed

        //other methods
        void animation();
};