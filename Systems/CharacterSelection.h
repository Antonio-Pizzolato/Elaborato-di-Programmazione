//
// Created by Antonio on 18/02/2022.
//

#ifndef MAIN_CPP_CHARACTERSELECTION_H
#define MAIN_CPP_CHARACTERSELECTION_H


#include "../GUI/GUI.h"
#include "../Util.h"
#include "../Entities/Warrior.h"
#include "../Entities/Wizard.h"
#include "../Entities/Archer.h"

class CharacterSelection {
private:

    sf::Texture backgroundTexture;
    sf::RectangleShape background;

    sf::RectangleShape btnBackground;
    std::map<std::string, GUI::Button*> buttons;
    sf::Texture texture;
public:
    CharacterSelection(sf::RenderWindow &window, sf::Font *font);
    ~CharacterSelection();


    void Update(const sf::Vector2i& mousePosWindow, GAME_STATE *gameState, Player **player);
    void Draw(sf::RenderWindow &window);
};



#endif //MAIN_CPP_CHARACTERSELECTION_H
