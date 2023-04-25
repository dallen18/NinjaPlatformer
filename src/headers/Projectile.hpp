#include <SFML/Graphics.hpp>
#ifndef _Entity 
    #include "Entity.hpp"
#endif // !

class Projectile : public Entity
{
    private:
        
    public:
        Projectile(sf::Texture *t, float xvel, float yvel, float x, float y);
        ~Projectile();
        void move();

};
