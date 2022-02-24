#include "PauseMenu.h"


PauseMenu::PauseMenu(sf::RenderWindow &window, sf::Font &font)
        : font(font) {
    //Init container
    container.setSize(sf::Vector2f(500, window.getSize().y));
    container.setFillColor(sf::Color(20, 20, 20, 200));
    container.setPosition(window.getSize().x / 2 - container.getSize().x / 2,20);
    //Init text
    menuText.setFont(font);
    menuText.setFillColor(sf::Color(255, 255, 255, 200));
    menuText.setCharacterSize(25);
    menuText.setString("PAUSED");
    menuText.setPosition(container.getPosition().x + container.getSize().x / 2.f - menuText.getGlobalBounds().width / 2.f,container.getPosition().y + 5);
    buttons["GAME_STATE"] = new GUI::Button(menuText.getPosition().x - 100, 900,200, 200,&font, "Exit", 25,sf::Color(200, 200, 200, 200), sf::Color(255, 255, 255, 255),sf::Color(20, 20, 20, 50),sf::Color(70, 70, 70, 0), sf::Color(150, 150, 150, 0),sf::Color(20, 20, 20, 0));
}

PauseMenu::~PauseMenu() {
    auto it = buttons.begin();
    for (it = buttons.begin(); it != buttons.end(); ++it) {
        delete it->second;
    }
}

//Functions
void PauseMenu::update(sf::RenderWindow &window, sf::Vector2i &mousePosWindow, GAME_STATE *gameState) {
    for (auto &i: buttons) {
        i.second->update(mousePosWindow);
    }
    if (buttons["GAME_STATE"]->isPressed()) {
        *gameState = GAME_STATE::MAIN_MENU;
    }
}

void PauseMenu::render(sf::RenderWindow &window) {
    window.draw(container);
    for (auto &i: buttons) {
        i.second->render(window);
    }
    window.draw(menuText);
}