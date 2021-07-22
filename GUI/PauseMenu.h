//
// Created by 39324 on 22/07/2021.
//

#ifndef MAIN_CPP_PAUSEMENU_H
#define MAIN_CPP_PAUSEMENU_H


#include<iostream>
#include<ctime>
#include<cstdlib>
#include<vector>
#include<fstream>
#include<sstream>
#include<stack>
#include<map>

#include "../GUI.h"
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>
class PauseMenu {
private:
    sf::Font& font;
    sf::Text menuText;

    sf::RectangleShape background;
    sf::RectangleShape container;

    std::map<std::string, GUI::Button*> buttons;

    //Private functions

public:
    PauseMenu(sf::RenderWindow& window, sf::Font& font);
    virtual ~PauseMenu();

    //Accessors
    std::map<std::string, GUI::Button*>& getButtons();

    //Functions
    const bool isButtonPressed(const std::string key);
    void addButtons(const std::string key, float y, const std::string text);
    void update(const sf::Vector2i& mousePosWindow);
    void render(sf::RenderTarget& target);
};


#endif //MAIN_CPP_PAUSEMENU_H
