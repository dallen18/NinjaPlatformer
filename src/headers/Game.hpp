#include <SFML/Graphics.hpp>
#include <iostream>
#include <stdarg.h>
#include <vector>
#include <map>
#include <string>
#include "Player.hpp"
#include "Enemy.hpp"
#include "Block.hpp"
#include "Button.hpp"

class Game
{
    private:
        sf::RenderWindow window;
        enum State {
            MAIN_MENU,
            FIRST_LEVEL,
            SECOND_LEVEL,
            THIRD_LEVEL
        };
        enum State state;
        std::map<std::string, std::vector<sf::Texture>> textures;

    public:
        Game();
        ~Game();
        void run();
        void setMainMenu(std::vector<Button> *buttons);
        void mainMenu(std::vector<Button> *buttons);
        void setFirstLevel(std::vector<Button> *buttons, std::vector<Block> *blocks, std::vector<Entity> *entities, Player *player);
        void firstLevel(std::vector<Button> *buttons, std::vector<Block> *blocks, std::vector<Entity> *entities, Player *player);
        void initWindow();
        void loadTextures();
        void movePlayer(std::vector<Block> *blocks, std::vector<Entity> *entities, Player *player);
        void playerCollision(std::vector<Entity> *entities, std::vector<Block> *blocks, Player *player, sf::FloatRect *n);
        std::string mouseCollision(std::vector<Button> *buttons);
        void draw(int n, ...);
};