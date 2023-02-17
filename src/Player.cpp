#include "headers/Player.hpp"

Player::Player(sf::Texture *_t)
{
    t = *_t;
    s.setTexture(t);
    v = 5.0f;
}

Player::~Player()
{

}

sf::Sprite *Player::getSprite()
{
    return &s;
}

float Player::getVelocity()
{
    return v;
}

void Player::setTexture(sf::Texture *_t)
{
    t = *_t;
    s.setTexture(t);
}

void Player::setVelocity(float _v)
{
    v = _v;
}