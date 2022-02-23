#ifndef MAIN_CPP_PLAYERGUI_H
#define MAIN_CPP_PLAYERGUI_H


#include "GUI.h"
#include "../Entities/Player.h"


class PlayerGUI {
private:
    Player* player;

    sf::Font font;

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
    //Functions
    void update();
    void render(sf::RenderWindow &window);

};



#endif //MAIN_CPP_PLAYERGUI_H
