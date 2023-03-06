#include "headers/Game.hpp"

Game::Game()
{
    initWindow();

    loadTextures();

    run();
}

Game::~Game()
{

}

//initializes window
void Game::initWindow()
{
    //sets default size for window, creates title, and sets style to fullscreen
    window.create(sf::VideoMode(640, 360), "Ninja Platofmrer",sf::Style::Fullscreen);

    //syncs frames with refresh rate of monitor
    window.setVerticalSyncEnabled(true);
}

//loads textures
void Game::loadTextures()
{
    //load player textures
    std::vector<sf::Texture> playerTextures;

    sf::Texture playerTexture;

    if(!playerTexture.loadFromFile("resources/Adam.jpg")) //takes texture from resources folder
    {
        std::cout << "failed to load image.";
    }

    playerTextures.push_back(playerTexture);

    //load enemy textures
    std::vector<sf::Texture> enemyTextures;

    //load block textures
    std::vector<sf::Texture> blockTextures;

    sf::Texture blockTexture;

    if(!blockTexture.loadFromFile("resources/Adam.jpg")) //takes texture from resources folder
    {
        std::cout << "failed to load image.";
    }
    
    blockTextures.push_back(blockTexture);

    //inserts lists into map
    textures["Player"] = playerTextures;
    textures["Enemy"] = enemyTextures;
    textures["Block"] = blockTextures;

    //loads font
    if(!font.loadFromFile("resources/Roboto-Black.ttf"))
    {
        std::cout << "failed to load font";
    }
}

//runs the game loop
void Game::run()
{
    //sets initial state of game at main menu
    state = MAIN_MENU;

    //check if setup has been performed
    bool createdMenu;
    bool createdPause;
    bool createdFirst;

    //lists of interactable objecs
    std::vector<Entity> entities;
    
    std::vector<Block> blocks;

    std::vector<Button> buttons;

    Player player(&textures["Player"], 10.0f, 10.0f, 1.0f); //instantiates player. passes player textures, max x-axis speed, max y-axis speed, and acceleration rate

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

        switch(state)
        {
            case MAIN_MENU:
                if(!createdMenu)
                {
                    setMainMenu(&buttons);
                    createdMenu = true;
                    createdPause = false;
                    createdFirst = false;
                }
                mainMenu(&buttons);
                break;
            case PAUSE_MENU:
                if(!createdPause)
                {
                    setPauseMenu(&buttons);
                    createdPause = true;
                }
                pauseMenu(&buttons, &blocks, &entities, &player);
                break;
            case FIRST_LEVEL:
                if(!createdFirst)
                {
                    setFirstLevel(&blocks, &entities, &player);
                    createdMenu = false;
                    createdPause = false;
                    createdFirst = true;
                }
                firstLevel(&blocks, &entities, &player);
                break;
            case SECOND_LEVEL:
                break;
            case THIRD_LEVEL:
                break;
        }
    }
}

void Game::setMainMenu(std::vector<Button> *buttons)
{
    std::cout << "main menu";

    buttons->clear();

    Button startBtn("startBtn","Start", &font);

    Button optionsBtn("optionsBtn","Options", &font);

    buttons->push_back(startBtn);

    buttons->push_back(optionsBtn);
}

void Game::mainMenu(std::vector<Button> *buttons)
{
    window.clear();

    Menu menu("Ninja Platformer",buttons,&font);

    menu.draw(&window);

    std::string id = mouseCollision(buttons);

    if(id != "" && sf::Mouse::isButtonPressed(sf::Mouse::Right))
    {
        if(id == "startBtn")
        {
            state = FIRST_LEVEL;
        }
    }

    window.display();
}

void Game::setPauseMenu(std::vector<Button> *buttons)
{
    buttons->clear();

    Button menuBtn("menuBtn","Menu", &font);

    Button firstBtn("firstBtn","First Level", &font);

    Button secondBtn("secondBtn","Second Level", &font);

    Button thirdBtn("thirdBtn","Third Level", &font);

    buttons->push_back(menuBtn);
    buttons->push_back(firstBtn);
    buttons->push_back(secondBtn);
    buttons->push_back(thirdBtn);
}

void Game::pauseMenu(std::vector<Button> *buttons, std::vector<Block> *blocks, std::vector<Entity> *entities, Player *player)
{
    window.clear();

    Menu pause("Paused",buttons,&font);

    for(Block block : *blocks)
    {
        window.draw(*block.getSprite());
    }
    window.draw(*player->getSprite());

    pause.draw(&window);

    std::string id = mouseCollision(buttons);

    if(id != "" && sf::Mouse::isButtonPressed(sf::Mouse::Right))
    {
        if(id == "menuBtn")
        {
            state = MAIN_MENU;
        }
        else if(id == "firstBtn")
        {
            state = FIRST_LEVEL;
        }
        else if(id == "secondBtn")
        {
            state = SECOND_LEVEL;
        }
        else if(id == "thirdBtn")
        {
            state = THIRD_LEVEL;
        }
    }

    window.display();
}

void Game::setFirstLevel(std::vector<Block> *blocks, std::vector<Entity> *entities, Player *player)
{
    std::cout << "first level";

    blocks->clear();
    entities->clear();

    //gets window size and set position of player sprite to middle of window
    sf::Vector2f windowSize = (sf::Vector2f)window.getSize();
    sf::Sprite *playerSprite = player->getSprite();
    playerSprite->setPosition(windowSize.x/2 - playerSprite->getGlobalBounds().width/2, windowSize.y/2 - playerSprite->getGlobalBounds().height * 2);

    int playerSize = playerSprite->getTexture()->getSize().x;

    //creates line of blocks across the screen
    for(int i = 0; i < windowSize.x; i += playerSize)
    {
        Block b(&textures["Block"]);
        b.getSprite()->setPosition(i,windowSize.y/2);
        blocks->push_back(b);
    }
}

void Game::firstLevel(std::vector<Block> *blocks, std::vector<Entity> *entities, Player *player)
{
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
    {
        state = PAUSE_MENU;
    }

    movePlayer(blocks, entities, player);

    window.clear();
    for(Block block : *blocks)
    {
        window.draw(*block.getSprite());
    }
    // for(Entity entity : entities)
    // {
    //     window.draw(*entity.getSprite());
    // }
    window.draw(*player->getSprite());
    window.display();
}

void Game::movePlayer(std::vector<Block> *blocks, std::vector<Entity> *entities, Player *player)
{
    //floatRects contain coordinates and sizes of current state of player and next state
    sf::FloatRect playerBounds = player->getSprite()->getGlobalBounds();
    sf::FloatRect nextBounds = playerBounds;

    float xVel = player->getXVel();
    float yVel = player->getYVel();
    float xMax = player->getXMax();
    float yMax = player->getYMax();
    float accel = player->getAccel();

    if(sf::Keyboard::isKeyPressed(sf::Keyboard::D)) //right
    {
        if(xVel < xMax)
        {
            xVel += accel;
        }
    }
    else if(sf::Keyboard::isKeyPressed(sf::Keyboard::A)) //left
    {
        if(xVel > -xMax)
        {
            xVel -= accel;
        }
    }
    else
    {
        if(xVel > 0)
        {
            xVel -= accel;
        }
        else if(xVel < 0)
        {
            xVel += accel;
        }
    }

    bool spacePressed = false;

    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) //up
    {
        if(yVel == 0 && player->getContactBottom())
        {
            yVel = -yMax;
            spacePressed = true;
            player->setContactBottom(false);
        }
    }

    if(!spacePressed) //down
    {
        if(yVel < yMax)
        {
            yVel += accel;
        }
    }

    player->setXVel(xVel);
    player->setYVel(yVel);

    //modifies next state
    nextBounds.left += xVel;
    nextBounds.top += yVel;

    //check collision
    playerCollision(entities, blocks, player, &nextBounds);

    //moves sprite
    player->getSprite()->move(player->getXVel(),player->getYVel());
}

void Game::playerCollision(std::vector<Entity> *entities, std::vector<Block> *blocks, Player *player, sf::FloatRect *n)
{
    //collision with screen

    //collision with entities

    //collision with blocks
    for(Block b : *blocks) //goes through list of blocks
    {
        sf::FloatRect blockBounds = b.getSprite()->getGlobalBounds();
        sf::FloatRect playerBounds = player->getSprite()->getGlobalBounds();
        sf::FloatRect nextBounds = *n;

        //collision with bottom of player
        if(playerBounds.top + playerBounds.height <= blockBounds.top
        && nextBounds.top + nextBounds.height > blockBounds.top
        && ((nextBounds.left > blockBounds.left && nextBounds.left < blockBounds.left + blockBounds.height) 
            ||(nextBounds.left + nextBounds.height > blockBounds.left && nextBounds.left + nextBounds.height < blockBounds.left + blockBounds.height)
            ||(nextBounds.left <= blockBounds.left && nextBounds.left + nextBounds.height >= blockBounds.left + blockBounds.height)))
        {
            player->setYVel(0.0f); //resets y-axis velocity
            player->getSprite()->setPosition(player->getSprite()->getPosition().x, blockBounds.top - playerBounds.height); //sets position to edge of block
            player->setContactBottom(true); //this boolean is used to check if the player is on the ground and is able to jump. go to move()
        }
        //collision with top of player
        else if(playerBounds.top >= blockBounds.top + blockBounds.height
        && nextBounds.top < blockBounds.top + blockBounds.height
        && ((nextBounds.left > blockBounds.left && nextBounds.left < blockBounds.left + blockBounds.height) 
            ||(nextBounds.left + nextBounds.height > blockBounds.left && nextBounds.left + nextBounds.height < blockBounds.left + blockBounds.height)
            ||(nextBounds.left <= blockBounds.left && nextBounds.left + nextBounds.height >= blockBounds.left + blockBounds.height)))
        {
            player->setYVel(0.0f);
            player->getSprite()->setPosition(player->getSprite()->getPosition().x, blockBounds.top + blockBounds.height);
        }
        //collision with right of player
        else if(playerBounds.left + playerBounds.width <= blockBounds.left 
        && nextBounds.left + nextBounds.width > blockBounds.left
        && ((nextBounds.top > blockBounds.top && nextBounds.top < blockBounds.top + blockBounds.height) 
            ||(nextBounds.top + nextBounds.height > blockBounds.top && nextBounds.top + nextBounds.height < blockBounds.top + blockBounds.height)
            ||(nextBounds.top <= blockBounds.top && nextBounds.top + nextBounds.height >= blockBounds.top + blockBounds.height)))
        {
            player->setXVel(0.0f); //resets x-axis velocity
            player->getSprite()->setPosition(blockBounds.left - playerBounds.width, player->getSprite()->getPosition().y);
        }
        //collision with left of player
        else if(playerBounds.left >= blockBounds.left + blockBounds.width
        && nextBounds.left < blockBounds.left + blockBounds.width
        && ((nextBounds.top > blockBounds.top && nextBounds.top < blockBounds.top + blockBounds.height) 
            ||(nextBounds.top + nextBounds.height > blockBounds.top && nextBounds.top + nextBounds.height < blockBounds.top + blockBounds.height)
            ||(nextBounds.top <= blockBounds.top && nextBounds.top + nextBounds.height >= blockBounds.top + blockBounds.height)))
        {
            player->setXVel(0.0f);
            player->getSprite()->setPosition(blockBounds.left + blockBounds.width, player->getSprite()->getPosition().y);
        }
    }
}

std::string Game::mouseCollision(std::vector<Button> *buttons)
{
    //collision with buttons
    sf::Vector2f mousePos = (sf::Vector2f)sf::Mouse::getPosition();

    sf::RectangleShape r(sf::Vector2f(1,1));

    r.setPosition(mousePos);

    for(int i = 0; i < buttons->size(); i++)
    {
        Button *b = &buttons->at(i);
        if(r.getGlobalBounds().intersects(b->getRect()->getGlobalBounds()))
        {
            b->highlightButton(&window);
            return b->getID();
        }
    }

    return "";
}