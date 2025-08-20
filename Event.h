// Event.h - Base Event Class Only
#pragma once

// Forward declaration
class Restaurant;

class Event {
protected:
    int TimeStep;
    int OrderID;
    char Type;

public:
    Event(int t, int id, char type) : TimeStep(t), OrderID(id), Type(type) {}
    virtual ~Event() {}  // Virtual destructor for proper cleanup
    virtual void Execute(Restaurant* pRest) = 0;  // Pure virtual function

    // Getter functions
    char getType() const { return Type; }
    int getTimeStep() const { return TimeStep; }
    int getOrderID() const { return OrderID; }
};