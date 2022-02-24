#ifndef MAIN_CPP_ARCHER_H
#define MAIN_CPP_ARCHER_H

#include "Player.h"

class Archer : public Player {
public:
    Archer(sf::Texture &texture_sheet, PLAYER_CLASS _class);
    ~Archer() override;

    void updateAttack(const float &dt) override;
    void updateAnimation(const float &dt, ANIMATION_STATE animState) override;
};


#endif //MAIN_CPP_ARCHER_H
