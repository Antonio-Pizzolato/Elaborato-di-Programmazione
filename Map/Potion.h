//
// Created by Antonio on 27/11/2021.
//

#ifndef MAIN_CPP_POTION_H
#define MAIN_CPP_POTION_H


#include "Items.h"

class Potion : public Items
{
public:
    Potion();


    int GetHpValue() const;

private:

    int hpPotionValue;
};


#endif //MAIN_CPP_POTION_H
