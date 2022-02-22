#include "MainMenu.h"


MainMenu::MainMenu(sf::RenderWindow &window, sf::Font *font) {

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
    btnBackground.setPosition(static_cast<float>(window.getSize().x) / 5, 0.f);
    btnBackground.setFillColor(sf::Color(10, 10, 10, 220));

    //Buttons
    buttons["GAME_STATE"] = new GUI::Button(400, 100,
                                                  200, 200,
                                                  font, "New Game", 25,
                                                  sf::Color(200, 200,200,200), sf::Color(255, 255, 255,255), sf::Color(20, 20, 20,50),
                                                  sf::Color(70, 70, 70, 0), sf::Color(150, 150, 150, 0), sf::Color(20, 20, 20,0));

    buttons["SETTINGS_STATE"] = new GUI::Button(400, 400,
                                                      200, 200,
                                                      font, "Settings", 25,
                                                      sf::Color(200, 200,200,200), sf::Color(255, 255, 255,255), sf::Color(20, 20, 20,50),
                                                      sf::Color(70, 70,70,0), sf::Color(150, 150, 150,0), sf::Color(20, 20, 20,0));

    buttons["EXIT_STATE"] = new GUI::Button(400, 700,  200, 200,
                                                  font, "Quit", 25,
                                                  sf::Color(200, 200,200,200), sf::Color(255, 255, 255,255), sf::Color(20, 20, 20,50),
                                                  sf::Color(100, 100,100,0), sf::Color(150, 150, 150,0), sf::Color(20, 20, 20,0));



}
MainMenu::~MainMenu() {
    auto it = buttons.begin();
    for(it = buttons.begin(); it != buttons.end(); ++it){
        delete it->second;
    }
}

void MainMenu::Update(const sf::Vector2i& mousePosWindow, GAME_STATE *gameState, bool *isRunning) {
/*Updates all the buttons in the state and handles their functionality.*/

    for(auto &it : buttons){
        it.second->update(mousePosWindow);
    }

    //New game
    if(buttons["GAME_STATE"]->isPressed()) {
        *gameState = GAME_STATE::CHARACTER_SELECT;
    }

    //Setting

    //Quit the game
    if(buttons["EXIT_STATE"]->isPressed()){
        *isRunning = false;
    }
}

void MainMenu::Draw(sf::RenderWindow &window) {
    window.draw(background);

    window.draw(btnBackground);

    for(auto &it : buttons){
        it.second->render(window);
    }
}

