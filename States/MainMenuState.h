//
// Created by Antonio on 22/07/2021.
//

#ifndef ELABORATO_DI_PROGRAMMAZIONE_MAINMENUSTATE_H
#define ELABORATO_DI_PROGRAMMAZIONE_MAINMENUSTATE_H

#include "GameState.h"
#include "../GUI.h"


class MainMenuState:
        public State
{
private:
    //Variables

    sf::Texture backgroundTexture;
    sf::RectangleShape background;
    sf::Font font;

    std::map<std::string, GUI::Button*> buttons;

    //Functions
    void initVariables();
    void initBackground();
    void initFonts();
    void initKeybinds();
    void initButtons();
public:
    MainMenuState(StateData* state_data);
    virtual ~MainMenuState();

    //Functions
    void updateInput(const float &dt);
    void updateButtons();
    void update(const float &dt);
    void renderButtons(sf::RenderTarget& target);
    void render(sf::RenderTarget* target = NULL);

};


#endif //ELABORATO_DI_PROGRAMMAZIONE_MAINMENUSTATE_H
