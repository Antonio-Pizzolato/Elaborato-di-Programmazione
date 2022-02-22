#include "EnemyAttributeComponent.h"

EnemyAttributeComponent::EnemyAttributeComponent(int level, ENEMY enemy)
        : hp(0), hpMax(0), damageMin(1), damageMax(3), level(level)
{


    switch (enemy) {

        case ENEMY::SLIME:
            vitality = 2;
            strength = 1;
            break;
        case ENEMY::HUMANOID:
            vitality = 3;
            strength = 2;
            break;
        case ENEMY::RAT:
            vitality = 1;
            strength = 2;
            break;
        default:
            vitality = 1;
            strength = 1;
            break;
    }




    updateStats();

}

EnemyAttributeComponent::~EnemyAttributeComponent() {

}

void EnemyAttributeComponent::loseHp(int damage) {
    hp -= damage;
    if(hp < 0)
        hp = 0;
}

bool EnemyAttributeComponent::isDead() const {
    return hp <= 0;
}

void EnemyAttributeComponent::updateStats() {
    hpMax = (vitality * 5 + vitality + strength / 2) * level;
    damageMin = (strength * 2 + this->strength / 4) * level;
    damageMax = (strength * 2 + this->strength / 2) * level;
    hp = hpMax;

}

void EnemyAttributeComponent::update() {

}
