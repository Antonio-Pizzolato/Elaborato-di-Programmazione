//
// Created by Antonio on 18/02/2022.
//

#include "AttributeComponent.h"

AttributeComponent::AttributeComponent(PLAYER_CLASS playerClass):
        level(1), exp(0), hp(0), hpMax(0), damageMin(0), damageMax(0), accuracy(0), defence(0), luck(0){

    expNext = static_cast<int>((50 / 3) * (pow(this->level + 1, 3) - 6 * pow(this->level + 1, 2) + ((this->level + 1) * 17) - 12));
    attributePoints = 3;

    switch (playerClass) {
        case PLAYER_CLASS::WARRIOR:
        {
            vitality = 5;
            strength = 3;
            dexterity = 1;
            agility = 1;
            intelligence = 1;
        }
            break;

        case PLAYER_CLASS::WIZARD:
        {
            vitality = 1;
            strength = 1;
            dexterity = 2;
            agility = 2;
            intelligence = 5;
        }
            break;
        case PLAYER_CLASS::ARCHER:
        {
            vitality = 2;
            strength = 2;
            dexterity = 5;
            agility = 5;
            intelligence = 1;
        }
            break;

        default:
            break;
    }


    updateLevel(playerClass);
    updateStats(true);

}

AttributeComponent::~AttributeComponent() {

}

//Functions
std::string AttributeComponent::debugPrint() const
{
    std::stringstream ss;

    ss << "Level: " << this->level << "\n"
       << "Exp: " << this->exp << "\n"
       << "Exp Next: " << this->expNext << "\n"
       << "Attp: " << this->attributePoints << "\n";

    return ss.str();
}

void AttributeComponent::loseHp(const int hp) {
    this->hp -= hp;
    if(this->hp < 0)
        this->hp = 0;
}

void AttributeComponent::gainHp(const int hp) {
    this->hp += hp;
    if(this->hp >  this->hpMax)
        this->hp = this->hpMax;
}

void AttributeComponent::loseExp(const int exp) {
    this->exp -= exp;
    if(this->exp < 0)
        this->exp = 0;
}
void AttributeComponent::gainExp(const int exp, PLAYER_CLASS playerClass) {

    this->exp += exp;

    this->updateLevel(playerClass);
}

bool AttributeComponent::isDead() const
{
    return hp <= 0;
}

void AttributeComponent::updateStats(const bool reset) {
    hpMax = vitality * 5 + vitality + strength / 2 + intelligence / 5;
    damageMin = strength * 2 + strength / 4 + intelligence / 5;
    damageMax = strength * 2 + strength / 2 + intelligence / 5;
    accuracy = dexterity * 5 + dexterity / 2 + intelligence / 5;
    defence = agility * 2 + agility / 4 + intelligence / 5;
    luck = intelligence * 2 + intelligence / 5;

    if(reset){
        hp = hpMax;
    }

}

void AttributeComponent::updateLevel(PLAYER_CLASS playerClass)
{
    while(exp >= expNext)
    {
        ++level;
        exp -= expNext;
        expNext = static_cast<int>((50 / 3) * (pow(level, 3) - 6 * pow(level, 2) + (level * 17) - 12));
        ++attributePoints;
        switch (playerClass) {
            case PLAYER_CLASS::WARRIOR:
            {
                vitality += 5;
                strength += 3;
                dexterity += 1;
                agility += 1;
                intelligence += 1;
            }
                break;

            case PLAYER_CLASS::WIZARD:
            {
                vitality += 1;
                strength += 1;
                dexterity += 2;
                agility += 2;
                intelligence += 5;
            }
                break;
            case PLAYER_CLASS::ARCHER:
            {
                vitality += 2;
                strength += 2;
                dexterity += 5;
                agility += 5;
                intelligence += 1;
            }
                break;

            default:
                break;
        }
        updateStats(true);
    }


}

void AttributeComponent::update(PLAYER_CLASS playerClass)
{
    updateLevel(playerClass);

}





