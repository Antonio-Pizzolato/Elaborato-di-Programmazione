//
// Created by Antonio on 18/02/2022.
//

#ifndef MAIN_CPP_ACHIEVEMENTS_H
#define MAIN_CPP_ACHIEVEMENTS_H


#include "ConditionAchievement.h"
#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>



using namespace std;

class Achievements : public Observer{
public:
    //Constructor & Destructor
    Achievements(Observable* conditionAchievement);
    ~Achievements() override;
    //Update Treasure
    void update(float _killNumber, float _gold);
    //Animation
    void setAnimation();
    void render(sf::RenderWindow &window);

    void update(float dt);


private:

    Observable* conditionAchievement;
    float killNumber;
    float gold;

    sf::Text text;
    sf::Font font;
    float lifetime;
    bool kill;
    bool golda;
    inline bool isExpired() const{ return lifetime <= 0.f; }

    void unlockAchievement(Event event);



};


#endif //MAIN_CPP_ACHIEVEMENTS_H
