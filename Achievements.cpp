//
// Created by Antonio on 18/02/2022.
//

#include "Achievements.h"

Achievements::Achievements(Observable* conditionAchievement) : conditionAchievement(conditionAchievement),
                                                               killNumber(0), gold(0), lifetime(200), kill(false), golda(false)
{
    conditionAchievement->addObserver(this);
    //animation
    setAnimation();

    text.setPosition(0, 600);

}

void Achievements::update(float _killNumber, float _gold) {

    killNumber = _killNumber;
    gold = _gold;
    if (killNumber == 3) {

        unlockAchievement(Event::Kill);

    }

    if (gold >= 15) {

        unlockAchievement(Event::Die);


    }

}


void Achievements::setAnimation() {


    //font
    if (!font.loadFromFile("Fonts/Minecraft.ttf"))
        std::cout << "ERROR::ACHIEVEMENTS::CAN'T LOAD THE FONT";
    text = sf::Text(" 7000000", font, 30);

}

void Achievements::render(sf::RenderWindow &window) {

    window.draw(text);
}

void Achievements::update(float dt)
{
    if (lifetime > 0.f)
    {
        //Update the lifetime
        lifetime -= 100.f * dt;
    }

    if (isExpired())
    {
        text.setString(" ");
        lifetime = 200.f;
    }
}

Achievements::~Achievements() {

    conditionAchievement->removeObserver(this);
}

void Achievements::unlockAchievement(Event event) {

    switch (event) {
        case Event::Kill:{
            if(!kill){
                text.setString("Congratulation: you kill one enemy");
                kill = true;
            }
        }
            break;
        case Event::Die:{
            if(!golda){
                text.setString("gold!!!!!!");
                golda = true;
            }
        }
    }

}






