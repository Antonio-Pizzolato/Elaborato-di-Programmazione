//
// Created by Antonio on 18/02/2022.
//
#include "PlayerGUI.h"

PlayerGUI::PlayerGUI(Player* player, sf::RenderWindow &window, const sf::Font& font)
        : m_font(font)
{

    m_player = player;

    float width = GUI::p2pX(1.6f, window);
    float height =  GUI::p2pY(2.8f, window);
    float x =  GUI::p2pX(1.f, window);
    float y =  GUI::p2pY(1.9f, window);

    levelBarBack.setSize(sf::Vector2f(width, height));
    levelBarBack.setFillColor(sf::Color(50, 50, 50, 200));
    levelBarBack.setPosition(x, y);

    levelBarText.setFont(m_font);
    levelBarText.setCharacterSize(25);
    levelBarText.setPosition(
            levelBarBack.getPosition().x +  GUI::p2pX(0.53f, window),
            levelBarBack.getPosition().y +  GUI::p2pY(0.5f, window));

    expBar = new GUI::ProgressBar(
            1.f, 5.6f, 10.4f, 1.9f,
            sf::Color::Blue, 220,
            window, &m_font);

    hpBar = new GUI::ProgressBar(
            1.f, 8.3f, 10.4f, 2.8f,
            sf::Color::Red, 180,
            window, &m_font);

}

PlayerGUI::~PlayerGUI() {

    delete hpBar;
    delete expBar;

}


//Functions
void PlayerGUI::updateLevelBar()
{
    levelBarString = std::to_string(m_player->getAttributeComponent()->level);
    levelBarText.setString(levelBarString);
}
void PlayerGUI::updateExpBar()
{
    expBar->update(m_player->getAttributeComponent()->exp, m_player->getAttributeComponent()->expNext);
}
void PlayerGUI::updateHpBar()
{
    hpBar->update(m_player->getAttributeComponent()->hp, m_player->getAttributeComponent()->hpMax);
}



void PlayerGUI::update() {

    updateLevelBar();
    updateExpBar();
    updateHpBar();

}


void PlayerGUI::renderLevelBar(sf::RenderWindow &window)
{
    window.draw(levelBarBack);
    window.draw(levelBarText);
}

void PlayerGUI::renderExpBar(sf::RenderWindow &window)
{
    expBar->render(window);
}

void PlayerGUI::renderHpBar(sf::RenderWindow &window)
{
    hpBar->render(window);
}

void PlayerGUI::render(sf::RenderWindow &window) {
    renderLevelBar(window);
    renderExpBar(window);
    renderHpBar(window);

}











