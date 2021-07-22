//
// Created by Antonio on 22/07/2021.
//

#include "MainMenuState.h"

void MainMenuState::initVariables() {

}

void MainMenuState::initBackground() {

    this->background.setSize
            (sf::Vector2f
                     (
                             static_cast<float>(this->window->getSize().x),
                             static_cast<float>(this->window->getSize().y)
                     )
            );

    if(!this->backgroundTexture.loadFromFile("Resources/Images/Backgrounds/bg1.jpg")){
        throw "ERROR::MAIN_MENU_STATE::FAILED_TO_LOAD_BACKGROUND_TEXTURE";
    }

    this->background.setTexture(&this->backgroundTexture);
}


void MainMenuState::initFonts() {
    if(!this->font.loadFromFile("Fonts/Dosis-Light.ttf")){
        throw("ERROR::MAIN_MENU_STATE::COULD NOT LOAD FONT");
    }
}

void MainMenuState::initKeybinds() {


    std::ifstream ifs("Config/mainmenustate_keybinds.ini");

    if(ifs.is_open()){
        std::string key = "";
        std::string key2 = "";

        while (ifs >> key >> key2){
            this->keybinds[key] = this->supportedKeys->at(key2);
        }
    }

    ifs.close();

}

void MainMenuState::initButtons() {

    this->buttons["GAME_STATE"] = new GUI::Button(300.f, 480.f, 250.f, 65.f,
                                                  &this->font, "New Game", 50,
                                                  sf::Color(70, 70,70,200), sf::Color(250, 250, 250,250), sf::Color(20, 20, 20,50),
                                                  sf::Color(70, 70, 70, 0), sf::Color(150, 150, 150, 0), sf::Color(20, 20, 20,0));

    this->buttons["SETTINGS_STATE"] = new GUI::Button(300.f, 580.f, 250.f, 65.f,
                                                      &this->font, "Settings",50,
                                                      sf::Color(70, 70,70,200), sf::Color(250, 250, 250,250), sf::Color(20, 20, 20,50),
                                                      sf::Color(70, 70,70,0), sf::Color(150, 150, 150,0), sf::Color(20, 20, 20,0));

    this->buttons["EDITOR_STATE"] = new GUI::Button(300.f, 680.f, 250.f, 65.f,
                                                    &this->font, "Editor",50,
                                                    sf::Color(70, 70,70,200), sf::Color(250, 250, 250,250), sf::Color(20, 20, 20,50),
                                                    sf::Color(70, 70,70,0), sf::Color(150, 150, 150,0), sf::Color(20, 20, 20,0));

    this->buttons["EXIT_STATE"] = new GUI::Button(300.f, 780.f, 250.f, 65.f,
                                                  &this->font, "Quit",50,
                                                  sf::Color(70, 70,70,200), sf::Color(250, 250, 250,250), sf::Color(20, 20, 20,50),
                                                  sf::Color(70, 70,70,0), sf::Color(150, 150, 150,0), sf::Color(20, 20, 20,0));
}

MainMenuState::MainMenuState(StateData* state_data)
        : State(state_data){

    this->initVariables();
    this->initBackground();
    this->initFonts();
    this->initKeybinds();
    this->initButtons();

}




MainMenuState::~MainMenuState() {
    auto it = this->buttons.begin();
    for(it = this->buttons.begin(); it != this->buttons.end(); ++it){
        delete it->second;
    }
}


//Functions
void MainMenuState::updateInput(const float &dt) {



}

void MainMenuState::updateButtons() {

    /*Updates all the buttons in the state and handles their functionality.*/
    for(auto &it : this->buttons){
        it.second->update(this->mousePosWindow);
    }

    //New game
    if(this->buttons["GAME_STATE"]->isPressed()){
        this->states->push(new GameState(this->stateData));
    }

    //Quit the game
    if(this->buttons["EXIT_STATE"]->isPressed()){
        this->endState();
    }
}

void MainMenuState::update(const float &dt) {

    this->updateMousePositions();
    this->updateInput(dt);
    this->updateButtons();


}

void MainMenuState::renderButtons(sf::RenderTarget& target) {

    for(auto &it : this->buttons){
        it.second->render(target);
    }
}

void MainMenuState::render(sf::RenderTarget* target) {

    if(!target)
        target = this->window;

    target->draw(this->background);

    this->renderButtons(*target);
}