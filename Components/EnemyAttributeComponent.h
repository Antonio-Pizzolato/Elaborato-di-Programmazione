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
    int exp;
    //Attributes
    int vitality;
    int strength;
    //Stats
    int hp;
    int hpMax;
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
