#pragma once

class Chief
{
private:
    int ID;
    char Type;
    int Dishes_per_Timestep;
    int Length_of_Break;
    int Orders_Before_Break;
    int Orders_Done;
    int Remaining_BreakTime;
    bool isOnBreak;
    bool is_In_Emergency;
    int emergency_Time_Remaining;
public:
    Chief(int id, char typ, int spd, int bd, int obb)
        : ID(id), Type(typ), Dishes_per_Timestep(spd), Length_of_Break(bd),
        Orders_Before_Break(obb), Orders_Done(0), Remaining_BreakTime(0), 
        isOnBreak(0), is_In_Emergency(false), emergency_Time_Remaining(0) {
    }
    void setspeed(int spd);
    void setOrders_Before_Break(int obb);
    void setLenghtofBreak(int bd);
    void setOrders_Done(int od);
    void setIsOnBreak(bool onBreak);
    void setRemaining_BreakTime(int time);
    void print() const;
    int getspeed()const;
    int getID()const;
    char getType() const;
    int getNumberOfDishesPerT()const;
    int getRemaining_BreakTime() const;
    int getOrders_done() const;
    int getLenghtofbreak()const;
    int getOrders_Before_Break() const;
    bool getIsOnBreak() const;
    void setInEmergency(bool emergency);
    void setEmergencyTimeRemaining(int time);
    bool getInEmergency() const; 
    int getEmergencyTimeRemaining() const; 
};


/* bool sendChiefTobreak(Chief* chief);*/
 /*bool isChiefOnBreak(int chiefID) const;
int countInBreakChiefs() const;*/

