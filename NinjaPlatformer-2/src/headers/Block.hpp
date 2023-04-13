#include <SFML/Graphics.hpp>

class Block
{
    private:
        sf::Sprite sprite;
        std::vector<sf::Texture> *textures;

    public:
        //constructor and destructor
        Block(std::vector<sf::Texture> *t);
        ~Block();

        //getter methods
        sf::Sprite *getSprite();

        //setter methods
};