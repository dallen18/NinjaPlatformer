#include <SFML/Graphics.hpp>
#include <SFML/Graphics/Rect.hpp>

class Block
{
    private:
        sf::Sprite sprite;
        sf::Texture *texture;
        int x;
        int y;

    public:
        //constructor and destructor
        Block(sf::Texture *t, int _x, int _y, sf::IntRect rect, sf::Vector2f s);
        ~Block();

        //getter methods
        sf::Sprite *getSprite();
        int getX();
        int getY();
        //setter methods
};
