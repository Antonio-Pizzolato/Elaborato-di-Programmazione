//
// Created by Antonio on 18/02/2022.
//

#ifndef MAIN_CPP_MAINMENU_H
#define MAIN_CPP_MAINMENU_H


#include "../Systems/CharacterSelection.h"

class MainMenu {
private:

    sf::Texture backgroundTexture;
    sf::RectangleShape background;

    sf::RectangleShape btnBackground;
    std::map<std::string, GUI::Button*> buttons;
public:
    MainMenu(sf::RenderWindow &window, sf::Font *font);
    ~MainMenu();


    void Update(const sf::Vector2i& mousePosWindow, GAME_STATE *gameState, bool *isRunning);
    void Draw(sf::RenderWindow &window);

};

#endif //MAIN_CPP_MAINMENU_H
