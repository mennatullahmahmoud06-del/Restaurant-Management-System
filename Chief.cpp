#include "Chief.h"
#include<iostream>
using namespace std;

void Chief::setspeed(int sp) { Dishes_per_Timestep = sp; }

void Chief::setInEmergency(bool emergency) { is_In_Emergency = emergency; }

void Chief::setEmergencyTimeRemaining(int time) { emergency_Time_Remaining = time; }

bool Chief::getInEmergency() const { return is_In_Emergency; }

int Chief::getEmergencyTimeRemaining() const { return emergency_Time_Remaining; }

void Chief::setOrders_Before_Break(int obb) { Orders_Before_Break = obb; }

void Chief::setIsOnBreak(bool onBreak){  isOnBreak = onBreak;}

void Chief::setOrders_Done(int od) { Orders_Done = od; ; }

void Chief::setLenghtofBreak(int bd) {  Length_of_Break = bd; }

void Chief:: setRemaining_BreakTime(int time) { Remaining_BreakTime = time; }

char Chief::getType() const { return Type; }

int Chief::getNumberOfDishesPerT() const{ return Dishes_per_Timestep;}

int Chief::getRemaining_BreakTime() const { return Remaining_BreakTime; }

int Chief::getID() const{  return ID;}

int Chief::getOrders_done() const{ return Orders_Done; }

int Chief::getLenghtofbreak()const { return  Length_of_Break;}

int Chief::getOrders_Before_Break()const { return Orders_Before_Break; }

bool Chief::getIsOnBreak() const { return isOnBreak; }

int Chief::getspeed()const { return Dishes_per_Timestep; }

void Chief::print() const
{

    cout << "\n-----------------------------------------\n"
        << "               Chief's information               \n"
        << "\n chief's ID is:      " << ID << "\n"
        << "\n chief's break duration:      " << Length_of_Break << "/n"
        << "\n The type of chief is:    " << Type << "\n"
        << "\n Orders done are:     " << Orders_Done << "\n";


}

ostream& operator<<(ostream& os, Chief& chief)
{
    os << "cheif's ID:     " << chief.getID() << "\n"
        << "\nchief is   " << chief.getType() << "\n"
        << "  \n orders done  " << chief.getOrders_done() << "\n"
        << "\nChief will be available after   " << chief.getRemaining_BreakTime();


    return os;
}




