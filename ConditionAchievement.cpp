//
// Created by Antonio on 18/02/2022.
//


#include "ConditionAchievement.h"


ConditionAchievement::ConditionAchievement() : killNumber(0), gold(0) {

}


void ConditionAchievement::notify() {

    for (auto const &i: observerList) {
        i->update(killNumber, gold);
    }

}

void ConditionAchievement::conditionsChanged() {

    notify();
}

void ConditionAchievement::setConditions(float _killNumber, float _gold) {

    killNumber = _killNumber;
    gold = _gold;
    conditionsChanged();
}
