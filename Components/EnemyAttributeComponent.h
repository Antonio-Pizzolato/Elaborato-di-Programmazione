//
// Created by Antonio on 11/12/2021.
//

#ifndef MAIN_CPP_ENEMYATTRIBUTECOMPONENT_H
#define MAIN_CPP_ENEMYATTRIBUTECOMPONENT_H


#include "cmath"
#include <string>
#include "sstream"
#include "../Util.h"


class EnemyAttributeComponent {
public:
    //Leveling
    int level;

    //Attributes
    int vitality;
    int strength;

    //Stats
    int hp;
    int hpMax;
    int damageMin;
    int damageMax;

    //Cons / Des
    EnemyAttributeComponent(int level, ENEMY enemy);
    virtual ~EnemyAttributeComponent();

    //Functions
    void loseHp(int damage);

    bool isDead() const;

    void updateStats();

    void update();
};



#endif //MAIN_CPP_ENEMYATTRIBUTECOMPONENT_H
