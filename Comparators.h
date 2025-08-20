
//#pragma once
//
//#include "Order.h"
//#include "Chief.h"
//#include <cstdlib>  
//#include <ctime>   
//
//struct VIPComparator {
//    bool operator()(const Order* a, const Order* b) {
//        // Simple priority: money matters most
//        return a->getMoney() < b->getMoney(); // Lower money = lower priority
//    }
//};
//
//struct FinishTimeComparator {
//    bool operator()(const Order* a, const Order* b) {
//        return rand() % 2;
//    }
//};
//
//struct BreakEndComparator {
//    bool operator()(const Chief* a, const Chief* b) {
//        return rand() % 2;
//    }
//};
