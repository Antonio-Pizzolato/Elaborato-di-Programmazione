//
// Created by Antonio on 22/07/2021.
//

#include "Game.h"

void Game::initVariables() {
    this->window = NULL;
    this->dt = 0.f;
    this->gridSize = 100.f;
}

void Game::initGraphicsSettings() {

    this->gfxSettings.loadFromFile("Config/graphics.ini");


}



void Game::initWindow() {

    /*Creates a SFML window.*/

    if(this->gfxSettings.fullscreen)
        this->window = new sf::RenderWindow(this->gfxSettings.resolution, this->gfxSettings.title, sf::Style::Fullscreen, this->gfxSettings.contextSettings);
    else
        this->window = new sf::RenderWindow(this->gfxSettings.resolution, this->gfxSettings.title, sf::Style::Titlebar | sf::Style::Close, this->gfxSettings.contextSettings);

    this->window->setFramerateLimit(this->gfxSettings.frameRateLimit);
    this->window->setVerticalSyncEnabled(this->gfxSettings.verticalSync);
}

void Game::initKeys() {

    std::ifstream ifs("Config/supported_keys.ini");

    if(ifs.is_open()){
        std::string key = "";
        int key_value = 0;

        while (ifs >> key >> key_value){
            this->supportedKeys[key] = key_value;
        }
    }

    ifs.close();

}


void Game::initStateData() {

    this->stateData.window = this->window;
    this->stateData.gfxSettings = &this->gfxSettings;
    this->stateData.supportedKeys = &this->supportedKeys;
    this->stateData.states = &this->states;
    this->stateData.gridSize = this->gridSize;
}

void Game::initStates() {
    this->states.push(new MainMenuState(&this->stateData));
}




//Constructors/Destructors
Game::Game() {
    this->initVariables();
    this->initGraphicsSettings();
    this->initWindow();
    this->initKeys();
    this->initStateData();
    this->initStates();

}
Game::~Game() {
    delete this->window;

    while(!this->states.empty()){
        delete this->states.top();
        this->states.pop();
    }
}

//Functions

void Game::endApplication() {
}

void Game::updateDt() {

    /* Updates the delta time with the time it takes to update and render one frame. */
    this->dt = this->dtClock.restart().asSeconds();

}

void Game::updateSFMLEvents() {
    while(this->window->pollEvent(this->sfEvent)){
        if(this->sfEvent.type == sf::Event::Closed)
            this->window->close();
    }
}

void Game::update() {
    this->updateSFMLEvents();

    if(!this->states.empty()) {

        this->states.top()->update(this->dt);

        if (this->states.top()->getQuit()) {
            this->states.top()->endState();
            delete this->states.top();
            this->states.pop();
        }
    }
    else{
        //this->endApplication();
        this->window->close();
    }
}

void Game::render() {
    this->window->clear();

    //Render items
    if(!this->states.empty())
        this->states.top()->render();


    this->window->display();
}

void Game::run() {
    while (this->window->isOpen()) {
        this->updateDt();
        this->update();
        this->render();
    }
}