#ifndef MAIN_CPP_CONDITIONACHIEVEMENT_H
#define MAIN_CPP_CONDITIONACHIEVEMENT_H

#include "Observable.h"

class ConditionAchievement : public Observable {
private:
    float killNumber;
    float gold;
public:
    ConditionAchievement();

    void notify() override;
    void conditionsChanged();
    void setConditions(float _killNumber, float _gold);
};


#endif //MAIN_CPP_CONDITIONACHIEVEMENT_H
