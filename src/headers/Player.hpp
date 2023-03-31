#include <SFML/Graphics.hpp>
#ifndef _Entity
    #include "Entity.hpp"
#endif

class Player : public Entity
{
    private:
        bool contactBottom;
        
        //input
        bool jumping; 

        // int health;

    public:
        int health;
        //constructor
        Player(std::vector<sf::Texture> *textures, float xMax, float yMax, float accel, int xSize, int ySize);

        //getter methods
        bool getContactBottom();
        bool getJumping();
        int getHealth();

        //setter methods
        void setContactBottom(bool b);
        void setJumping(bool b); //sets spacePressed to true if space bar is pressed
        void setHealth(int h);
        void decreaseHealth();

        void move();

        //other methods
        void animation();
};