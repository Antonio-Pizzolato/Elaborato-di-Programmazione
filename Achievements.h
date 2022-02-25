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

class Achievements : public Observer {
public:
    //Constructor & Destructor
    explicit Achievements(Observable *conditionAchievement);
    ~Achievements() override;

    //Update Treasure
    bool getKill() const {return kill;}
    void update(float _killNumber, float _gold) override;
    //Animation
    void render(sf::RenderWindow &window);
    void updateLifetime(float dt);
private:
    Observable *conditionAchievement;
    float killNumber;
    float gold;
    float lifetime;
    sf::Texture texture;
    sf::Sprite sprite;
    bool kill;
    bool golda;
    bool CanDraw;
    inline bool isExpired() const { return lifetime <= 0.f; }
    void unlockAchievement(Event event);
};


#endif //MAIN_CPP_ACHIEVEMENTS_H
