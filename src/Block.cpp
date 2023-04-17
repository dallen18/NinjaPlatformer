#include "headers/Block.hpp"
#include <SFML/Graphics/Rect.hpp>
#include <SFML/System/Vector2.hpp>

Block::Block(sf::Texture *t, int _x, int _y,sf::IntRect rect, sf::Vector2f s)
{
    x = _x;
    y = _y;
    texture = t;
    sprite.setTexture(*texture); //sets initial texture of sprite as the first texture in list
    sprite.setTextureRect(rect);
    sprite.setScale(s);
    sprite.setPosition(x,y);
    if(s.x == -1)
    {
        sprite.move(rect.width,0);
    }

    if(s.y == -1)
    {
        sprite.move(0,rect.height);
    }
}

Block::~Block()
{

}

int Block::getX()
{
    return x;
}

int Block::getY()
{
    return y;
}

sf::Sprite *Block::getSprite()
{
    return &sprite;
}
