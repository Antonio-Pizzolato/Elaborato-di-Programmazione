#include "PlayerGUI.h"

PlayerGUI::PlayerGUI(Player *_player, sf::RenderWindow &window, const sf::Font &_font)
        : font(_font) {
    player = _player;
    float width = GUI::p2pX(1.6f, window);
    float height = GUI::p2pY(2.8f, window);
    float x = GUI::p2pX(1.f, window);
    float y = GUI::p2pY(1.9f, window);
    levelBarBack.setSize(sf::Vector2f(width, height));
    levelBarBack.setFillColor(sf::Color(50, 50, 50, 200));
    levelBarBack.setPosition(x, y);
    levelBarText.setFont(font);
    levelBarText.setCharacterSize(25);
    levelBarText.setPosition(levelBarBack.getPosition().x + GUI::p2pX(0.60f, window),levelBarBack.getPosition().y + GUI::p2pY(0.10f, window));
    expBar = new GUI::ProgressBar(1.f, 5.6f, 10.4f, 2.2f,sf::Color::Blue, 220,window, &font);
    hpBar = new GUI::ProgressBar(1.f, 8.3f, 10.4f, 2.8f,sf::Color::Red, 180,window, &font);
}

PlayerGUI::~PlayerGUI() {
    delete hpBar;
    delete expBar;
}

//Functions
void PlayerGUI::update() {
    levelBarString = std::to_string(player->getAttributeComponent()->level);
    levelBarText.setString(levelBarString);
    expBar->update(player->getAttributeComponent()->exp, player->getAttributeComponent()->expNext);
    hpBar->update(player->getAttributeComponent()->hp, player->getAttributeComponent()->hpMax);
}

void PlayerGUI::render(sf::RenderWindow &window) {
    window.draw(levelBarBack);
    window.draw(levelBarText);
    expBar->render(window);
    hpBar->render(window);
}