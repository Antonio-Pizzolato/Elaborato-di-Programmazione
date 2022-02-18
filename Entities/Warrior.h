//
// Created by Antonio on 18/02/2022.
//

#ifndef MAIN_CPP_WARRIOR_H
#define MAIN_CPP_WARRIOR_H


#include "Player.h"

class Warrior :
        public Player {
private:

public:
    Warrior(float x, float y, sf::Texture &texture_sheet, PLAYER_CLASS _class);

    ~Warrior();



    void updateAttack(const float& dt);
    void updateAnimation(const float &dt, ANIMATION_STATE animState);



};



#endif //MAIN_CPP_WARRIOR_H
