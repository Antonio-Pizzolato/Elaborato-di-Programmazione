//
// Created by Antonio on 18/02/2022.
//

#ifndef MAIN_CPP_WIZARD_H
#define MAIN_CPP_WIZARD_H

#include "Player.h"


class Wizard :
        public Player {
private:
    void initVariables();
    void initAnimations();



public:
    Wizard(float x, float y, sf::Texture &texture_sheet, PLAYER_CLASS _class);

    ~Wizard();


    void updateAttack(const float& dt);
    void updateAnimation(const float &dt, ANIMATION_STATE animState);

};



#endif //MAIN_CPP_WIZARD_H
