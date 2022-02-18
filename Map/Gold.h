//
// Created by Antonio on 18/02/2022.
//

#ifndef MAIN_CPP_GOLD_H
#define MAIN_CPP_GOLD_H

#include <random>
#include "Items.h"

class Gold : public Items
{
public:
    /**
     * Default constructor.
     */
    Gold();

    /**
     * Gets the amount of gold this pickup has.
     * @return The amount of gold the pickup has.
     */
    int GetGoldValue() const;

private:
    /**
     * The value of this gold pickup.
     */
    int goldValue;
};



#endif //MAIN_CPP_GOLD_H
