//
// Created by Antonio on 18/02/2022.
//

#ifndef MAIN_CPP_ATTRIBUTECOMPONENT_H
#define MAIN_CPP_ATTRIBUTECOMPONENT_H


#include "cmath"
#include <string>
#include "sstream"
#include "../Util.h"

class AttributeComponent {
public:
    //Leveling
    int level;
    int exp;
    int expNext;
    int attributePoints;

    //Attributes
    int vitality;
    int strength;
    int dexterity;
    int agility;
    int intelligence;

    //Stats
    int hp;
    int hpMax;
    int damageMin;
    int damageMax;
    int accuracy;
    int defence;
    int luck;

    //Cons / Des
    AttributeComponent(PLAYER_CLASS playerClass);
    virtual ~AttributeComponent();

    //Functions
    std::string debugPrint() const;

    void loseHp(int hp);
    void gainHp(int hp);
    void loseExp(int exp);
    void gainExp(int exp, PLAYER_CLASS playerClass);

    bool isDead() const;

    void updateStats(bool reset);
    void updateLevel(PLAYER_CLASS playerClass);

    void update(PLAYER_CLASS playerClass);
};



#endif //MAIN_CPP_ATTRIBUTECOMPONENT_H
