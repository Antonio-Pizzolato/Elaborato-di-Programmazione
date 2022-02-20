//
// Created by Antonio on 24/11/2021.
//

#include "Shop.h"

Shop::Shop(sf::RenderWindow &window) {
    texture.loadFromFile("Resources/Images/Inventory/inventorySlot.png");
    container0.setSize(sf::Vector2f(static_cast<float>(window.getSize().x) / 5,
                                    static_cast<float>(window.getSize().y) / 3));
    container0.setFillColor(sf::Color(20, 20, 20, 200));
    container0.setPosition(
            static_cast<float>(window.getSize().x) / 6.f - container0.getSize().x / 7.f,
            600.f);

    container1.setSize(sf::Vector2f(static_cast<float>(window.getSize().x) / 5,
                                    static_cast<float>(window.getSize().y) / 3));
    container1.setFillColor(sf::Color(20, 20, 20, 200));
    container1.setPosition(
            static_cast<float>(window.getSize().x) / 2 - container1.getSize().x / 1.85,
            600.f);

    container2.setSize(sf::Vector2f(static_cast<float>(window.getSize().x) / 5,
                                    static_cast<float>(window.getSize().y) / 3));
    container2.setFillColor(sf::Color(20, 20, 20, 200));
    container2.setPosition(
            static_cast<float>(window.getSize().x) / 1.5 - container2.getSize().x / 8,
            600.f);


    addButtons("1",0 , 0, texture);
    addButtons("2",48 , 0, texture);            //i 3 bottoni di scelta  shop/upgrade/...
    addButtons("3",96 , 0, texture);

    /*texture2.loadFromFile("Resources/Images/Inventory/Small_Health_Potion.png");
    sprite.setTexture(texture2);                                                                //Aggiungi Texture come +dmg, +hp...
    sprite.setPosition(container.getPosition().x + 48, container.getPosition().y + 48);*/
}

void Shop::addButtons(const std::string &key, float x, float y, const sf::Texture &texture) {
    float w0 = container0.getPosition().x + x;
    float h0 = container0.getPosition().y + y;
    slot0[key] = new GUI::Slot(w0, h0, texture);

    float w1 = container1.getPosition().x + x;
    float h1 = container1.getPosition().y + y;
    slot1[key] = new GUI::Slot(w1, h1, texture);

    float w2 = container2.getPosition().x + x;
    float h2 = container2.getPosition().y + y;
    slot2[key] = new GUI::Slot(w2, h2, texture);
}

void Shop::Update(const sf::Vector2i &mousePosWindow) {
    for(auto &i : slot0){
        i.second->update(mousePosWindow);
    }
    for(auto &i : slot1){
        i.second->update(mousePosWindow);
    }
    for(auto &i : slot2){
        i.second->update(mousePosWindow);
    }
}

void Shop::Draw(sf::RenderWindow &window) {
    window.draw(container0);
    window.draw(container1);
    window.draw(container2);


    for(auto &i : slot0){
        i.second->render(window);
    }
    for(auto &i : slot1){
        i.second->render(window);
    }
    for(auto &i : slot2){
        i.second->render(window);
    }

    window.draw(sprite);
}
