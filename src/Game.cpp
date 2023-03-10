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

    sf::Texture heartTexture;

    if(!heartTexture.loadFromFile("resources/Images/heart-icon.png")) //takes texture from resources folder
    {
        std::cout << "failed to load image.";
    }

    playerTextures.push_back(heartTexture);

    //load enemy textures
    std::vector<sf::Texture> enemyTextures;

    sf::Texture enemyTexture;

    if(!enemyTexture.loadFromFile("resources/Images/Adam.jpg")) //takes texture from resources folder
    {
        std::cout << "failed to load image.";
    }

    enemyTextures.push_back(enemyTexture);

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

    //allocates memory for player since there is no default constructor that allows global variable otherwise
    player = new Player(&textures["Player"], 10.0f, 12.0f, 1.0f);  //instantiates player. passes player textures, max x-axis speed, max y-axis speed, and acceleration rate

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

    sf::View view(sf::FloatRect(0.0f,0.0f,1920.0f,1080.0f));

    window.setView(view);

    Button startBtn("startBtn","Start", &font);

    Button exitBtn("exitBtn","Exit", &font);

    buttons.push_back(startBtn);

    buttons.push_back(exitBtn);
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
            createdState[state] = false;
            state = FIRST_LEVEL;
        }
        if(id == "exitBtn")
        {
            window.close();
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

    for(Entity *entity: entities)
    {
        window.draw(*entity->getSprite());
    }

    window.draw(*player->getSprite());

    drawUI();

    pause.draw(&window);

    std::string id = mouseCollision();

    if(id != "" && clicked)
    {
        if(id == "menuBtn")
        {
            createdState[savedState] = false;
            createdState[state] = false;
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

    entities.clear();

    player->setHealth(5);

    sf::View view(sf::FloatRect(0.0f,0.0f,1920.0f,1080.0f));

    window.setView(view);

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

    Block r(&textures["Block"]);
    r.getSprite()->setPosition(900,476);
    blocks.push_back(r);

    Block w(&textures["Block"]);
    w.getSprite()->setPosition(1220,476);
    blocks.push_back(w);

    /*
        entities is a vector of derived objects so it has contain pointers otherwise object splicing occurs. 
        allocates memory for enemy otherwise data is only copied and the data that the pointer points to is
        overwritten by the program with other variables.
    */
    Enemy *enemy = new Enemy(&textures["Player"],10.0f,0.0f,1.0f);
    enemy->getSprite()->setPosition(1000,476);
    entities.push_back(enemy);
}

void Game::firstLevel()
{
    player->move();

    playerCollision();

    player->getSprite()->move(sf::Vector2f(player->getXVel(),player->getYVel()));

    sf::View view = window.getView();
    view.setCenter(player->getSprite()->getPosition());

    window.setView(view);

    for(Entity *entity : entities)
    {
        if(entity->getClass() == "Enemy")
        {
            ((Enemy *)entity)->move();
        }
    }

    window.clear();

    for(Block block : blocks)
    {
        window.draw(*block.getSprite());
    }

    for(Entity *entity: entities)
    {
        window.draw(*entity->getSprite());
    }

    window.draw(*player->getSprite());

    drawUI();

    window.display();
}

void Game::playerCollision()
{
    //collision with screen

    //collision with entities
    for(int i = 0; i < entities.size(); i++)
    {
        if(player->getSprite()->getGlobalBounds().intersects(entities.at(i)->getSprite()->getGlobalBounds()))
        {
            player->decreaseHealth();
            entities.erase(entities.begin()+i);
        }
    }

    //collision with blocks
    for(Block b : blocks) //goes through list of blocks
    {
        sf::FloatRect blockBounds = b.getSprite()->getGlobalBounds();
        sf::FloatRect playerBounds = player->getSprite()->getGlobalBounds();
        sf::FloatRect nextBounds = player->getSprite()->getGlobalBounds();
        nextBounds.left += player->getXVel();
        nextBounds.top += player->getYVel();

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
    sf::Vector2f mousePos = window.getView().getCenter() - window.getView().getSize() / 2.0f + (sf::Vector2f)sf::Mouse::getPosition();

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
                createdState[state] = false;
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
                clicked = true;
            }
        }
    }
}

void Game::drawUI()
{
    //draws hearts
    for(int i = 0; i < player->getHealth(); i++)
    {
        sf::Vector2u textureSize = textures["Player"].at(1).getSize();
        sf::RectangleShape heart(sf::Vector2f(64,64));
        heart.setTexture(&textures["Player"].at(1));
        sf::View view = window.getView();
        heart.setPosition(view.getCenter().x - view.getSize().x / 2 + (i + 1) * 64, view.getCenter().y - view.getSize().y / 2 + 100);
        window.draw(heart);
    }
}

void Game::enemyCollision(Enemy *enemy)
{
    for(Block block : blocks)
    {
        // if(enemy->getSprite()->getGlobalBounds().intersects(block.getSprite()->getGlobalBounds()))
        // {
        //     if(enemy->getAccel() > 0)
        //     {
        //         enemy->getSprite()->setPosition(block.getSprite()->getPosition().x - enemy->getSprite()->getGlobalBounds().width, enemy->getSprite()->getGlobalBounds().top);
        //     }
        //     else
        //     {
        //         enemy->getSprite()->setPosition(block.getSprite()->getPosition().x + block.getSprite()->getGlobalBounds().width, enemy->getSprite()->getGlobalBounds().top);
        //     }
        //     enemy->setAccel(-enemy->getAccel());
        //     enemy->setXVel(0);
        // }
    }
}





