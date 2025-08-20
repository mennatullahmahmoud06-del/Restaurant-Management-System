
#include "PromoteEvent.h"
#include "Restaurant.h"
#include <iostream>
using namespace std;

void PromoteEvent::Execute(Restaurant* pRest) {
    // Try to promote the order using the restaurant's promoteOrder method
    if (pRest->promoteOrder(getOrderID(), extraMoney)) {
        cout << "Order " << getOrderID() << " promoted to VIP with extra $" << extraMoney << ".\n";
    }
    else {
        cout << "Order " << getOrderID() << " not found or cannot be promoted.\n";
    }
}
