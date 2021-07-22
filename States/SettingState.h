//
// Created by 39324 on 22/07/2021.
//

#ifndef MAIN_CPP_SETTINGSTATE_H
#define MAIN_CPP_SETTINGSTATE_H
#include "State.h"
#include "../GUI.h"

class SettingState :
        public State
{
private:
    //Variables
    sf::Texture backgroundTexture;
    sf::RectangleShape background;
    sf::Font font;

    std::map<std::string, GUI::Button*> buttons;
    std::map<std::string, GUI::DropDownList*> dropDownLists;

    sf::Text optionsText;

    std::vector<sf::VideoMode> modes;

    //Functions
    void initVariables();
    void initBackground();
    void initFonts();
    void initKeybinds();
    void initGUI();
    void initText();
public:
    SettingState(StateData* state_data);
    virtual ~SettingState();


    //Accessors

    //Functions
    void updateInput(const float &dt);
    void updateGUI(const float &dt);
    void update(const float& dt);
    void renderGUI(sf::RenderTarget& target);
    void render(sf::RenderTarget* target = NULL);
};



#endif //MAIN_CPP_SETTINGSTATE_H
