#include <SFML/Graphics.hpp>
#include <SFML/Graphics/Texture.hpp>
//#include <Animation.hpp>

#define _Entity

class Entity
{
    private:
        
        float xVel;
        float yVel;
        float xMax;
        float yMax;
        float accel;
        int xSize;
        int ySize;
        float x;
        float y;

     //array contains booleans and checks whether the setup function for a state has been performed
        //bool createdState[sizeof(entityState)];

        
    public:
        /// moved from private
        sf::Sprite sprite;
        sf::Texture textureSheet;
        //////////

        //getter methods
        sf::Sprite *getSprite();
        sf::Texture *texture;
        float getXVel();
        float getYVel();
        float getXMax();
        float getYMax();
        float getAccel();
        int getXSize();
        int getYSize();
        bool getAlive();
        sf::Texture *getTexture();
        //std::vector<sf::Texture> *getTextures();
        float getX();
        float getY();

        //entityState Entity::setState(entityState state);

        //setter methods
        void setXVel(float x);
        void setYVel(float y);
        void setXMax(float x);
        void setYMax(float y);
        void setAccel(float a);
        void setXSize(int s);
        void setYSize(int s);
        void setTexture(sf::Texture *t);
        void setX(float v);
        void setY(float v);
        void setAlive(bool b);

        virtual std::string getClass();

        virtual void move();

        //Set states in public, have setters and getters
        //State will hold the animation features and will update in play level
        //in my animation update I will 

        //////////////

        //methods that need to be implemented for every class that is derived from Entity
        void update();
        void render(sf::RenderTarget& target);

        virtual void animation(sf::Texture *t)
        {
            //animation.getUpdate();
        }; //handles animation
};
