#include "Order.h"
#include"Chief.h"
#include <iostream>
using namespace std;

Order::Order(int id, char typ, int rt, int sz, int mon)
    : ID(id), Type(typ), Request_Time_Step(rt), Number_of_dishes(sz), Total_Price(mon),
    assignedChief(nullptr), Service_Start_Time(-1), Waiting_Time(0),
    Service_Time(0), Finish_Time(0) {
}


    
    // Remove the int declarations completely


void Order:: setID(int id) { ID=id; }

void Order::setmoney(int mon) { Total_Price = mon; }

void Order::setType(char typ) { Type = typ; }

void Order::setRT(int rt) { Request_Time_Step = rt; }

void Order::setsize(int sz) { Number_of_dishes = sz; }

void Order::setServeStartTime(int st) { Service_Start_Time = st; }

void Order::setwaitingtime(int wt) { Waiting_Time=wt; }

void Order::setassignedchief(Chief* assc) { assignedChief=assc; }

int Order:: getID() const { return ID; }

char Order:: getType() const { return Type; }

int Order:: getRT() const { return     Request_Time_Step; }

int Order:: getSize() const { return Number_of_dishes; }

int Order:: getMoney() const { return Total_Price; }

int Order::getserveStartTime()const { return Service_Start_Time; }

int Order::getwaitingtime() const { return Waiting_Time; }

Chief* Order::getassignedchief()const { return assignedChief; }

int Order::getFinishTime() const { return Finish_Time;}

void Order::setFinishTime(int time) { Finish_Time = time; }

int Order::getServiceTime() const{ return Service_Time;}

void Order::setServiceTime(int time) { Service_Time = time; }


ostream& operator<<(ostream& os, const Order* order) {
    if (!order) {
        os << "null";
        return os;
    }

    os << "O" << order->getID()
        << "(Type:" << order->getType()
        << ",Request_Time_Step:" << order->getRT()
        << ",Size:" << order->getSize() << ")";
    return os;
}
