#include "headers/Game.hpp"
#include "headers/Hud.hpp"
#include "headers/tinyxml2.h"
#include <SFML/Graphics/Rect.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/System/Vector2.hpp>
#include <SFML/Window/Keyboard.hpp>
#include <SFML/Window/Mouse.hpp>
#include <SFML/Window/WindowStyle.hpp>
#include <fstream>
#include <string>
#include <thread>
#include <cmath>

Game::Game()
{
    player = NULL;
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


    //inserts textures into map
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
    input = InputManager::getInstance();
    while (window.isOpen())
    {
        sf::Event event;

        while(window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
            {
                window.close();
                std:: cout <<"a";
            }
        }

        input->checkPlayerInput();
        auto pressed = input->getPressed();

        if(player != NULL)
        {
            if((*pressed)["Right"]) //right
            {
                player->setRight(true);
            }

            if((*pressed)["Left"])
            {
                player->setLeft(true);
            }
            
            if((*pressed)["Jump"])
            {
                player->setJumping(true);
            }

            if((*pressed)["Attack"])
            {
                player->setAttack(true);
            }

            if((*pressed)["Switch"])
            {
                int i = player->getMethod();
                if(i == 0)
                {
                    player->setMethod(1);
                }
                else
                {
                    player->setMethod(0);
                }
            }
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

    mouseCollision();

    if(input->checkOtherInput(sf::Mouse::Left, 1))
    {
        std::string id = mouseCollision();
        if(id == "startBtn")
        {
            createdState[state] = false;
            state = PLAYING;
        }
        if(id == "exitBtn")
        {
            window.close();
        }
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

    sf::View vie(sf::FloatRect(0.0f,0.0f,1920.0f,1080.0f));
    vie.setCenter(player->getSprite()->getPosition());
    vie.zoom(0.5f);
    window.setView(vie);

    if(input->checkOtherInput(sf::Keyboard::Escape, 0))
    {
        createdState[state] = false;
        state = savedState;
    }
    
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

    sf::View view(sf::FloatRect(0.0f,0.0f,1920.0f,1080.0f));
    view.setCenter(player->getSprite()->getPosition());
    window.setView(view);

    Hud hud(player, &textures["Heart"]);
    hud.draw(&window);

    pause.draw(&window);

    mouseCollision();

    if(input->checkOtherInput(sf::Mouse::Left, 1))
    {
        std::string id = mouseCollision();
        if(id == "menuBtn")
        {

            auto shurikens = player->getShurikens();
            shurikens->clear();
            delete player;
            player = NULL;
            createdState[savedState] = false;
            createdState[state] = false;
            state = MAIN_MENU;
            return;
        }
        else if(id == "firstBtn")
        {
            state = PLAYING;
        }
    }

    window.display();
}

void Game::setLevel(std::string filename)
{
    blocks.clear();

    entities.clear();

    sf::View view(sf::FloatRect(0.0f,0.0f,1920.0f,1080.0f));

    view.zoom(0.5f);

    window.setView(view);
    //allocates memory for player since there is no default constructor that allows global variable otherwise
    if(player == NULL)
    {

        player = new Player(&textures["Player"], 4.0f, 11.0f, 0.75f, 16, 16);  //instantiates player. passes player textures, max x-axis speed, max y-axis speed, and acceleration rate
        player->setHealth(3);
    }

 

    //get info from xml files
    tinyxml2::XMLDocument level;
    level.LoadFile(filename.c_str());

    // the source image isn't taken as of now from the .tsx file but will be in the future if we add more tile sets
    std::string source = "resources/Levels/";
    source += level.RootElement()->FirstChild()->ToElement()->Attribute("source");
    tinyxml2::XMLDocument sheet;
    sheet.LoadFile(source.c_str());

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
    int xc = std::stoi(element->ToElement()->Attribute("x"));
    int yc = std::stoi(element->ToElement()->Attribute("y"));
    
    playerSprite->setPosition(xc, yc);
    player->setX(xc);
    player->setY(yc);

    element = level.RootElement()->FirstChildElement("objectgroup")->NextSibling()->FirstChild();
    while(element != NULL)
    {
        Enemy *enemy = new Enemy(&textures["Player"],1.0f,10.0f,1.0f,16,16,true);
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
    //std::vector<long> line;
    std::string num;
    long long val = 0;
    while(c != '\0')
    {
        if(c == ',')
        {
            val = std::stoll(num);
            //line.push_back(std::stol(num
            num.clear();
            //long val = line.back();
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

    if(input->checkOtherInput(sf::Keyboard::Escape, 0))
    {
        savedState = state;
        state = PAUSE_MENU;
    }

    player->move();

    if(player->getAttack())
    { 
        player->createAttack();
    }

    // check collision 
    sf::Rect<float> a, b;
    
    bool checkX;
    bool checkY;

    auto shurikens = player->getShurikens();

    for(int i = 0; i < shurikens->size(); i++)
    {
        auto shuriken = shurikens->at(i);
        checkX = false;
        checkY = false;
        shuriken->move();
        a.left = shuriken->getX();
        a.top = shuriken->getY();
        a.width = 16;
        a.height = 16;

        for(Block bl : blocks)
        {
            b.left = bl.getX();
            b.top = bl.getY();
            b.width = bl.getSprite()->getGlobalBounds().width;
            b.height = bl.getSprite()->getGlobalBounds().height;
            a.left += shuriken->getXVel();
            checkX = checkCollision(a, b);
            if(checkX)
            {
                shurikens->erase(shurikens->begin() + i);
                break;
            }
            else
            {
                a.left -= shuriken->getXVel();
            }
            
            a.top += shuriken->getYVel();
            checkY = checkCollision(a, b);
            if(checkY)
            {
                shurikens->erase(shurikens->begin() + i);
                break;
            }
            else
            {
                a.top -= shuriken->getYVel();
            } 
        }

        bool enemyCheck = false;
        for(int l = 0; l < entities.size(); l++)
        {
            Entity *entity = entities.at(l);
            b.left = entity->getSprite()->getPosition().x;
            b.top = entity->getSprite()->getPosition().y;
            if(entity->getClass() == "Enemy")
            {
                bool c = checkCollision(a, b);
                if(c)
                {
                    entities.erase(entities.begin() + l);
                    enemyCheck = true;
                    break;
                }
            }
        }
        if(enemyCheck)
        {
            shurikens->erase(shurikens->begin() + i);
        }
        else
        {
            shuriken->getSprite()->move(shuriken->getXVel(),shuriken->getYVel());
            shuriken->setX(shuriken->getX() + shuriken->getXVel());
            shuriken->setY(shuriken->getY() + shuriken->getYVel());
        }
    }

    a.left = player->getSprite()->getPosition().x;
    a.top = player->getSprite()->getPosition().y;
    a.width = player->getXSize();
    a.height = player->getYSize();
    if((player->getSprite()->getPosition()).y>480){
        createdState[state] = false;
        state = MAIN_MENU;
    }
    
    checkX = false;
    checkY = false;

    for(Block bl : blocks)
    {
        b.left = bl.getX();
        b.top = bl.getY();
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
    player->setX(player->getX() + player->getXVel());
    player->setY(player->getY() + player->getYVel());

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
                    delete player;
                    for(auto shuriken : *shurikens)
                    {
                        delete shuriken;
                    }
                    player = NULL;
                    createdState[state] = false;
                    state = MAIN_MENU;
                    return;
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
            b.left = bl.getX();
            b.top = bl.getY();
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
                if(entity->getClass() == "Enemy")
                {
                    ((Enemy*)entity)->setContactBottom(true);
                }
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
    //view.setCenter(player->getSprite()->getPosition());
    int position1 = player->getSprite()->getPosition().x;
    if (position1<480){
        position1 = 480;
    }
    if (position1>2770){
        position1=2770;
    }
    view.setCenter(position1,240);
   // window.zoom(.5f);
    window.setView(view);
    if(player->getMethod() == 0)
    {
        sf::Vector2f mousePos = (sf::Vector2f)sf::Mouse::getPosition();
        sf::Vector2f playerPos = {960,540};
        sf::Vector2f difference = mousePos - playerPos;
        float hypotenuse = std::sqrt(std::pow(difference.x,2) + std::pow(difference.y,2));
        float angle = std::atan(difference.y/difference.x);
        int multiplier = 1;
        if(difference.x < 0)
        {
            multiplier = -1;
        }
        sf::Vector2f pointerPos;
        pointerPos.x = multiplier * 100 * std::cos(angle) + player->getSprite()->getGlobalBounds().left;
        pointerPos.y = multiplier * 100 * std::sin(angle) + player->getSprite()->getGlobalBounds().top;
        sf::RectangleShape rectangle;
        rectangle.setSize(sf::Vector2f{10,10});
        rectangle.setFillColor(sf::Color::Red);
        rectangle.setPosition(pointerPos);
        window.draw(rectangle);
    }
    else
    {
        if(player->getAttack() == true)
        {
            sf::RectangleShape rect;
            rect.setSize(sf::Vector2f{66,16});
            rect.setFillColor(sf::Color::Red);
            sf::Vector2f m = (sf::Vector2f) sf::Mouse::getPosition();
            if(m.x > 960)
            {
                rect.setPosition(player->getSprite()->getGlobalBounds().left,player->getSprite()->getGlobalBounds().top);
            }
            else
            {
                rect.setPosition(player->getSprite()->getGlobalBounds().left - 50,player->getSprite()->getGlobalBounds().top);
            }
            a.left = rect.getGlobalBounds().left;
            a.top = rect.getGlobalBounds().top;
            a.width = rect.getGlobalBounds().width;
            a.height = rect.getGlobalBounds().height;

            for(int i = 0; i < entities.size(); i++)
            {
                Entity *entity = entities.at(i);
                b.left = entity->getSprite()->getPosition().x;
                b.top = entity->getSprite()->getPosition().y;
                b.width = entity->getXSize();
                b.height = entity->getYSize();
                checkX = false;
                checkY = false;

                checkX = checkCollision(a, b);
                if(checkX)
                {
                    if(entity->getClass() == "Enemy")
                    {
                        entities.erase(entities.begin() + i);
                        continue;
                    }
                }

                if(checkY)
                {
                    if(entity->getClass() == "Enemy")
                    {
                        entities.erase(entities.begin() + i);
                        continue;
                    }
                }
            }
            window.draw(rect);
        }
    }

    for(Block block : blocks)
    {
        window.draw(*block.getSprite());
    }

    for(Entity *entity: entities)
    {
        window.draw(*entity->getSprite());
    }
    
    window.draw(*player->getSprite());

    for(auto shuriken : *shurikens)
    {
       window.draw(*shuriken->getSprite()); 
    }

    sf::View vie(sf::FloatRect(0.0f,0.0f,1920.0f,1080.0f));
    vie.setCenter(player->getSprite()->getPosition());
    window.setView(vie);
 
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
