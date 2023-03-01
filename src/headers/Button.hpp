#include <SFML/Graphics.hpp>
#include <string>
#include <functional>

class Button
{
    private:
        sf::RectangleShape rect;
        sf::Text text;
        std::string id;

    public:
        Button(std::string _id, std::string _text);//, std::function<void()> _action);
        ~Button();

        //getter methods
        sf::RectangleShape *getRect();
        std::string getID();

        //setter methods

        //other methods
        void action();
        void highlightButton();

};