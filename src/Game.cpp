#include "headers/Game.hpp"

Game::Game()
{
    initWindow();

    loadTextures();

    run();
}

Game::~Game()
{
    delete player;
}

//initializes window
void Game::initWindow()
{
    //sets default size for window, creates title, and sets style to fullscreen
    window.create(sf::VideoMode(1920,1080), "Ninja Platofmrer",sf::Style::Fullscreen);

    //syncs frames with refresh rate of monitor
    window.setVerticalSyncEnabled(true);
    
    //key presses cannot repeat so holding down keys isn't possible
    window.setKeyRepeatEnabled(false);
}

//loads textures
void Game::loadTextures()
{
    //load player textures
    std::vector<sf::Texture> playerTextures;

    sf::Texture playerTexture;

    if(!playerTexture.loadFromFile("resources/Images/Adam.jpg")) //takes texture from resources folder
    {
        std::cout << "failed to load image.";
    }

    playerTextures.push_back(playerTexture);

    //load enemy textures
    std::vector<sf::Texture> enemyTextures;

    //load block textures
    std::vector<sf::Texture> blockTextures;

    sf::Texture blockTexture;

    if(!blockTexture.loadFromFile("resources/Images/Adam.jpg")) //takes texture from resources folder
    {
        std::cout << "failed to load image.";
    }
    
    blockTextures.push_back(blockTexture);

    //inserts lists into map
    textures["Player"] = playerTextures;
    textures["Enemy"] = enemyTextures;
    textures["Block"] = blockTextures;

    //loads font
    if(!font.loadFromFile("resources/Fonts/Roboto-Black.ttf"))
    {
        std::cout << "failed to load font";
    }
}

//runs the game loop
void Game::run()
{
    //sets initial state of game at main menu
    state = MAIN_MENU;
    savedState = state;

    //array contains booleans and checks whether the setup function for a state has been performed
    bool createdState[sizeof(State)];

    player = new Player(&textures["Player"], 10.0f, 10.0f, 1.0f);  //instantiates player. passes player textures, max x-axis speed, max y-axis speed, and acceleration rate

    while (window.isOpen())
    {
        sf::Event event;

        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
            {
                window.close();
            }

            handleInput(&event);
        }

        switch(state)
        {
            case MAIN_MENU:
                if(!createdState[MAIN_MENU])
                {
                    setMainMenu(); //set up
                    createdState[savedState] = false;
                    createdState[MAIN_MENU] = true;
                }
                mainMenu(); //logic
                break;
            case PAUSE_MENU:
                if(!createdState[PAUSE_MENU])
                {
                    setPauseMenu(); //set up
                    createdState[PAUSE_MENU] = true; //not inserting false to previous state in case we want to go back
                }
                pauseMenu(); //logic
                break;
            case FIRST_LEVEL:
                if(!createdState[FIRST_LEVEL])
                {
                    setFirstLevel();
                    createdState[savedState] = false;
                    createdState[FIRST_LEVEL] = true;
                }
                firstLevel();
                break;
        }
    }
}

void Game::setMainMenu()
{
    buttons.clear();

    Button startBtn("startBtn","Start", &font);

    Button optionsBtn("optionsBtn","Options", &font);

    buttons.push_back(startBtn);

    buttons.push_back(optionsBtn);
}

void Game::mainMenu()
{
    window.clear();

    Menu menu("Ninja Platformer",&buttons,&font);

    menu.draw(&window);

    std::string id = mouseCollision();

    if(id != "" && clicked)
    {
        if(id == "startBtn")
        {
            state = FIRST_LEVEL;
        }
        clicked = false;
    }

    window.display();
}

void Game::setPauseMenu()
{
    buttons.clear();

    Button menuBtn("menuBtn","Menu", &font);

    Button firstBtn("firstBtn","First Level", &font);

    Button secondBtn("secondBtn","Second Level", &font);

    Button thirdBtn("thirdBtn","Third Level", &font);

    buttons.push_back(menuBtn);
    buttons.push_back(firstBtn);
    buttons.push_back(secondBtn);
    buttons.push_back(thirdBtn);
}

void Game::pauseMenu()
{
    window.clear();
    
    Menu pause("Paused",&buttons,&font);

    for(Block block : blocks)
    {
        window.draw(*block.getSprite());
    }

    window.draw(*player->getSprite());

    pause.draw(&window);

    std::string id = mouseCollision();

    if(id != "" && clicked)
    {
        if(id == "menuBtn")
        {
            state = MAIN_MENU;
        }
        else if(id == "firstBtn")
        {
            state = FIRST_LEVEL;
        }
        clicked = false;
    }

    window.display();
}

void Game::setFirstLevel()
{
    blocks.clear();

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
        blocks.push_back(b);
    }
}

void Game::firstLevel()
{
    movePlayer();

    window.clear();

    for(Block block : blocks)
    {
        window.draw(*block.getSprite());
    }

    window.draw(*player->getSprite());
    
    window.display();
}

void Game::movePlayer()
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

    if(player->getJumping()) //up
    {
        if(yVel == 0 && player->getContactBottom())
        {
            yVel = -yMax;
            player->setContactBottom(false);
        }
    }
    else //down
    {
        if(yVel < yMax)
        {
            yVel += accel;
        }
    }

    player->setJumping(false);

    player->setXVel(xVel);
    player->setYVel(yVel);

    //modifies next state
    nextBounds.left += xVel;
    nextBounds.top += yVel;

    //check collision
    playerCollision(&nextBounds);

    //moves sprite
    player->getSprite()->move(player->getXVel(),player->getYVel());
}

void Game::playerCollision(sf::FloatRect *_nextBounds)
{
    //collision with screen

    //collision with entities

    //collision with blocks
    for(Block b : blocks) //goes through list of blocks
    {
        sf::FloatRect blockBounds = b.getSprite()->getGlobalBounds();
        sf::FloatRect playerBounds = player->getSprite()->getGlobalBounds();
        sf::FloatRect nextBounds = *_nextBounds;

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

std::string Game::mouseCollision()
{
    //collision with buttons
    sf::Vector2f mousePos = (sf::Vector2f)sf::Mouse::getPosition();

    sf::RectangleShape r(sf::Vector2f(1,1));

    r.setPosition(mousePos);

    for(int i = 0; i < buttons.size(); i++)
    {
        Button *b = &buttons.at(i);
        if(r.getGlobalBounds().intersects(b->getRect()->getGlobalBounds()))
        {
            b->highlightButton(&window);
            return b->getID();
        }
    }

    return "";
}

void Game::handleInput(sf::Event *event)
{
    if(event->type == sf::Event::KeyPressed)
    {   
        if(state != MAIN_MENU && state != PAUSE_MENU)
        {
            if(event->key.code == sf::Keyboard::Escape)
            {
                savedState = state;
                state = PAUSE_MENU;
            }

            if(event->key.code == sf::Keyboard::Space)
            {
                player->setJumping(true);
            }
        }
        else if(state == PAUSE_MENU)
        {
            if(event->key.code == sf::Keyboard::Escape)
            {
                state = savedState;
            }
        }
    }
    else if(event->type == sf::Event::MouseButtonPressed)
    {
        if(state == MAIN_MENU || state == PAUSE_MENU)
        {
            if(event->mouseButton.button == sf::Mouse::Left)
            {
                savedState = state;
                clicked = true;
            }
        }
    }
}









