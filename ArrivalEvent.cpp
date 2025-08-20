// ArrivalEvent.cpp
#include "ArrivalEvent.h"
#include "Restaurant.h"
#include "Order.h"

void ArrivalEvent::Execute(Restaurant* pRest) {
    // Create new order using the FIXED variable names
    Order* newOrder = new Order(getOrderID(), OrderType, getTimeStep(), size, money);
    pRest->addToWaitingList(newOrder);
}