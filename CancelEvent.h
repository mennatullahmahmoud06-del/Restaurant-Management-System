// CancelEvent.h
#pragma once
#include "Event.h"

class CancelEvent : public Event {
public:
    CancelEvent(int ts, int id) : Event(ts, id, 'X') {}
    void Execute(Restaurant* pRest) override;
};