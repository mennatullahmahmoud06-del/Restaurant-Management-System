#pragma once
#include <iostream>
#include "LinkedQueue.h"
#include "priQueue.h"
#include "ArrayStack.h"
#include "Order.h"
#include "Chief.h"
#include "Event.h"
#include "waitNorm.h"
using namespace std;

class UI {
    int count;
    int mode = 0;
    int simulation = 0;
    Restaurant* Rs;
public:

     void printSimulationStatus(
        const LinkedQueue<Event*>& events,
        const waitNorm<Order*>& waitingNormal,
        const LinkedQueue<Order*>& waitingVegan,
        const priQueue<Order*>& waitingVIP,
        const priQueue<Chief*>& availableVIP,
        const priQueue<Chief*>& availableVegan,
        const priQueue<Chief*>& availableNormal,
        const priQueue<Order*>& inService,
        const priQueue<Chief*>& inBreak,
        const ArrayStack<Order*>& done,
        int timestep
    );

    void interactivemode(Restaurant* R);

    static void waitForEnter();
};