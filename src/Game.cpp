#include "headers/Game.hpp"

Game::Game()
{
    //initializes window
    initWindow();

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

void Game::run()
{
    sf::Texture playerTexture;

    //takes texture from resources folder
    if(!playerTexture.loadFromFile("resources/Adam.jpg"))
    {
        std::cout << "failed to load image.";
    }

    Player player(&playerTexture);

    //make texture edges smoother if resolution is low
    //texture.setSmooth(true);

    //gets window size and set position of player sprite to middle of window
    sf::Vector2u size = window.getSize();
    sf::Sprite *playerSprite = player.getSprite();
    playerSprite->setPosition(size.x/2,size.y/2);

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

        if(sf::Keyboard::isKeyPressed(sf::Keyboard::W))
        {
            playerSprite->move(0.0f,-player.getVelocity());
        }

        if(sf::Keyboard::isKeyPressed(sf::Keyboard::S))
        {
            playerSprite->move(0.0f,player.getVelocity());
        }   

        if(sf::Keyboard::isKeyPressed(sf::Keyboard::A))
        {
            playerSprite->move(-player.getVelocity(),0.0f);
        }   

        if(sf::Keyboard::isKeyPressed(sf::Keyboard::D))
        {
            playerSprite->move(player.getVelocity(),0.0f);
        }   
                
        window.clear();
        window.draw(*playerSprite);
        window.display();
    }

    //std::cout << "Hello World!";
}