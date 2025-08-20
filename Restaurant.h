#pragma once
#include"LinkedList.h"
#include"ArrayStack.h"
#include"priQueue.h"
#include"waitNorm.h"
#include"LinkedQueue.h"
#include"Chief.h"
#include"Event.h"
#include"Order.h"
#include "Comparators.h"
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <algorithm>
#include <iomanip>
#include "CancelEvent.h"
#include "ArrivalEvent.h"
#include "PromoteEvent.h"
#include "UI.h"

using namespace std;

class Restaurant {
private:
    int autoPromotedOrders;
    int autoPromotionLimit;
public:
    Restaurant() : ui(new UI()), emergencyReports(0), currentTime(0), autoPromotedOrders(0), autoPromotionLimit(0) {}
    /*  ~Restaurant() { delete ui; }*/
    priQueue<Chief*> emergencyChefs;
    priQueue<Order*> waitingVIP;
    LinkedQueue<Order*> waitingVegan;
    waitNorm<Order*> waitingNormal;
    LinkedQueue<Event*> eventsList;
    priQueue<Order*> inServiceList;
    ArrayStack<Order*> doneList;
    priQueue<Chief*> availableVIPChefs;
    priQueue<Chief*> availableNormalChefs;
    priQueue<Chief*> availableVeganChefs;
    priQueue<Chief*> InBreak_chief;
    int emergencyReports;
    int currentTime;
    UI* ui;
public:
 
    ~Restaurant() {
        delete ui;
        ui = nullptr;
    }

    // Core functions
    bool cancelnormOrder(int ID);
    void loadInputFile(const char* fileName);
    void processEvents(int currentTimestep);
    void addToWaitingList(Order* pOrder);
    void simulate(int mode);
    void runSimpleSimulator();
    bool CheckEmpty() const;

    // Assignment functions
    void assignVIPOrders(int currentTime);
    void assignNormalOrders(int currentTime);
    void assignVeganOrders(int currentTime);

    // Order processing
    void randomlyCompleteOrders();
    void completeorders(int currentTime);
    void randomlyAssignOrders();

    // Chef management
    void processChefsOnBreak(int currentTime);
    void sendChiefToBreak(Chief* chief);

    // Order management
    bool promoteOrder(int orderID, int extraMoney);
    void checkAutoPromotion(int currentTime);
    // Emergency functions
    void handleHealthEmergency(int chefID, int duration);
    bool removeChefFromService(int chefID);
    void processEmergencyChefs(int currentTime);
    void reportEmergencyNeed(const string& chefType, int currentTime);

    // Output
    void generateOutputFile(const char* fileName);

    friend class UI;
};