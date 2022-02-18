//
// Created by Antonio on 24/11/2021.
//

#ifndef MAIN_CPP_SHOP_H
#define MAIN_CPP_SHOP_H


#include "../GUI/GUI.h"

class Shop {
private:
    sf::Texture texture;
    sf::RectangleShape container0;
    sf::RectangleShape container1;
    sf::RectangleShape container2;
    std::map<std::string, GUI::Slot*> slot0;
    std::map<std::string, GUI::Slot*> slot1;
    std::map<std::string, GUI::Slot*> slot2;
    sf::Sprite sprite;
    sf::Texture texture1;

public:
    Shop(sf::RenderWindow &window);

    void addButtons(const std::string& key, float x, float y, const sf::Texture& texture);

    void Update(const sf::Vector2i& mousePosWindow);
    void Draw(sf::RenderWindow &window);
};

#endif //MAIN_CPP_SHOP_H
