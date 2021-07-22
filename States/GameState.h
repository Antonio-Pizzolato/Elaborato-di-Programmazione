//
// Created by Antonio on 22/07/2021.
//

#ifndef ELABORATO_DI_PROGRAMMAZIONE_GAMESTATE_H
#define ELABORATO_DI_PROGRAMMAZIONE_GAMESTATE_H


#include "State.h"

class GameState :
        public State
{
private:
    sf::View view;
    sf::RenderTexture renderTexture;
    sf::Sprite renderSprite;

    sf::Font font;
    sf::Texture texture;


    //Functions
    void initView();
    void initKeybinds();
    void initFonts();
    void initTextures();
    void initPauseMenu();
    void initPlayers();
    void initTileMap();

public:
    GameState(StateData* state_data);
    virtual ~GameState();

    //Functions
    void updateView(const float& dt);
    void updateInput(const float& dt);
    void updatePlayerInput(const float &dt);
    void updatePauseMenuButtons();
    void update(const float &dt);
    void render(sf::RenderTarget* target = NULL);
};


#endif //ELABORATO_DI_PROGRAMMAZIONE_GAMESTATE_H
