#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Graphics/Rect.hpp>
#include <SFML/System/Clock.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
#include <stdarg.h>
#include <vector>
#include <map>
#include <string>
#include <chrono>
#include <thread>
#include "Player.hpp"
#include "Enemy.hpp"
#include "Block.hpp"
#include "Menu.hpp"
#include "NPC.hpp"
#include "Hud.hpp"
#include "InputManager.hpp"
#include "tinyxml2.h"
#include "Sound.hpp"

const int SCREEN_FPS = 60;
const int SCREEN_TICKS_PER_FRAME = 1000 / SCREEN_FPS;

class Game
{
    private:
        sf::RenderWindow window;

        //state of game
        enum State 
        {
            MAIN_MENU,
            PAUSE_MENU,
            PLAYING
        };

        enum State state;
        enum State savedState;

        //array contains booleans and checks whether the setup function for a state has been performed
        bool createdState[sizeof(State)];

        //assets
        std::unordered_map<std::string, sf::Texture> textures;
        std::unordered_map<std::string, sf::SoundBuffer> sounds;
        ActiveSounds activeSounds;
        sf::Font font;

        //lists of interactable objecs
        std::vector<Entity*> entities;
        
        std::vector<Block> blocks;

        std::vector<Button> buttons;

        Player *player;

        InputManager *input;

    public:
        Game();
        ~Game();

        //game set-up functions
        void initWindow();
        void loadTextures();
        void loadSounds();

        //game loop
        void run();

        //main menu set-up and logic functions
        void setMainMenu();
        void mainMenu();

        //first level
        void setLevel(std::string filename);
        void playLevel();

        //pause menu
        void setPauseMenu();
        void pauseMenu();

        //collision and movement
        std::string mouseCollision();
        bool checkCollision(sf::Rect<float> a, sf::Rect<float> b);
};
