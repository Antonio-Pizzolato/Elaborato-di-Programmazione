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

    //Attributes
    int vitality;
    int strength;
    int dexterity;
    int agility;
    int intelligence;

    //Stats
    int hp;
    int hpMax;
    int damageMax;
    int defence;

    //Cons / Des
    explicit AttributeComponent(PLAYER_CLASS playerClass);
    virtual ~AttributeComponent();

    //Functions

    void loseHp(int damage);
    void gainHp(int heal);
    void loseExp(int exp_date);
    void gainExp(int exp_date, PLAYER_CLASS playerClass);

    bool isDead() const;

    void updateStats(bool reset);
    void updateLevel(PLAYER_CLASS playerClass);

    void update(PLAYER_CLASS playerClass);
};



#endif //MAIN_CPP_ATTRIBUTECOMPONENT_H
