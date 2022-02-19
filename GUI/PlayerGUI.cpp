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

    this->levelBarBack.setSize(sf::Vector2f(width, height));
    this->levelBarBack.setFillColor(sf::Color(50, 50, 50, 200));
    this->levelBarBack.setPosition(x, y);

    this->levelBarText.setFont(m_font);
    this->levelBarText.setCharacterSize(25);
    this->levelBarText.setPosition(
            this->levelBarBack.getPosition().x +  GUI::p2pX(0.53f, window),
            this->levelBarBack.getPosition().y +  GUI::p2pY(0.5f, window));

    this->expBar = new GUI::ProgressBar(
            1.f, 5.6f, 10.4f, 1.9f,
            sf::Color::Blue, 220,
            window, &m_font);

    this->hpBar = new GUI::ProgressBar(
            1.f, 8.3f, 10.4f, 2.8f,
            sf::Color::Red, 180,
            window, &m_font);

}

PlayerGUI::~PlayerGUI() {

    delete this->hpBar;
    delete this->expBar;

}


//Functions
void PlayerGUI::updateLevelBar()
{
    levelBarString = std::to_string(m_player->getAttributeComponent()->level);
    levelBarText.setString(this->levelBarString);
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
    window.draw(this->levelBarBack);
    window.draw(this->levelBarText);
}

void PlayerGUI::renderExpBar(sf::RenderWindow &window)
{
    this->expBar->render(window);
}

void PlayerGUI::renderHpBar(sf::RenderWindow &window)
{
    this->hpBar->render(window);
}

void PlayerGUI::render(sf::RenderWindow &window) {
    this->renderLevelBar(window);
    this->renderExpBar(window);
    this->renderHpBar(window);

}










