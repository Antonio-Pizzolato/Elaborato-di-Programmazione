//
// Created by Antonio on 09/02/2022.
//

#include "Observable.h"


void Observable::addObserver(Observer* observer) {
    observerList.push_back(observer);
}

void Observable::removeObserver(Observer* observer) {
    observerList.remove(observer);
}


Observable::~Observable() = default;