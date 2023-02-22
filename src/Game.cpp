#include "headers/Game.hpp"
#include <stdarg.h>
#include <iostream>
#include <vector>

Game::Game()
{
    //initializes window
    initWindow();

    //loads textures
    loadTextures();

    //runs program
    run();
}

Game::~Game()
{

}

void Game::initWindow()
{
    //sets default size for window, creates title, and sets style to fullscreen
    window.create(sf::VideoMode(640, 360), "Ninja Platofmrer",sf::Style::Fullscreen);

    //syncs frames with refresh rate of monitor
    window.setVerticalSyncEnabled(true);
}

void Game::loadTextures()
{

}

void Game::run()
{
    sf::Texture playerTexture;

    //takes texture from resources folder
    if(!playerTexture.loadFromFile("resources/Adam.jpg"))
    {
        std::cout << "failed to load image.";
    }

    //instantiates player with given texture
    Player player(&playerTexture);

    //make texture edges smoother if resolution is low
    //texture.setSmooth(true);

    //gets window size and set position of player sprite to middle of window
    sf::Vector2f size = (sf::Vector2f)window.getSize();
    sf::Sprite *playerSprite = player.getSprite();
    playerSprite->setPosition(size.x/2 - playerTexture.getSize().x/2, size.y/2 - playerTexture.getSize().y);

    float rectSize = 50.0f;

    //list to keep track of all objects that player can collide with
    std::vector<sf::RectangleShape> blockList;

    //creates line of blocks across the screen
    for(int i = 0; i < size.x; i += rectSize)
    {
        sf::RectangleShape r(sf::Vector2f(rectSize,rectSize));
        r.setFillColor(sf::Color::Red);
        r.setPosition(i,size.y/2);

        blockList.push_back(r);
    }

    //random block
    sf::RectangleShape r(sf::Vector2f(rectSize,rectSize));
    r.setFillColor(sf::Color::Red);
    r.setPosition(900,size.y/2 - 150);

    blockList.push_back(r);

    //random block
    sf::RectangleShape f(sf::Vector2f(rectSize,rectSize));
    f.setFillColor(sf::Color::Red);
    f.setPosition(1200,size.y/2 - 50);

    blockList.push_back(f);

    while (window.isOpen())
    {
        sf::Event event;

        while (window.pollEvent(event))
        {

            if (event.type == sf::Event::Closed)
            {
                window.close();
            }
        }

        player.move(&blockList);

        window.clear();
        for(sf::RectangleShape b: blockList)
        {
            window.draw(b);
        }
        window.draw(*playerSprite);
        window.display();
    }
}

void Game::draw(int n, ...)
{
    //look at variadic templates c++ to add however many elements needed to draw and then calling it in run()
}