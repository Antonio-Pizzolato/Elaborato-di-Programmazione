#ifndef MAIN_CPP_PAUSEMENU_H
#define MAIN_CPP_PAUSEMENU_H


#include "../GUI/GUI.h"
#include "../Util.h"
class PauseMenu {
private:

    sf::Font& font;
    sf::Text menuText;
    sf::RectangleShape container;
    std::map<std::string, GUI::Button*> buttons;


public:

    PauseMenu(sf::RenderWindow &window, sf::Font& font);
    virtual ~PauseMenu();

    //Functions
    void update(sf::RenderWindow &window, sf::Vector2i& mousePosWindow, GAME_STATE *gameState);
    void render(sf::RenderWindow &window);
};

#endif //MAIN_CPP_PAUSEMENU_H
