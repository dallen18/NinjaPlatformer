#include <SFML/Graphics.hpp>
#ifndef _Entity
    #include "Entity.hpp"
#endif

enum ENEMY_ANIMATION_STATES{
    ENEMY_MOVING_LEFT = 0,
    ENEMY_MOVING_RIGHT,
    ENEMY_DYING
};

class Enemy : public Entity
{
    private:
        bool contactBottom; 
        bool jumping;
        bool alive;
        float totalTime;
        float rotateTime;
        sf::IntRect currentFrame;
        sf::Clock enAnimationTimer;
        short animationState;
        sf::Texture dieTexture;
        sf::Sprite sprite;


    public:
        Enemy(sf::Texture *texture, float xMax, float yMax, float accel, int xSize, int ySize, bool j);
        Enemy();
        ~Enemy();

        std::string getClass();

        void setContactBottom(bool b);
        void setJumping(bool b); 
        void setAlive(bool b);
        bool getContactBottom();
        bool getJumping();
        bool getAlive();

        void move();


        sf::IntRect rect;
        void update();
        void render(sf::RenderTarget& target);
        void animation(sf::Texture* texture, float _rotateTime,float dt, bool alive);
        void UpdateAnimation();
        void animationReset();
        void variables();
        void dyingTexture();
        void Texture();
        void Sprite();
        void animations();
};
