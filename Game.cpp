//
// Created by Antonio on 22/07/2021.
//

#include "Game.h"

//Initialization function
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




//Constructors/Destructors
Game::Game() {
    this->initVariables();
    this->initGraphicsSettings();
    this->initWindow();
    this->initKeys();

}
Game::~Game() {
    delete this->window;

}

//Functions
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

}

void Game::render() {
    this->window->clear();
    this->window->display();
}

void Game::run() {
    while (this->window->isOpen()) {
        this->updateDt();
        this->update();
        this->render();
    }
}