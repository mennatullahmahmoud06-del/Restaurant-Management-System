// ArrivalEvent.h
#pragma once
#include "Event.h"

class ArrivalEvent : public Event {
private:
    char OrderType;  // The type of order (V, N, G)
    int size;
    int money;

public:
    ArrivalEvent(int ts, int id, char orderType, int sz, int mon)
        : Event(ts, id, 'R'), OrderType(orderType), size(sz), money(mon) {
    }

    void Execute(Restaurant* pRest) override;

    // Getter functions
    char getOrderType() const { return OrderType; }
    int getSize() const { return size; }
    int getMoney() const { return money; }
};