#pragma once
class Chief;

class Order
{
private:
    int ID;
    char Type;
    int Request_Time_Step;
    int Number_of_dishes;
    int Total_Price;
    Chief* assignedChief;
    int Service_Start_Time;
    int Waiting_Time;
    int Finish_Time;
    int Service_Time;
public:
    Order(int id, char typ, int rt, int sz, int mon);
    void setID(int id);
    void setType(char typ);
    void setRT(int rt);
    void setsize(int sz);
    void setmoney(int mon);
    void setServeStartTime(int st);
    void setwaitingtime(int wt);
    void setassignedchief(Chief* assc);
    int getID() const;
    char getType() const;
    int getRT() const;
    int getSize() const;
    int getMoney() const;
    int getserveStartTime() const;
    int getwaitingtime() const;
    Chief* getassignedchief() const;
    int getFinishTime()const;
    void setFinishTime(int time);
    int getServiceTime()const;
    void setServiceTime(int time);
};

