#include <SFML/Graphics.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <chrono>
#include <vector>
#include "Projectile.hpp"
#ifndef _Entity
    #include "Entity.hpp"
#endif

#define _Player

enum PLAYER_ANIMATION_STATES{
    IDLE_lEFT,
    IDLE_RIGHT,
    MOVING_LEFT,
    MOVING_RIGHT,
    JUMPING,
    ATTACKING_LEFT,
    ATTACKING_RIGHT,
    CROUCH_LEFT,
    CROUCH_RIGHT,
    CROUCHING_LEFT,
    HURT_LEFT,
    HURT_RIGHT,
    DYING_LEFT,
    DYING_RIGHT,
    DASH_LEFT,
    DASH_RIGHT
};

class Player : public Entity
{
    private:
        bool contactBottom; 
        int health;
        int method;
        bool attack;
        bool jump;
        bool right;
        bool left;
        int num = 20;
        std::vector<Projectile*> shurikens;
        sf::RectangleShape rect;
        std::chrono::time_point<std::chrono::steady_clock> time;

        /////////////////////////
        sf::Clock aAnimationTimer;
        short aAnimationState;

    public:
        //constructorPlayer(sf::Texture *texture, float xMax, float yMax, float accel, int xSize, int ySize, int x, int y);
        Player();
        Player(sf::Texture *texture, float xMax, float yMax, float accel, int xSize, int ySize, int x, int y);
        ~Player();

        
        //getter methods
        bool getContactBottom();
        bool getJumping();
        bool getRight();
        bool getLeft();
        int getHealth();
        bool getAttack();
        int getMethod();
        std::vector<Projectile*> *getShurikens();
        
        //setter methods
        void setContactBottom(bool b);
        void setJumping(bool b); //sets spacePressed to true if space bar is pressed
        void setRight(bool b);
        void setLeft(bool b);
        void setHealth(int h);
        void decreaseHealth();
        void setAttack(bool b);
        void setMethod(int i);
        void setAlive(bool b);

        void move();
        void createAttack(const sf::View &view);

        //other methods
        void animation();

        ////////functions/////////////
        ////////////////deontae
        bool getAlive();
        void updateMovement();
        void updateAnimations();
        void update();
        void render(sf::RenderTarget& target);
        sf::IntRect currentFrame;
        sf::Texture textureSheet;
        sf::Sprite sprite;
        void iVariables();
        void iSprite();
        void iTexture();
        void iAnimations();
        ///////////////////////
};