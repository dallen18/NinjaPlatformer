#include "headers/Block.hpp"

Block::Block(std::vector<sf::Texture> *t)
{
    textures = t;
    sprite.setTexture(textures->front()); //sets initial texture of sprite as the first texture in list
}

Block::~Block()
{

}

sf::Sprite *Block::getSprite()
{
    return &sprite;
}