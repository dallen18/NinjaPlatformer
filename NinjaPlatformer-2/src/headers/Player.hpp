#include <SFML/Graphics.hpp>
#ifndef _Entity
#include "Entity.hpp"
#endif

class Player : public Entity {
 private:
  bool contactBottom;

  int health;

  bool jump;
  bool right;
  bool left;

 public:
  // constructor
  Player(std::vector<sf::Texture> *textures, float xMax, float yMax,
         float accel, int xSize, int ySize, float xScale = 1.f,
         float yScale = 1.f);

  // getter methods
  bool getContactBottom();
  bool getJumping();
  bool getRight();
  bool getLeft();
  int getHealth();

  // setter methods
  void setContactBottom(bool b);
  void setJumping(bool b);  // sets spacePressed to true if space bar is pressed
  void setRight(bool b);
  void setLeft(bool b);
  void setHealth(int h);
  void decreaseHealth();

  void move();

  // other methods
  void animation();
};
