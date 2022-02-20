#include "AttributeComponent.h"

AttributeComponent::AttributeComponent(PLAYER_CLASS playerClass):
        level(1), exp(0), hp(0), hpMax(0), damageMin(0), damageMax(0), defence(0){

    expNext = static_cast<int>((50 / 3) * (pow(level + 1, 3) - 6 * pow(level + 1, 2) + ((level + 1) * 17) - 12));

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

AttributeComponent::~AttributeComponent() = default;

//Functions
void AttributeComponent::loseHp(int damage) {
    hp -= damage;
    if(hp < 0)
        hp = 0;
}

void AttributeComponent::gainHp(int heal) {
    hp += heal;
    if(hp >  hpMax)
        hp = hpMax;
}

void AttributeComponent::loseExp(int exp_date) {
    exp -= exp_date;
    if(exp < 0)
        exp = 0;
}
void AttributeComponent::gainExp(int exp_date, PLAYER_CLASS playerClass) {

    exp += exp_date;

    updateLevel(playerClass);
}

bool AttributeComponent::isDead() const
{
    return hp <= 0;
}

void AttributeComponent::updateStats(const bool reset) {
    hpMax = vitality * 5 + vitality + strength / 2 + intelligence / 5;
    damageMin = strength * 2 + strength / 4 + intelligence / 5;
    damageMax = strength * 2 + strength / 2 + intelligence / 5;
    defence = agility * 2 + agility / 4 + intelligence / 5;

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





