#include "HealthEmergencyEvent.h"
#include "Restaurant.h"
#include <iostream>

void HealthEmergencyEvent::Execute(Restaurant* pRest) {
    pRest->handleHealthEmergency(chefID, emergencyDuration);
}