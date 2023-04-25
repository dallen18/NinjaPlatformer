#include "headers/Game.hpp"
#include "headers/Hud.hpp"
#include "headers/tinyxml2.h"
#include <SFML/Graphics/Rect.hpp>
#include <SFML/System/Vector2.hpp>
#include <SFML/Window/Keyboard.hpp>
#include <SFML/Window/Mouse.hpp>
#include <fstream>
#include <string>
#include <thread>

Game::Game()
{
    //Come back
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
    window.create(sf::VideoMode(1920, 1080), "Ninja Platformer");

    //syncs frames with refresh rate of monitor
    window.setVerticalSyncEnabled(true);
    
    //key presses cannot repeat so holding down keys isn't possible
    window.setKeyRepeatEnabled(false);
}

//loads textures
void Game::loadTextures()
{
    //load player textures
    sf::Texture playerIdleTexture;
    sf::Texture playerLeftRunTexture;
    sf::Texture playerJumpTexture;
    sf::Texture playerRunTexture;

    if(!playerIdleTexture.loadFromFile("/Users/deontaeallen/MostRecent/NinjaPlatformer/resources/Images/Player/idle.png")) //takes texture from resources folder
    {
        std::cout << "failed to load image.";
    }

    if(!playerRunTexture.loadFromFile("/Users/deontaeallen/MostRecent/NinjaPlatformer/resources/Images/Player/run_2.png")) //takes texture from resources folder
    {
        std::cout << "failed to load image.";
    }

    if(!playerLeftRunTexture.loadFromFile("/Users/deontaeallen/MostRecent/NinjaPlatformer/resources/Images/Player/left_run_1.png")) //takes texture from resources folder
    {
        std::cout << "failed to load image.";
    }

     if(!playerJumpTexture.loadFromFile("/Users/deontaeallen/MostRecent/NinjaPlatformer/resources/Images/Player/jump_1.png")) //takes texture from resources folder
    {
        std::cout << "failed to load image.";
    }











    sf::Texture heartTexture;

    if(!heartTexture.loadFromFile("/Users/deontaeallen/MostRecent/NinjaPlatformer/resources/Images/heart-icon.png")) //takes texture from resources folder
    {
        std::cout << "failed to load image.";
    }

    //load enemy textures
    sf::Texture EnemyBugIdle;

    if(!EnemyBugIdle.loadFromFile("/Users/deontaeallen/MostRecent/NinjaPlatformer/resources/Images/Enemies/bug/fly.png")) //takes texture from resources folder
    {
        std::cout << "failed to load image.";
    }

    //load block textures
    sf::Texture blockTexture;

    if(!blockTexture.loadFromFile("/Users/deontaeallen/MostRecent/NinjaPlatformer/resources/Images/cavesofgallet.png")) //takes texture from resources folder
    {
        std::cout << "failed to load image.";
    }
    
    //inserts textures into map
    textures["PlayerIdle"] = playerIdleTexture;
    textures["PlayerLeftRun"] = playerLeftRunTexture;
    textures["PlayerJump"] = playerJumpTexture;
    textures["PlayerRun"] = playerRunTexture;
    textures["Heart"] = heartTexture;
    textures["Enemy"] = EnemyBugIdle;
    textures["Block"] = blockTexture;

    //loads font
    if(!font.loadFromFile("/Users/deontaeallen/MostRecent/NinjaPlatformer/resources/Fonts/Roboto-Black.ttf")) 
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
            }
        }

        input->checkPlayerInput();
        auto pressed = input->getPressed();

        if(player != NULL)
        {
            // if((*pressed)["Right"]) //right
            // {
            //     player->setRight(true);
            // }

            // if((*pressed)["Left"])
            // {
            //     player->setLeft(true);
            // }
            
            // if((*pressed)["Jump"])
            // {
            //     player->setJumping(true);
            // }

            auto rect = player->getSprite()->getTextureRect();

            if (event.type == sf::Event::KeyReleased) {
                auto keyCode = event.key.code;
                if (keyCode == sf::Keyboard::D || keyCode == sf::Keyboard::A || keyCode == sf::Keyboard::W  || keyCode == sf::Keyboard::Space) {
                player->getSprite()->setTextureRect(
                    sf::IntRect(0, 0, rect.width, rect.height));
                    }
                } else{

                }

            if(sf::Keyboard::isKeyPressed(sf::Keyboard::D))
                {
                    player->setRight(true);
                }

            

            if(sf::Keyboard::isKeyPressed(sf::Keyboard::A))
                {
                    player->setLeft(true); 
                }

            if(sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
                {
                    player->setJumping(true);
                }
 

        if (player->getRight() || player->getLeft()) {
            auto posX = player->getSprite()->getPosition().x;
            auto textureIndex = static_cast<int>(posX) / 50 % 8;
            textureIndex *= rect.width;

            if (player->getRight()) {
            player->getSprite()->setTexture(textures["PlayerRun"]);
            }

            if (player->getLeft()) {
            player->getSprite()->setTexture(textures["PlayerLeftRun"]);
            }

            if (player->getJumping()) {
            player->getSprite()->setTexture(textures["PlayerJump"]);
            }

            player->getSprite()->setTextureRect(
                sf::IntRect(textureIndex, 0, rect.width, rect.height));
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
                    setLevel("/Users/deontaeallen/MostRecent/NinjaPlatformer/resources/Levels/NinjaLevelOne.tmx");
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

    Hud hud(player, &textures["Heart"]);
    hud.draw(&window);

    pause.draw(&window);

    if(input->checkOtherInput(sf::Mouse::Left, 1))
    {
        std::string id = mouseCollision();
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
        player = new Player(&textures["PlayerIdle"], 6.0f, 12.0f, 1.0f, 24, 31);  //instantiates player. passes player textures, max x-axis speed, max y-axis speed, and acceleration rate
    }
   
    player->setHealth(5);

    //get info from xml files
    
    tinyxml2::XMLDocument level;
    level.LoadFile(filename.c_str());

    // the source image isn't taken as of now from the .tsx file but will be in the future if we add more tile sets
    
    std::string source = "/Users/deontaeallen/MostRecent/NinjaPlatformer/resources/Levels/cavesofgallet.tsx";
    //source += level.RootElement()->FirstChild()->ToElement()->Attribute("source");
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
    playerSprite->setPosition(std::stoi(element->ToElement()->Attribute("x")),std::stoi(element->ToElement()->Attribute("y")));

    element = level.RootElement()->FirstChildElement("objectgroup")->NextSibling()->FirstChild();
    while(element != NULL)
    {
        Enemy *enemy = new Enemy(&textures["EnemyBugIdle"],3.0f,4.0f,1.0f,23,29);
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
            //line.push_back(std::stol(num));
            val = std::stoll(num);
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
    //sf::Vector2f mousePos = (sf::Vector2f)sf::Mouse::getPosition();
    sf::Vector2f mousePos = window.getView().getCenter() - window.getView().getSize() / 2.0f + (sf::Vector2f)sf::Mouse::getPosition();
    mousePos.y -= 2022;

    sf::RectangleShape r(sf::Vector2f(1,1));

    r.setPosition(mousePos);

   std::cout << mousePos.x  << "," << mousePos.y << "\n";

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
