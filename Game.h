//
// Created by Antonio on 22/07/2021.
//

#ifndef ELABORATO_DI_PROGRAMMAZIONE_GAME_H
#define ELABORATO_DI_PROGRAMMAZIONE_GAME_H

#include "States/MainMenuState.h"

class Game {

private:


    //Variables
    GraphicsSettings gfxSettings;
    StateData stateData;
    sf::RenderWindow *window;
    sf::Event sfEvent;

    //delta time
    sf::Clock dtClock;
    float dt;

    std::stack<State*> states;

    std::map<std::string , int> supportedKeys;

    float gridSize;

    //Initialization
    void initVariables();
    void initGraphicsSettings();
    void initWindow();
    void initKeys();
    void initStateData();
    void initStates();


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
