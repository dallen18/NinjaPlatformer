#include <SFML/Graphics.hpp>
#include <SFML/Graphics/Rect.hpp>
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

        //state of game
        enum State {
            MAIN_MENU,
            PAUSE_MENU,
            LOST_MENU,
            FIRST_LEVEL,
            SECOND_LEVEL,
            THIRD_LEVEL
        };

        enum State state;
        enum State savedState;

        //array contains booleans and checks whether the setup function for a state has been performed
        bool createdState[sizeof(State)];

        //assets
        std::map<std::string, std::vector<sf::Texture>> textures;
        sf::Font font;

        //lists of interactable objecs
        std::vector<Entity*> entities;
        
        // std::array<Block,1024> blocks;
        std::vector<Block> blocks;

        std::vector<Button> buttons;

        Player *player;

        bool clicked = false;

    public:
        Game();
        ~Game();

        //game set-up functions
        void initWindow();
        void loadTextures();

        //game loop
        void run();

        //main menu set-up and logic functions
        void setMainMenu();
        void mainMenu();

        //first level
        void setFirstLevel();
        void firstLevel();

        //pause menu
        void setPauseMenu();
        void pauseMenu();

        //collision and movement
        void playerCollision();
        std::string mouseCollision();
        void handleInput(sf::Event *event);
        bool checkCollision(sf::Rect<float> a, sf::Rect<float> b);
        void drawUI();
};
