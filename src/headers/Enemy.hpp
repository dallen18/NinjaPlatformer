#include <SFML/Graphics.hpp>
#ifndef _Entity
    #include "Entity.hpp"
#endif

class Enemy : public Entity
{
    private:

    public:
        Enemy(std::vector<sf::Texture> *textures, float xMax, float yMax, float accel);
        void animation();
};