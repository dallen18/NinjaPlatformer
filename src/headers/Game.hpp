#include <SFML/Graphics.hpp>
#include <iostream>
#include <stdarg.h>
#include <vector>
#include <map>
#include <string>
#include "Player.hpp"
#include "Enemy.hpp"
#include "Block.hpp"
#include "Menu.hpp"

class Game
{
    private:
        sf::RenderWindow window;
        enum State {
            MAIN_MENU,
            PAUSE_MENU,
            FIRST_LEVEL,
            SECOND_LEVEL,
            THIRD_LEVEL
        };
        enum State state;
        std::map<std::string, std::vector<sf::Texture>> textures;
        sf::Font font;

    public:
        Game();
        ~Game();

        //game set-up functions
        void initWindow();
        void loadTextures();

        //game loop
        void run();

        //main menu set-up and logic functions
        void setMainMenu(std::vector<Button> *buttons);
        void mainMenu(std::vector<Button> *buttons);

        //first level
        void setFirstLevel(std::vector<Block> *blocks, std::vector<Entity> *entities, Player *player);
        void firstLevel(std::vector<Block> *blocks, std::vector<Entity> *entities, Player *player);

        //pause menu
        void setPauseMenu(std::vector<Button> *buttons);
        void pauseMenu(std::vector<Button> *buttons, std::vector<Block> *blocks, std::vector<Entity> *entities, Player *player);

        //collision and movement
        void movePlayer(std::vector<Block> *blocks, std::vector<Entity> *entities, Player *player);
        void playerCollision(std::vector<Entity> *entities, std::vector<Block> *blocks, Player *player, sf::FloatRect *n);
        std::string mouseCollision(std::vector<Button> *buttons);
};