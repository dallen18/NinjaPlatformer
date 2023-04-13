#include "headers/Game.hpp"
#include "headers/Hud.hpp"
#include "headers/tinyxml2.h"
#include <SFML/Graphics/Rect.hpp>
#include <SFML/System/Vector2.hpp>
#include <fstream>
#include <string>

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
    sf::Texture playerTexture;

    if(!playerTexture.loadFromFile("resources/Images/Adam.jpg")) //takes texture from resources folder
    {
        std::cout << "failed to load image.";
    }

    sf::Texture heartTexture;

    if(!heartTexture.loadFromFile("resources/Images/heart-icon.png")) //takes texture from resources folder
    {
        std::cout << "failed to load image.";
    }

    //load enemy textures
    sf::Texture enemyTexture;

    if(!enemyTexture.loadFromFile("resources/Images/Adam.jpg")) //takes texture from resources folder
    {
        std::cout << "failed to load image.";
    }

    //load block textures
    sf::Texture blockTexture;

    if(!blockTexture.loadFromFile("resources/Images/cavesofgallet.png")) //takes texture from resources folder
    {
        std::cout << "failed to load image.";
    }
    
    //inserts lists into map
    textures["Player"] = playerTexture;
    textures["Heart"] = heartTexture;
    textures["Enemy"] = enemyTexture;
    textures["Block"] = blockTexture;

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
            case PLAYING:
                if(!createdState[PLAYING])
                {
                    setLevel("resources/Levels/NinjaLevelOne.tmx");
                    createdState[savedState] = false;
                    createdState[PLAYING] = true;
                }
                playLevel();
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
            state = PLAYING;
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

    buttons.push_back(menuBtn);
    buttons.push_back(firstBtn);
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

    Hud hud(player, &textures["Heart"]);
    hud.draw(&window);

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
            state = PLAYING;
        }
        clicked = false;
    }

    window.display();
}

void Game::setLevel(std::string filename)
{
    blocks.clear();

    entities.clear();

    sf::View view(sf::FloatRect(0.0f,0.0f,1920.0f,1080.0f));

    //view.zoom(0.25f);

    window.setView(view);

    //allocates memory for player since there is no default constructor that allows global variable otherwise
    if(player == NULL)
    {
        player = new Player(&textures["Player"], 6.0f, 12.0f, 1.0f, 16, 16);  //instantiates player. passes player textures, max x-axis speed, max y-axis speed, and acceleration rate
    }

    player->setHealth(5);

    //gets window size and set position of player sprite to middle of window
    //sf::Vector2f windowSize = (sf::Vector2f)window.getSize();
    //get info from xml files
    
    tinyxml2::XMLDocument level;
    level.LoadFile(filename.c_str());

    tinyxml2::XMLDocument sheet;
    sheet.LoadFile("resources/Levels/cavesofgallet.tsx");

    int tileCount = std::stoi(sheet.RootElement()->Attribute("tilecount"));
    int columns = std::stoi(sheet.RootElement()->Attribute("columns"));

    int levelWidth = std::stoi(level.RootElement()->FirstChildElement("layer")->Attribute("width"));
    int levelHeight = std::stoi(level.RootElement()->FirstChildElement("layer")->Attribute("height"));

    int blockWidth = std::stoi(level.RootElement()->Attribute("tilewidth"));
    int blockHeight = std::stoi(level.RootElement()->Attribute("tileheight"));

    sf::Vector2f playerPosition;
    std::vector<sf::Vector2f> enemyPositions;

    auto element = level.RootElement()->FirstChildElement("objectgroup")->FirstChild();

    sf::Sprite *playerSprite = player->getSprite();
    playerSprite->setPosition(std::stoi(element->ToElement()->Attribute("x")),std::stoi(element->ToElement()->Attribute("y")));

    element = level.RootElement()->FirstChildElement("objectgroup")->NextSibling()->FirstChild();
    while(element != NULL)
    {
        Enemy *enemy = new Enemy(&textures["Player"],3.0f,4.0f,1.0f,16,16);
        enemy->getSprite()->setPosition(std::stoi(element->ToElement()->Attribute("x")),std::stoi(element->ToElement()->Attribute("y")));
        entities.push_back(enemy);
        element = element->NextSibling();
    }

    // parse data to create blocks and rotate them
    std::string d = level.RootElement()->FirstChildElement("layer")->FirstChildElement()->GetText();
    
    char c = d[1];
    int i = 0;
    int x = 0;
    int y = 0;
    std::vector<long> line;
    std::string num;
    while(c != '\0')
    {
        if(c == ',')
        {
            line.push_back(std::stol(num));
            num.clear();
            long val = line.back();
            sf::Vector2f scale(1.0f,1.0f);
            if(val > 0x80000000)
            {
                val -= 0x80000000;
                scale.x *= -1;
            }

            if(val > 0x40000000)
            {
                val -= 0x40000000;
                scale.y *= -1; 
            }

            if(val > tileCount)
            {
                val -= 1024;
            }
            else
            {
                
            }

            if(val > 0)
            {
                Block b(&textures["Block"],x * blockWidth,y * blockHeight,sf::IntRect(((val - 1) % columns) * blockWidth, ((val - 1) / columns) * blockHeight, blockWidth, blockHeight), scale);
                blocks.push_back(b);
            }
            x++;
        }
        else if(c == '\n')
        {
            y += 1;
            x = 0;
        }
        else
        {
            num.push_back(c);
        }
        i += 1;
        c = d[i];
    }
}

void Game::playLevel()
{
    window.clear();

    // check input
    
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
   
    // check collision 
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
        b.width = bl.getSprite()->getGlobalBounds().width;
        b.height = bl.getSprite()->getGlobalBounds().height;

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

    //std::cout << player->getSprite()->getGlobalBounds().top;
    
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
            
                sf::RectangleShape background(sf::Vector2f(220,str.size() + 20));

                background.setFillColor(sf::Color::White);

                background.setPosition(t.getPosition().x - 10, t.getPosition().y - 10);

                window.draw(background);
                
                for(int i = 0; i < str.size(); i++)
                {
                    if(str[i] != '\n')
                    {
                        //std::cout << str[i];
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
            b.width = bl.getSprite()->getGlobalBounds().width;
            b.height = bl.getSprite()->getGlobalBounds().height;

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

    // Drawing all Entities, Blocks, and UI to the screen

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

    Hud hud(player, &textures["Heart"]);
    hud.draw(&window);

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
