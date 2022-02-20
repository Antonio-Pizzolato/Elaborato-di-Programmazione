//
// Created by Antonio on 18/02/2022.
//


#include "CharacterSelection.h"


CharacterSelection::CharacterSelection(sf::RenderWindow &window, sf::Font *font) {

    background.setSize(sf::Vector2f(static_cast<float>(window.getSize().x),
                                    static_cast<float>(window.getSize().y)));
    backgroundTexture.loadFromFile("Resources/Images/Backgrounds/bg1.jpg");
    background.setTexture(&backgroundTexture);

    btnBackground.setSize(
            sf::Vector2f(
                    static_cast<float>(window.getSize().x) / 5,
                    static_cast<float>(window.getSize().y)
            )
    );
    btnBackground.setPosition(static_cast<float>(window.getSize().x) / 2, 0.f);
    btnBackground.setFillColor(sf::Color(10, 10, 10, 220));

    //Buttons
    buttons["WARRIOR"] = new GUI::Button(1000, 100,
                                               200, 200,
                                               font, "Warrior", 25,
                                               sf::Color(200, 200,200,200), sf::Color(255, 255, 255,255), sf::Color(20, 20, 20,50),
                                               sf::Color(70, 70, 70, 0), sf::Color(150, 150, 150, 0), sf::Color(20, 20, 20,0));

    buttons["WIZARD"] = new GUI::Button(1000, 400,
                                              200, 200,
                                              font, "Wizard", 25,
                                              sf::Color(200, 200,200,200), sf::Color(255, 255, 255,255), sf::Color(20, 20, 20,50),
                                              sf::Color(70, 70,70,0), sf::Color(150, 150, 150,0), sf::Color(20, 20, 20,0));

    buttons["ARCHER"] = new GUI::Button(1000, 700,  200, 200,
                                              font, "Archer", 25,
                                              sf::Color(200, 200,200,200), sf::Color(255, 255, 255,255), sf::Color(20, 20, 20,50),
                                              sf::Color(100, 100,100,0), sf::Color(150, 150, 150,0), sf::Color(20, 20, 20,0));

    buttons["EXIT_STATE"] = new GUI::Button(1000, 900,  200, 200,
                                                  font, "Quit", 25,
                                                  sf::Color(200, 200,200,200), sf::Color(255, 255, 255,255), sf::Color(20, 20, 20,50),
                                                  sf::Color(100, 100,100,0), sf::Color(150, 150, 150,0), sf::Color(20, 20, 20,0));




}
CharacterSelection::~CharacterSelection() {
    auto it = buttons.begin();
    for(it = buttons.begin(); it != buttons.end(); ++it){
        delete it->second;
    }
}

void CharacterSelection::Update(const sf::Vector2i& mousePosWindow, GAME_STATE *gameState, Player **player) {
/*Updates all the buttons in the state and handles their functionality.*/

    for(auto &it : buttons){
        it.second->update(mousePosWindow);
    }

    //New game
    if(buttons["WARRIOR"]->isPressed()) {
        *gameState = GAME_STATE::PLAYING;
        texture.loadFromFile("Resources/Images/Sprites/Player/texture_sheet.png");

        *player = new Warrior(500, 500, texture, PLAYER_CLASS::WARRIOR);

        //playerGui = new PlayerGUI(m_player, m_window, font);
    }

    //Setting
    if(buttons["WIZARD"]->isPressed()){
        *gameState = GAME_STATE::PLAYING;
        texture.loadFromFile("Resources/Images/Sprites/Player/Wizard/Wizard.png");

        *player = new Wizard(500, 500, texture, PLAYER_CLASS::WIZARD);

        //playerGui = new PlayerGUI(m_player, m_window, font);
    }

    //Quit the game
    if(buttons["ARCHER"]->isPressed()){
        *gameState = GAME_STATE::PLAYING;
        texture.loadFromFile("Resources/Images/Sprites/Player/Archer/Archer.png");

        *player = new Archer(500, 500, texture, PLAYER_CLASS::ARCHER);

        //playerGui = new PlayerGUI(m_player, m_window, font);
    }

    //Quit the game
    if(buttons["EXIT_STATE"]->isPressed()){
        *gameState = GAME_STATE::MAIN_MENU;
    }
}

void CharacterSelection::Draw(sf::RenderWindow &window) {
    window.draw(background);

    window.draw(btnBackground);

    for(auto &it : buttons){
        it.second->render(window);
    }
}
