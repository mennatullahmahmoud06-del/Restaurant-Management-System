
#include "CancelEvent.h"
#include "Restaurant.h"
#include <iostream>
using namespace std;

void CancelEvent::Execute(Restaurant* pRest) {
    // Try to cancel the order from waitingNormal queue
    if (pRest->cancelnormOrder(getOrderID())) {
        cout << "Order " << getOrderID() << " cancelled successfully.\n";
    }
    else if (!pRest->cancelnormOrder(getOrderID())) {
        cout << "Order " << getOrderID() << " not found or cannot be cancelled.\n";
    }
}