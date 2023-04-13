#include <SFML/Graphics.hpp>
#include <string>

class Game;

class Button
{
    private:
        sf::RectangleShape rect;
        sf::Text text;
        std::string id;

    public:
        Button(std::string _id, std::string _text, sf::Font *_font);
        ~Button();

        //getter methods
        sf::RectangleShape *getRect();
        std::string getID();

        //setter methods
        void setPosition(float x, float y);

        //other methods
        void highlightButton(sf::RenderWindow *w);
        void draw(sf::RenderWindow *w);

};