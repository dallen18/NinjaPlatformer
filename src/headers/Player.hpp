#include <SFML/Graphics.hpp>
#include <vector>
#include "Projectile.hpp"
#ifndef _Entity
    #include "Entity.hpp"
#endif

#define _Player

class Player : public Entity
{
    private:
        bool contactBottom; 
        int health;
        bool attack;
        bool jump;
        bool right;
        bool left;
        int num = 20;
        std::vector<Projectile*> shurikens;

    public:
        //constructor
        Player(sf::Texture *texture, float xMax, float yMax, float accel, int xSize, int ySize, int x, int y);
        ~Player();
        //getter methods
        bool getContactBottom();
        bool getJumping();
        bool getRight();
        bool getLeft();
        int getHealth();
        bool getAttack();
        std::vector<Projectile*> *getShurikens();

        //setter methods
        void setContactBottom(bool b);
        void setJumping(bool b); //sets spacePressed to true if space bar is pressed
        void setRight(bool b);
        void setLeft(bool b);
        void setHealth(int h);
        void decreaseHealth();
        void setAttack(bool b);

        void move();
        void createAttack();

        //other methods
        void animation();
};
