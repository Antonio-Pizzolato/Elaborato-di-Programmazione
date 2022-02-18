//
// Created by Antonio on 18/02/2022.
//

#ifndef MAIN_CPP_ARCHER_H
#define MAIN_CPP_ARCHER_H


#include "Player.h"


class Archer :
        public Player {
private:

    void initVariables();
    void initAnimations();


    //sf::Texture arrow_sheet;


public:
    Archer(float x, float y, sf::Texture &texture_sheet, PLAYER_CLASS _class);

    ~Archer();


    void updateAttack(const float& dt);

    void updateAnimation(const float &dt, ANIMATION_STATE animState);



};



#endif //MAIN_CPP_ARCHER_H
