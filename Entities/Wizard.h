#ifndef MAIN_CPP_WIZARD_H
#define MAIN_CPP_WIZARD_H

#include "Player.h"

class Wizard : public Player {
public:
    Wizard(sf::Texture &texture_sheet, PLAYER_CLASS _class);
    ~Wizard() override;

    void updateAttack(const float &dt) override;
    void updateAnimation(const float &dt, ANIMATION_STATE animState) override;
};

#endif //MAIN_CPP_WIZARD_H
