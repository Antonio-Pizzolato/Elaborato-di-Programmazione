//
// Created by Antonio on 18/02/2022.
//

#ifndef MAIN_CPP_PLAYERGUI_H
#define MAIN_CPP_PLAYERGUI_H


#include "GUI.h"
#include "../Entities/Player.h"


class PlayerGUI {
private:
    Player* m_player;

    sf::Font m_font;

    //Level Bar
    std::string levelBarString;
    sf::Text levelBarText;
    sf::RectangleShape levelBarBack;

    //EXP Bar
    GUI::ProgressBar* expBar;

    //HP Bar
    GUI::ProgressBar* hpBar;




public:
    PlayerGUI(Player *player, sf::RenderWindow &window, const sf::Font& font);
    virtual ~PlayerGUI();

    //Accessor


    //Functions
    void updateLevelBar();
    void updateExpBar();
    void updateHpBar();
    void update();

    void renderLevelBar(sf::RenderWindow &window);
    void renderExpBar(sf::RenderWindow &window);
    void renderHpBar(sf::RenderWindow &window);
    void render(sf::RenderWindow &window);

};



#endif //MAIN_CPP_PLAYERGUI_H
