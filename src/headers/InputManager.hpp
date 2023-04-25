#include <SFML/Graphics.hpp>
#include <SFML/Window/Event.hpp>
#include <SFML/Window/Keyboard.hpp>
#include <SFML/Window/Mouse.hpp>
#include <map>
#include <sstream>
#include <unordered_map>
#include <string>
#include <iostream>
#include "tinyxml2.h"

class InputManager
{
    private:
        std::unordered_map<std::string, std::string> controlMap;
        std::unordered_map<std::string, bool> pressed;
        std::unordered_map<int, bool> keys;
        std::unordered_map<int, bool> buttons;
        InputManager();
        static InputManager* instancePtr;

    public:
        InputManager(const InputManager& obj) = delete;
        static InputManager *getInstance();
        void checkPlayerInput();
        bool checkOtherInput(int code, int type);
        std::unordered_map<std::string, bool> *getPressed();
};
