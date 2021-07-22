//
// Created by Antonio on 22/07/2021.
//

#ifndef ELABORATO_DI_PROGRAMMAZIONE_GAME_H
#define ELABORATO_DI_PROGRAMMAZIONE_GAME_H

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include <SFML/Audio.hpp>
#include "GraphicSettings.h"

#include <iostream>
#include <ctime>
#include <cstdlib>
#include <sstream>
#include <vector>

class Game {

private:


    //Variables
    GraphicsSettings gfxSettings;
    sf::RenderWindow *window;
    sf::Event sfEvent;

    //delta time
    sf::Clock dtClock;
    float dt;


    std::map<std::string , int> supportedKeys;

    float gridSize;

    //Initialization
    void initVariables();
    void initGraphicsSettings();
    void initWindow();
    void initKeys();


public:
    //Constructors/Destructors
    Game();
    virtual ~Game();

    //Functions
    void endApplication();
    //Update
    void updateDt();
    void updateSFMLEvents();
    void update();

    //Render
    void render();

    //Core
    void run();
};


#endif //ELABORATO_DI_PROGRAMMAZIONE_GAME_H
