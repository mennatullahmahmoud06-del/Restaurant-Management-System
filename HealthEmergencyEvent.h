#pragma once
#include "Event.h"
class HealthEmergencyEvent :
    public Event
{
private:
    int chefID;
    int emergencyDuration;  

public:
    HealthEmergencyEvent(int ts, int chefId, int duration)
        : Event(ts, chefId, 'H'), chefID(chefId), emergencyDuration(duration) {
    }

    void Execute(Restaurant* pRest) override;
    int getChefID() const { return chefID; }
    int getEmergencyDuration() const { return emergencyDuration; }
};

