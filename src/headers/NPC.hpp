#include <SFML/Graphics.hpp>

#ifndef _Entity
    #include "Entity.hpp"
#endif


#include <string>
#include <vector>

class NPC : public Entity
{
    private:
        std::string message;

    public:
        NPC(sf::Texture *texture, float xMax, float yMax, float accel, int xSize, int ySize, std::string m);
        ~NPC();
        std::string getString();
        std::string getClass();
        void move();
        void animation();
};




