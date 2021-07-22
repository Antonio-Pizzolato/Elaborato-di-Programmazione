//
// Created by Antonio on 22/07/2021.
//

#include "GameState.h"

void GameState::initView() {

    this->view.setSize(sf::Vector2f(this->stateData->gfxSettings->resolution.width,
                                    this->stateData->gfxSettings->resolution.height));
    this->view.setCenter(sf::Vector2f(this->stateData->gfxSettings->resolution.width / 2.f,
                                      this->stateData->gfxSettings->resolution.height / 2.f));

}

void GameState::initKeybinds() {


    std::ifstream ifs("Config/gamestate_keybinds.ini");

    if(ifs.is_open()){
        std::string key = "";
        std::string key2 = "";

        while (ifs >> key >> key2){
            this->keybinds[key] = this->supportedKeys->at(key2);
        }
    }

    ifs.close();

}

void GameState::initFonts() {
    if(!this->font.loadFromFile("Fonts/Dosis-Light.ttf")){
        throw("ERROR::MAIN_MENU_STATE::COULD NOT LOAD FONT");
    }
}

GameState::GameState(StateData* state_data)
        : State(state_data)
{
    this->initView();
    this->initKeybinds();
    this->initFonts();
}

GameState::~GameState()  {

}


//Functions

void GameState::updateInput(const float &dt) {
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keybinds.at("CLOSE"))) && this->getKeyTime())
        if(!this->paused){
            this->pauseState();
        }
        else{
            this->unpauseState();
        }
}


void GameState::update(const float &dt) {

    this->updateMousePositions(&this->view);
    this->updateKeyTime(dt);
    this->updateInput(dt);

}

void GameState::render(sf::RenderTarget* target) {

    if(!target)
        target = this->window;

    target->setView(this->view);

    if(this->paused){ //Pause menu render
        target->setView(this->window->getDefaultView());
    }

}