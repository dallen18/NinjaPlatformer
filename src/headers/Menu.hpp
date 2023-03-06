#include <SFML/Graphics.hpp>
#include "Button.hpp"
#include <string>
#include <iostream>
#include <vector>

class Menu
{
    private:
        sf::Text title;
        std::vector<Button> *buttons;
        float rectHeight = 0.0f;

    public:
        Menu(std::string _title, std::vector<Button> *_buttons, sf::Font *_font);
        ~Menu();

        void draw(sf::RenderWindow *w);
};