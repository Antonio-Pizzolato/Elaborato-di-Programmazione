#ifndef MAIN_CPP_WARRIOR_H
#define MAIN_CPP_WARRIOR_H


#include "Player.h"

class Warrior :
        public Player {
private:

public:
    Warrior(float x, float y, sf::Texture &texture_sheet, PLAYER_CLASS _class);

    ~Warrior() override;

    void updateAttack(const float& dt) override;
    void updateAnimation(const float &dt, ANIMATION_STATE animState) override;


};



#endif //MAIN_CPP_WARRIOR_H
