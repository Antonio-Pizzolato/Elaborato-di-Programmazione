#ifndef MAIN_CPP_OBSERVER_H
#define MAIN_CPP_OBSERVER_H

#include "Entities/Player.h"

class Observer {
public:
    virtual ~Observer() = default;;
    virtual void update(float _killNumber, float _gold) = 0;
};

#endif //MAIN_CPP_OBSERVER_H