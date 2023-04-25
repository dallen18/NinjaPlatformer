#include "headers/InputManager.hpp"
#include "headers/tinyxml2.h"
#include <SFML/Window/Keyboard.hpp>
#include <unordered_map>

InputManager* InputManager::instancePtr = NULL;

InputManager::InputManager()
{ 
    tinyxml2::XMLDocument doc;
    std::cout << "hello";
    doc.LoadFile("resources/controls.xml");
    
    if(!doc.Error())
    {   
        auto node = doc.RootElement()->FirstChild();
        
        while(node != NULL)
        {
            auto key = node->ToElement()->Attribute("key");
            auto value = node->ToElement()->Attribute("action");
            controlMap[key] = value;
            node = node->NextSibling();
        }

        for(auto pair : controlMap)
        {
            pressed[pair.second] = false;
        }
    }
    else
    {
        std::cout << "controls document hasn't been found!";
    }
}

InputManager *InputManager::getInstance()
{
    if(instancePtr == NULL)
    {
        instancePtr = new InputManager();
    }
    return instancePtr;
}

void InputManager::checkPlayerInput()
{
    for(auto pair : controlMap)
    {
        sf::Keyboard::Key k;
        if(pair.first == "A")
        {
            k = sf::Keyboard::A;
        }
        else if(pair.first == "D")
        {
            k = sf::Keyboard::D;
        }
        else if(pair.first == "Space")
        {
            k = sf::Keyboard::Space;
        }
        else
        {
            k = sf::Keyboard::Unknown;
        }

        if(sf::Keyboard::isKeyPressed(k))
        {
            if(pair.second == "Jump")
            {
                if(!keys[k])
                {
                    pressed[pair.second] = true;       
                    keys[k] = true;
                }
                else
                {
                    pressed[pair.second] = false;
                }
            }
            else
            {
                pressed[pair.second] = true;
            }
        }
        else
        {
            if(pair.second == "Jump")
            {
                keys[k] = false;
            }
            pressed[pair.second] = false;
        }
    } 
}

bool InputManager::checkOtherInput(int code, int type)
{
    bool c = false;

    switch(type)
    {
        case 0:
            if(sf::Keyboard::isKeyPressed((sf::Keyboard::Key) code))
            {
                if(!keys[code])
                {
                    keys[code] = true;
                    c = true;
                }
            }
            else
            {
                keys[code] = false;
            }
            break;
        case 1:
            if(sf::Mouse::isButtonPressed((sf::Mouse::Button) code))
            {
                if(!buttons[code])
                {
                    buttons[code] = true;
                    c = true;
                }
            }
            else
            {
                buttons[code] = false;
            }
            break;
    }

    return c;
}

std::unordered_map<std::string, bool> *InputManager::getPressed()
{
    return &pressed;
}
