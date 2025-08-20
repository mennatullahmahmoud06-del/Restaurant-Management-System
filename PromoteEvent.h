
#pragma once
#include "Event.h"

class PromoteEvent : public Event {
private:
    int extraMoney;

public:
    PromoteEvent(int ts, int id, int exMon)
        : Event(ts, id, 'P'), extraMoney(exMon) {
    }

    void Execute(Restaurant* pRest) override;
    int getExtraMoney() const { return extraMoney; }
};