
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

void GameState::initTextures() {
    if(!this->textures["PLAYER_SHEET"].loadFromFile("Resources/Images/Sprites/Player/texture_sheet.png")){
        throw "ERROR::GAME_STATE::COULD_NOT_LOAD_PLAYER_TEXTURE";
    }
}

void GameState::initPauseMenu() {
    this->pmenu = new PauseMenu(*this->window, this->font);

    this->pmenu->addButtons("QUIT", 600.f, "Quit");
}


void GameState::initPlayers() {
    this->player = new Player(500, 500, this->textures["PLAYER_SHEET"]);
}


void GameState::initTileMap() {
}

GameState::GameState(StateData* state_data)
        : State(state_data)
{
    this->initView();
    this->initKeybinds();
    this->initFonts();
    this->initTextures();
    this->initPauseMenu();
    this->initPlayers();
    this->initTileMap();
}

GameState::~GameState()  {
    delete this->pmenu;
    delete this->player;

}


//Functions

void GameState::updateView(const float &dt) {

    this->view.setCenter(this->player->getPosition());
}

void GameState::updateInput(const float &dt) {
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keybinds.at("CLOSE"))) && this->getKeyTime())
        if(!this->paused){
            this->pauseState();
        }
        else{
            this->unpauseState();
        }
}

void GameState::updatePlayerInput(const float &dt) {


    //Update player input
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keybinds.at("MOVE_LEFT"))))
        this->player->move(-1.f, 0.f, dt);
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keybinds.at("MOVE_RIGHT"))))
        this->player->move(1.f, 0.f, dt);
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keybinds.at("MOVE_UP"))))
        this->player->move(0.f, -1.f, dt);
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keybinds.at("MOVE_DOWN"))))
        this->player->move(0.f, 1.f, dt);


}


void GameState::updatePauseMenuButtons() {
    if(this->pmenu->isButtonPressed("QUIT"))
        this->endState();
}


void GameState::update(const float &dt) {

    this->updateMousePositions(&this->view);
    this->updateKeyTime(dt);
    this->updateInput(dt);


    if(!this->paused){ //Unpaused update

        this->updateView(dt);
        this->updatePlayerInput(dt);
        this->player->update(dt);
    }
    else{ //Paused update

        this->pmenu->update(this->mousePosWindow);
        this->updatePauseMenuButtons();
    }
}

void GameState::render(sf::RenderTarget* target) {

    if(!target)
        target = this->window;

    target->setView(this->view);

    this->player->render(*target);

    if(this->paused){ //Pause menu render
        target->setView(this->window->getDefaultView());
        this->pmenu->render(*target);
    }

}
















