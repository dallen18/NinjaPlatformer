#include <SFML/Graphics.hpp>

#ifndef _Entity
    #include "Entity.hpp"
#endif


#include <string>
#include <vector>

enum MERCHANT_ANIMATION_STATE{
    MERCH_IDLE = 0
};


class NPC : public Entity
{
    private:
        std::string message;
        sf::Clock nAnimationTimer;
        short nAnimationState;

    public:
        NPC();
        NPC(sf::Texture *texture, float xMax, float yMax, float accel, int xSize, int ySize, std::string m);
        ~NPC();
        std::string getString();
        std::string getClass();
        void move();
        void animation();

        void updateMovement();
        void updateAnimations();
        void update();
        void render(sf::RenderTarget& target);
        sf::IntRect currentFrame;
        sf::Texture merchantTexture;
        sf::Sprite sprite;
        void iVariables();
        void iSprite();
        void iTexture();
        void iAnimations();
};




