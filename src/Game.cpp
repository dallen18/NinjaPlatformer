#include "headers/Game.hpp"
#include <SFML/Graphics/Glyph.hpp>
#include <SFML/Graphics/Rect.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <chrono>
#include <thread>

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
    //window.setVerticalSyncEnabled(true);
    
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
using namespace std::chrono_literals;
//runs the game loop
void Game::run()
{
    //sets initial state of game at main menu
    state = MAIN_MENU;
    savedState = state;

    //allocates memory for player since there is no default constructor that allows global variable otherwise
    player = new Player(&textures["Player"], 10.0f, 12.0f, 1.0f, 64, 64);  //instantiates player. passes player textures, max x-axis speed, max y-axis speed, and acceleration rate

    //auto start = std::chrono::high_resolution_clock::now();
    //std::this_thread::sleep_for(1s);
    //auto end = std::chrono::high_resolution_clock::now();
    //std::chrono::duration<float> duration = end - start;
    
    //auto start = std::chrono::high_resolution_clock::now();
    int countedFrames = 0;
    while (window.isOpen())
    {
        auto start = std::chrono::high_resolution_clock::now();
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
        auto end = std::chrono::high_resolution_clock::now();
        std::chrono::duration<float> duration = end - start;
        float avg = countedFrames / duration.count() * 1000;
        auto sleep = SCREEN_TICKS_PER_FRAME - duration.count();
        //std::cout << sleep;
        if(duration.count() * 1000 < SCREEN_TICKS_PER_FRAME)
        {
            std::this_thread::sleep_for(std::chrono::microseconds((int)(sleep*1000)));
        }
        //std::cout << 1/(sleep/1000) << "FPS" <<"\n";
        countedFrames += 1;
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
    playerSprite->setPosition(windowSize.x/2 - playerSprite->getGlobalBounds().width/2, windowSize.y/2 - playerSprite->getGlobalBounds().height * 2 - 200);

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
    Enemy *enemy = new Enemy(&textures["Player"],10.0f,12.0f,1.0f,64,64);
    enemy->getSprite()->setPosition(1000,400);
    entities.push_back(enemy);

    NPC *npc = new NPC(&textures["Player"],10.0f,12.0f,1.0f,64,64,"Hello, my name is Adam! I love eating raw potatoes while watching Korean dramas. My favorite instrument is the ocarina I stole from my four year old cousin.");
    npc->getSprite()->setPosition(500,476);
    entities.push_back(npc);
}

void Game::firstLevel()
{
    window.clear();
    
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::D)) //right
    {
        player->setRight(true);
    }
    else
    {
        player->setRight(false);
    }
    
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::A)) //left
    {
        player->setLeft(true);
    }
    else
    {
        player->setLeft(false);
    }

    player->move();

    //playerCollision();
    sf::Rect<float> a, b;

    a.left = player->getSprite()->getPosition().x;
    a.top = player->getSprite()->getPosition().y;
    a.width = player->getXSize();
    a.height = player->getYSize();
    
    bool checkX;
    bool checkY;

    for(Block bl : blocks)
    {
        b.left = bl.getSprite()->getPosition().x;
        b.top = bl.getSprite()->getPosition().y;
        b.width = 64;
        b.height = 64;

        a.left += player->getXVel();
        checkX = checkCollision(a, b);
        if(checkX)
        {
            a.left -= player->getXVel();
            if(a.left < b.left)
            {
                a.left =  b.left - a.width;
            }
            else
            {
                a.left = b.left + b.width;
            }
            player->getSprite()->setPosition(a.left,a.top);
            player->setXVel(0);
        }
        else
        {
            a.left -= player->getXVel();
        }

        a.top += player->getYVel();
        checkY = checkCollision(a, b);
        if(checkY)
        {
            a.top -= player->getYVel();
            if(a.top < b.top)
            {
                a.top = b.top - a.height;
            }
            else
            {
                a.top = b.top + b.height;
            }
            player->getSprite()->setPosition(a.left,a.top);
            player->setYVel(0);
            player->setContactBottom(true);
        }
        else
        {
            a.top -= player->getYVel();
        }

        if(checkX && checkY)
        {
            break;
        }
    }
    
    player->getSprite()->move(player->getXVel(),player->getYVel());
    
    for(int i = 0; i <  entities.size(); i++)
    {
        Entity *entity = entities.at(i);
        b.left = entity->getSprite()->getPosition().x;
        b.top = entity->getSprite()->getPosition().y;
        bool c = checkCollision(a, b);
        if(c)
        {
            if(entity->getClass() == "Enemy")
            {
                player->decreaseHealth();
                if(player->getHealth() == 0)
                {
                    state = MAIN_MENU;
                }
                entities.erase(entities.begin() + i);
            }
            else if(entity->getClass() == "NPC")
            {
                std::string str = ((NPC*)entity)->getString();
                std::string part;
                sf::Text t;
                t.setFont(font);
                t.setCharacterSize(20);
                t.setFillColor(sf::Color::Blue);
                t.setPosition(entity->getSprite()->getPosition().x,entity->getSprite()->getPosition().y - str.size());
                //t.setString("hello");
                //window.draw(t);
            
                sf::RectangleShape background(sf::Vector2f(220,str.size() + 20));

                background.setFillColor(sf::Color::White);

                background.setPosition(t.getPosition().x - 10, t.getPosition().y - 10);

                window.draw(background);
                
                for(int i = 0; i < str.size(); i++)
                {
                    if(str[i] != '\n')
                    {
                        std::cout << str[i];
                        part.push_back(str[i]);
                    }
                    else
                    {
                        t.setString(part);
                        window.draw(t);
                        part.clear();
                        t.move(0,20);
                    } 
                }
                t.setString(part);
                window.draw(t);
            }
        }
    }
    
    for(Entity *entity: entities)
    {
        entity->move();

        a.left = entity->getSprite()->getPosition().x;
        a.top = entity->getSprite()->getPosition().y;
        a.width = entity->getXSize();
        a.height = entity->getYSize();
        checkX = false;
        checkY = false;

        for(Block bl : blocks)
        {
            b.left = bl.getSprite()->getPosition().x;
            b.top = bl.getSprite()->getPosition().y;
            b.width = 64;
            b.height = 64;

            a.left += entity->getXVel();
            checkX = checkCollision(a, b);
            if(checkX)
            {
                a.left -= entity->getXVel();
                if(a.left < b.left)
                {
                    a.left =  b.left - a.width;
                }
                else
                {
                    a.left = b.left + b.width;
                }
                entity->setAccel(entity->getAccel() * -1);
                entity->getSprite()->setPosition(a.left,a.top);
                entity->setXVel(0);
            }
            else
            {
                a.left -= entity->getXVel();
            }

            a.top += entity->getYVel();
            checkY = checkCollision(a, b);
            if(checkY)
            {
                a.top -= entity->getYVel();
                if(a.top < b.top)
                {
                    a.top = b.top - a.height;
                }
                else
                {
                    a.top = b.top + b.height;
                }
                entity->getSprite()->setPosition(a.left,a.top);
                entity->setYVel(0);
            }
            else
            {
                a.top -= entity->getYVel();
            }

            if(checkX && checkY)
            {
                break;
            }
        }

        entity->getSprite()->move(entity->getXVel(),entity->getYVel());
    }

    sf::View view = window.getView();
    view.setCenter(player->getSprite()->getPosition());

    window.setView(view);

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

bool Game::checkCollision(sf::Rect<float> a, sf::Rect<float> b)
{
    float leftA, leftB;
    float rightA, rightB;
    float topA, topB;
    float bottomA, bottomB;

    leftA = a.left;
    rightA = a.left + a.width;
    topA = a.top;
    bottomA = a.top + a.height;
    
    leftB = b.left;
    rightB = b.left + b.width;
    topB = b.top;
    bottomB = b.top + b.height;

    if(bottomA <= topB)
    {
        return false;
    }

    if(topA >= bottomB)
    {
        return false;
    }

    if(rightA <= leftB)
    {
        return false;
    }

    if(leftA >= rightB)
    {
        return false;
    }

    return true;
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
                if(player->getContactBottom())
                {
                    player->setJumping(true);
                }
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





