#include <iostream>
#include <SFML/Graphics.hpp>
#include "Player.hpp"

class Game
{
    private:

    public:
        sf::RenderWindow window;
        Game();
        ~Game();
        void run();
        void initWindow();
        void loadTextures();
        void draw(int n, ...);
};