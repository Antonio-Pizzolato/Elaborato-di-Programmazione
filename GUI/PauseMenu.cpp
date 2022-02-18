#include "PauseMenu.h"


PauseMenu::PauseMenu(sf::RenderWindow &window, sf::Font& font)
        : font(font)
{

    //Init container
    container.setSize(sf::Vector2f(
            500,
            window.getSize().y)
    );
    container.setFillColor(sf::Color(20, 20, 20, 200));
    container.setPosition(
            window.getSize().x / 2 - container.getSize().x / 2,
            20);

    //Init text
    this->menuText.setFont(font);
    this->menuText.setFillColor(sf::Color(255, 255, 255, 200));
    this->menuText.setCharacterSize(25);
    this->menuText.setString("PAUSED");
    this->menuText.setPosition(this->container.getPosition().x + this->container.getSize().x / 2.f - this->menuText.getGlobalBounds().width / 2.f,
                               this->container.getPosition().y + 5);

    this->buttons["GAME_STATE"] = new GUI::Button(menuText.getPosition().x - 100, 900,
                                                  200, 200,
                                                  &font, "Exit", 25,
                                                  sf::Color(200, 200,200,200), sf::Color(255, 255, 255,255), sf::Color(20, 20, 20,50),
                                                  sf::Color(70, 70, 70, 0), sf::Color(150, 150, 150, 0), sf::Color(20, 20, 20,0));


}

PauseMenu::~PauseMenu() {

    auto it = this->buttons.begin();
    for(it = this->buttons.begin(); it != this->buttons.end(); ++it){
        delete it->second;
    }
}

//Accessors


//Functions


void PauseMenu::update(sf::RenderWindow &window, sf::Vector2i& mousePosWindow, GAME_STATE *gameState) {

    for(auto &i : this->buttons){
        i.second->update(mousePosWindow);

    }

    if(this->buttons["GAME_STATE"]->isPressed()) {

        *gameState = GAME_STATE::MAIN_MENU;
    }
}

void PauseMenu::render(sf::RenderWindow &window) {

    window.draw(this->container);

    for(auto &i : this->buttons){
        i.second->render(window);
    }
    window.draw(this->menuText);
}





