#include "headers/Entity.hpp"

sf::Sprite *Entity::getSprite() { return &sprite; }

float Entity::getXVel() { return xVel; }

float Entity::getYVel() { return yVel; }

float Entity::getXMax() { return xMax; }

float Entity::getYMax() { return yMax; }

float Entity::getAccel() { return accel; }

int Entity::getXSize() { return xSize; }

int Entity::getYSize() { return ySize; }

std::string Entity::getClass() { return "Entity"; }

std::vector<sf::Texture> *Entity::getTextures() { return textures; };

void Entity::setXVel(float x) { xVel = x; }

void Entity::setYVel(float y) { yVel = y; }

void Entity::setXMax(float x) { xMax = x; }

void Entity::setYMax(float y) { yMax = y; }

void Entity::setAccel(float a) { accel = a; }

void Entity::setXSize(int s) { xSize = s; }

void Entity::setYSize(int s) { ySize = s; }

void Entity::setTextures(std::vector<sf::Texture> *t) { textures = t; }

void Entity::animation() {}

void Entity::move() {}
