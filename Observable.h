#ifndef MAIN_CPP_OBSERVABLE_H
#define MAIN_CPP_OBSERVABLE_H

#include "Observer.h"
#include <iostream>
#include <list>

using namespace std;

class Observable {
public:
    //Virtual Destructor
    virtual ~Observable() = 0;
    //Observer stuff
    void addObserver(Observer *observer);
    void removeObserver(Observer *observer);
    virtual void notify() = 0;
    std::list<Observer *> observerList;
};

#endif //MAIN_CPP_OBSERVABLE_H
