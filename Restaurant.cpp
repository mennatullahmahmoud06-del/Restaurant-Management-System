#include "Restaurant.h"
#include "priQueue.h"
#include "LinkedQueue.h"
#include "ArrayStack.h"
#include "waitNorm.h"
#include "Chief.h"
#include "Event.h"
#include "Order.h"
#include "Comparators.h"
#include "UI.h"

bool Restaurant::cancelnormOrder(int ID) {
    bool cancelled = waitingNormal.cancelOrder(ID);
    return cancelled;
}

void Restaurant::randomlyCompleteOrders() {
    if (!inServiceList.isEmpty() && (rand() % 100 + 1) <= 15) {
        Order* top;
        int priorityDummy;
        bool success = inServiceList.dequeue(top, priorityDummy);

        if (success) {
            if (top->getassignedchief()) {
                top->getassignedchief()->setOrders_Done(top->getassignedchief()->getOrders_done() + 1);
                if (top->getassignedchief()->getOrders_done() >= top->getassignedchief()->getOrders_Before_Break()) {
                    sendChiefToBreak(top->getassignedchief());
                }
                else {
                    if (top->getassignedchief()->getType() == 'V') {
                        availableVIPChefs.enqueue(top->getassignedchief(), top->getassignedchief()->getspeed());
                    }
                    else if (top->getassignedchief()->getType() == 'N') {
                        availableNormalChefs.enqueue(top->getassignedchief(), top->getassignedchief()->getspeed());
                    }
                    else if (top->getassignedchief()->getType() == 'G') {
                        availableVeganChefs.enqueue(top->getassignedchief(), top->getassignedchief()->getspeed());
                    }
                }
            }
        }
        doneList.push(top);
    }
}

void Restaurant::completeorders(int currentTime)
{
    cout << "Checking orders for completion at time " << currentTime << endl;
    cout << "Orders in service: " << inServiceList.count() << endl;

    // ... rest of method


    priQueue<Order*> tempQueue;
    Order* order;
    int priority;
    while (inServiceList.dequeue(order, priority)) {
        if ((order->getFinishTime()) == currentTime) {
            cout << "Completing order " << order->getID() << " at time " << currentTime << endl;
            Chief* chief = order->getassignedchief();
            if (chief)
            {
                chief->setOrders_Done((chief->getOrders_done()) + 1);
                if ((chief->getOrders_done()) >= chief->getOrders_Before_Break()) {
                    sendChiefToBreak(chief);
                    chief->setOrders_Done(0);
                }
                else
                {
                    if ((chief->getType()) == 'V')
                        availableVIPChefs.enqueue(chief, chief->getspeed());
                    else if ((chief->getType()) == 'N') {
                        availableNormalChefs.enqueue(chief, chief->getspeed());
                    }
                    else if ((chief->getType()) == 'G') {
                        availableVeganChefs.enqueue(chief, chief->getspeed());
                    }
                }

                doneList.push(order);
            }
        }

        else {
            tempQueue.enqueue(order, priority);

        }


    }
    while (!tempQueue.isEmpty()) {
        tempQueue.dequeue(order, priority);
        inServiceList.enqueue(order, priority);
    }

}

void Restaurant::randomlyAssignOrders() {
    if (!waitingNormal.isEmpty() && (rand() % 100 + 1) <= 70) {
        Order* o = nullptr;
        Chief* chef = nullptr;
        int priority;
        // Peek first
        if (waitingNormal.peek(o) && o) {
            // Try to get a chief
            if (!availableNormalChefs.isEmpty()) {

                availableNormalChefs.dequeue(chef, priority);
            }
            else if (!availableVIPChefs.isEmpty()) {
                availableVIPChefs.dequeue(chef, priority);
            }

            if (chef) {
                waitingNormal.dequeue(o);
                o->setassignedchief(chef);
                o->setServeStartTime(currentTime);
                o->setwaitingtime(currentTime - o->getRT());
                int priority = 100 - o->getSize();
                inServiceList.enqueue(o, priority);
                inServiceList.enqueue(o, priority);

            }
        }
    }
}

bool Restaurant::CheckEmpty() const
{
    bool noMoreEvents = eventsList.isEmpty();

    bool allOrdersDone =
        waitingNormal.isEmpty() &&
        waitingVegan.isEmpty() &&
        waitingVIP.isEmpty() &&
        inServiceList.isEmpty();

    return noMoreEvents && allOrdersDone;
}

void Restaurant::runSimpleSimulator() {
    srand(time(0));
    int timestep = 1;
    const int MAX_TIMESTEPS = 200;

    while (!CheckEmpty() && timestep <= 100) {
        currentTime = timestep;
        cout << "\nTimestep " << timestep << " ---\n";

        processEvents(timestep);
        assignVIPOrders(timestep);
        assignVeganOrders(timestep);
        assignNormalOrders(timestep);
        randomlyCompleteOrders();
        processChefsOnBreak(timestep);




        ui->printSimulationStatus(eventsList, waitingNormal, waitingVegan, waitingVIP,
            availableVIPChefs, availableVeganChefs, availableNormalChefs,
            inServiceList, InBreak_chief, doneList, timestep);

        ui->waitForEnter();
        timestep++;
    }
}

void Restaurant::processEvents(int currentTime) {
    Event* e = nullptr;
    while (!eventsList.isEmpty()) {
        if (eventsList.peek(e) && e && e->getTimeStep() == currentTime) {
            eventsList.dequeue(e);
            e->Execute(this);
            delete e;
            e = nullptr;
        }
        else {
            break;
        }
    }
}

void Restaurant::assignVIPOrders(int currentTime) {
    while (!waitingVIP.isEmpty()) {
        Order* order = nullptr;
        int priorityDummy;  // Initialize priorityDummy
        bool success = waitingVIP.dequeue(order, priorityDummy);
        if (!success || !order) continue;

        Chief* chef = nullptr;
        if (!availableVIPChefs.isEmpty()) {
            availableVIPChefs.dequeue(chef, priorityDummy);
        }
        else if (!availableNormalChefs.isEmpty()) {
            availableNormalChefs.dequeue(chef, priorityDummy);
        }
        else {
            // No chefs available - check if it's due to emergencies
            if (!emergencyChefs.isEmpty()) {
                reportEmergencyNeed("VIP", currentTime);
            }
            waitingVIP.enqueue(order, priorityDummy);
            break;
        }
        if (!chef) {
            waitingVIP.enqueue(order, priorityDummy);
            break;
        }

        // Assignment logic
        order->setassignedchief(chef);
        order->setServeStartTime(currentTime);
        order->setwaitingtime(currentTime - order->getRT());
        int Service_Time = order->getSize() / chef->getNumberOfDishesPerT();// Rounded up if needed
        if (order->getSize() % chef->getNumberOfDishesPerT() != 0) Service_Time++;
        order->setServiceTime(Service_Time);
        int Finish_Time = currentTime + order->getServiceTime();
        order->setFinishTime(Finish_Time);
        int priority = -order->getFinishTime();
        inServiceList.enqueue(order, priority);
    }
}

void Restaurant::assignNormalOrders(int currentTime) {
    while (!waitingNormal.isEmpty() &&
        (!availableNormalChefs.isEmpty() || !availableVIPChefs.isEmpty())) {
        Order* order;
        waitingNormal.dequeue(order);
        Chief* chef = nullptr;
        int priority;

        if (!availableNormalChefs.isEmpty()) {
            availableNormalChefs.dequeue(chef, priority);
        }

        else {
            availableVIPChefs.dequeue(chef, priority);
        }

        // Set all order properties FIRST
        order->setassignedchief(chef);
        order->setServeStartTime(currentTime);
        order->setwaitingtime(currentTime - order->getRT());
        int Service_Time = order->getSize() / chef->getNumberOfDishesPerT();
        if (order->getSize() % chef->getNumberOfDishesPerT() != 0) Service_Time++;
        order->setServiceTime(Service_Time);

        // Calculate finish time
        int Finish_Time = currentTime + order->getServiceTime();
        order->setFinishTime(Finish_Time);

        int servpriority = -order->getFinishTime();
        inServiceList.enqueue(order, servpriority);
    }
}

void Restaurant::assignVeganOrders(int currentTime) {
    while (!waitingVegan.isEmpty() && !availableVeganChefs.isEmpty()) {
        Order* order;
        waitingVegan.dequeue(order);
        Chief* chef;
        int veganpriority;
        availableVeganChefs.dequeue(chef, veganpriority);

        // Set all properties FIRST
        order->setassignedchief(chef);
        order->setServeStartTime(currentTime);
        order->setwaitingtime(currentTime - order->getRT());

        // Calculate times BEFORE adding to service
        int Service_Time = order->getSize() / chef->getNumberOfDishesPerT();
        if (order->getSize() % chef->getNumberOfDishesPerT() != 0) Service_Time++;
        order->setServiceTime(Service_Time);
        int Finish_Time = currentTime + order->getServiceTime();
        order->setFinishTime(Finish_Time);

        int priority = -order->getFinishTime();
        inServiceList.enqueue(order, priority);
    }
}

void Restaurant::sendChiefToBreak(Chief* chief) {
    if (!chief || chief->getIsOnBreak()) return;

    chief->setIsOnBreak(true);
    chief->setRemaining_BreakTime(chief->getLenghtofbreak());


    int priority = chief->getLenghtofbreak();
    InBreak_chief.enqueue(chief, priority);

    cout << "Chief " << chief->getID() << " sent on break for "
        << priority << " minutes." << endl;
}

bool Restaurant::promoteOrder(int orderID, int extraMoney)
{
    Order* order = waitingNormal.getOrder(orderID);
    if (!order) return false;

    order->setType('V');
    order->setmoney(extraMoney + order->getMoney());
    waitingNormal.cancelOrder(orderID);


    int priority = order->getMoney() - (order->getSize() / 2) + 2 * (currentTime - order->getRT());
    waitingVIP.enqueue(order, priority);

    return true;
}

void Restaurant::loadInputFile(const char* fileName) {
    ifstream inFile(fileName);
    if (!inFile) {
        cout << "Unable to open input file: " << fileName << endl;
        return;
    }

    int normalChiefs, veganChiefs, vipChiefs;
    if (!(inFile >> normalChiefs >> veganChiefs >> vipChiefs)) {
        cout << "Error reading number of chiefs" << endl;
        inFile.close();
        return;
    }

    int totalchiefs = normalChiefs + veganChiefs + vipChiefs;

    int* speedsline = new int[totalchiefs + 1];
    int* breaklines = new int[totalchiefs + 1];
    for (int i = 0; i < totalchiefs; i++) {
        if (i >= totalchiefs) break;
        if (!(inFile >> speedsline[i])) {
            cout << "Error reading chief speeds" << endl;
            delete[] speedsline;
            inFile.close();
            return;
        }
    }


    string breakLine;
    getline(inFile, breakLine); // consume any remaining newline
    getline(inFile, breakLine); // get the actual break line

    istringstream breakStream(breakLine);
    for (int i = 0; i < totalchiefs; i++) {
        if (!(breakStream >> breaklines[i])) {
            cout << "Error reading break durations at index " << i << endl;
            delete[] speedsline;
            delete[] breaklines;
            inFile.close();
            return;
        }
    }

    int BO;
    if (!(breakStream >> BO)) {
        cout << "Error reading orders done before break" << endl;
        delete[] speedsline;
        delete[] breaklines;
        inFile.close();
        return;
    }


    int autoPromLimit;
    if (!(inFile >> autoPromLimit)) {
        cout << "Error reading auto-promotion limit" << endl;
        delete[] speedsline;
        delete[] breaklines;
        inFile.close();
        return;
    }
    this->autoPromotionLimit = autoPromLimit;
    cout << "Auto-promotion limit set to: " << autoPromotionLimit << endl;

    int eventCount;
    if (!(inFile >> eventCount)) {
        cout << "Error reading event count" << endl;
        inFile.close();
        return;
    }
    int chiefId = 1;
    int index = 0;

    int chiefID = 0;



    for (int i = 0; i < normalChiefs; ++i) {
        Chief* chief = new Chief(chiefId++, 'N', speedsline[index], breaklines[index], BO);
        availableNormalChefs.enqueue(chief, chief->getspeed());
        index++;
    }
    for (int i = 0; i < veganChiefs; ++i) {
        Chief* chief = new Chief(chiefId++, 'G', speedsline[index], breaklines[index], BO);
        availableVeganChefs.enqueue(chief, chief->getspeed());
        index++;
    }
    for (int i = 0; i < vipChiefs; ++i) {
        Chief* chief = new Chief(chiefId++, 'V', speedsline[index], breaklines[index], BO);
        availableVIPChefs.enqueue(chief, chief->getspeed());
        index++;
    }



    char eventType;
    int eventsProcessed = 0;

    while (eventsProcessed < eventCount and inFile >> eventType) {
        if (eventType == 'R') {
            char orderType;
            int ts, id, size, money;
            if (!(inFile >> orderType >> ts >> id >> size >> money)) {
                cout << "Error reading arrival event" << endl;
                break;
            }
            Event* e = new ArrivalEvent(ts, id, orderType, size, money);
            eventsList.enqueue(e);
        }
        else if (eventType == 'X') {
            int ts, id;
            if (!(inFile >> ts >> id)) {
                cout << "Error reading cancellation event" << endl;
                break;
            }
            Event* e = new CancelEvent(ts, id);
            eventsList.enqueue(e);
        }
        else if (eventType == 'P') {
            int ts, id, extraMoney;
            if (!(inFile >> ts >> id >> extraMoney)) {
                cout << "Error reading promotion event" << endl;
                break;
            }
            Event* e = new PromoteEvent(ts, id, extraMoney);
            eventsList.enqueue(e);
        }
        else {
            cout << "Unknown event type: " << eventType << endl;
            break;
        }
        eventsProcessed++;
    }

    if (eventsProcessed != eventCount) {
        cout << "Warning: Processed " << eventsProcessed << " events, expected " << eventCount << endl;
    }
    delete[] speedsline;
    delete[] breaklines;
    inFile.close();

}

void Restaurant::generateOutputFile(const char* fileName) {
    ofstream outFile(fileName);
    if (!outFile) {
        cout << "Error: Unable to create output file: " << fileName << endl;
        return;
    }

    cout << "DEBUG: doneList contains " << doneList.count() << " orders" << endl;

    vector<Order*> completedOrders;
    ArrayStack<Order*> tempStack = doneList;
    Order* order;
    while (doneList.pop(order)) {
        completedOrders.push_back(order);
        cout << "DEBUG: Extracted order " << order->getID() << endl;
    }

    cout << "DEBUG: Extracted " << completedOrders.size() << " orders total" << endl;

    outFile << "FT\tID\tRT\tWT\tST" << endl;

    int totalOrders = completedOrders.size();
    int normalOrders = 0, veganOrders = 0, vipOrders = 0;
    double totalWaitTime = 0, totalServiceTime = 0;

    for (const Order* order : completedOrders) {
        outFile << order->getFinishTime() << "\t"
            << order->getID() << "\t"
            << order->getRT() << "\t"
            << order->getwaitingtime() << "\t"
            << order->getServiceTime() << endl;

        totalWaitTime += order->getwaitingtime();
        totalServiceTime += order->getServiceTime();

        switch (order->getType()) {
        case 'N': normalOrders++; break;
        case 'G': veganOrders++; break;
        case 'V': vipOrders++; break;
        }
    }

    int totalNormalChefs = availableNormalChefs.count();
    int totalVeganChefs = availableVeganChefs.count();
    int totalVipChefs = availableVIPChefs.count();
    int breakChefs = InBreak_chief.count();


    outFile << "Orders: " << totalOrders
        << " [Norm:" << normalOrders
        << ", Veg:" << veganOrders
        << ", VIP:" << vipOrders << "]" << endl;

    outFile << "Chiefs: " << (totalNormalChefs + totalVeganChefs + totalVipChefs + breakChefs)
        << " [Norm:" << totalNormalChefs
        << ", Veg:" << totalVeganChefs
        << ", VIP:" << totalVipChefs << "]" << endl;

    double avgWait = (totalOrders > 0) ? (totalWaitTime / totalOrders) : 0.0;
    double avgServ = (totalOrders > 0) ? (totalServiceTime / totalOrders) : 0.0;
    double autoPromPercent = (totalOrders > 0) ? (autoPromotedOrders * 100.0 / totalOrders) : 0.0;

    outFile << fixed << setprecision(1);
    outFile << "Avg Wait = " << avgWait
        << ", Avg Serv = " << avgServ
        << ", Auto-promoted = " << autoPromPercent << "%" << endl;

    outFile.close();
    cout << "Output file generated successfully with " << totalOrders << " completed orders." << endl;
}

void Restaurant::addToWaitingList(Order* pOrder) {
    if (!pOrder) return;
    char type = pOrder->getType();
    if (type == 'V') {

        int priority = pOrder->getMoney();
        waitingVIP.enqueue(pOrder, priority);
    }
    else if (type == 'N') {
        waitingNormal.enqueue(pOrder);
    }
    else if (type == 'G') {

        waitingVegan.enqueue(pOrder);
    }
}

void Restaurant::processChefsOnBreak(int currentTime) {
    priQueue<Chief*> stillOnBreak;
    Chief* chief;
    int breakDuration;

    // Process all chiefs currently on break
    while (InBreak_chief.dequeue(chief, breakDuration)) {
        // Decrement remaining break time
        int remainingTime = chief->getRemaining_BreakTime() - 1;
        chief->setRemaining_BreakTime(remainingTime);

        if (remainingTime <= 0) {
            // Break finished - return to work
            chief->setIsOnBreak(false);
            chief->setRemaining_BreakTime(0);
            chief->setOrders_Done(0);

            if (chief->getType() == 'V') {
                availableVIPChefs.enqueue(chief, chief->getspeed());
            }
            else if (chief->getType() == 'N') {
                availableNormalChefs.enqueue(chief, chief->getspeed());
            }
            else if (chief->getType() == 'G') {
                availableVeganChefs.enqueue(chief, chief->getspeed());
            }
        }
        else {
            // Still on break
            stillOnBreak.enqueue(chief, remainingTime);
        }
    }

    // Put chiefs still on break back to break queue
    while (stillOnBreak.dequeue(chief, breakDuration)) {
        InBreak_chief.enqueue(chief, breakDuration);
    }
}

void Restaurant::handleHealthEmergency(int chefID, int duration) {
    cout << "\n*** HEALTH EMERGENCY *** Chef " << chefID
        << " unavailable for " << duration << " timesteps!" << endl;

    Chief* emergencyChef = nullptr;
    int chefPriority;
    priQueue<Chief*> tempVipQueue;
    Chief* chef;
    int priority;
    while (availableVIPChefs.dequeue(chef, priority)) {
        if (chef->getID() == chefID) {
            emergencyChef = chef;
        }
        else {
            tempVipQueue.enqueue(chef, priority);
        }
    }
    int rest;
    while (tempVipQueue.dequeue(chef, rest)) {
        availableVIPChefs.enqueue(chef, priority);
    }

    if (!emergencyChef) {
        priQueue<Chief*> tempNormalQueue;
        while (availableNormalChefs.dequeue(chef, rest)) {
            if (chef->getID() == chefID) {
                emergencyChef = chef;
            }
            else {
                tempNormalQueue.enqueue(chef, rest);
            }
        }
        while (tempNormalQueue.dequeue(chef, chefPriority)) {
            availableNormalChefs.enqueue(chef, priority);
        }
    }

    if (!emergencyChef) {
        priQueue<Chief*> tempVeganQueue;
        while (availableVeganChefs.dequeue(chef, rest)) {
            if (chef->getID() == chefID) {
                emergencyChef = chef;
            }
            else {
                tempVeganQueue.enqueue(chef, chefPriority);
            }
        }
        while (tempVeganQueue.dequeue(chef, chefPriority)) {
            availableVeganChefs.enqueue(chef, priority);
        }
    }
    if (!emergencyChef) {
        if (removeChefFromService(chefID)) {
            cout << "Chef " << chefID << " removed from active service due to emergency!" << endl;
        }
    }

    if (emergencyChef) {
        emergencyChef->setInEmergency(true);
        emergencyChef->setEmergencyTimeRemaining(duration);

        emergencyChefs.enqueue(emergencyChef, duration);

        cout << "Chef " << chefID << " (" << emergencyChef->getType()
            << ") moved to emergency unavailability!" << endl;
    }
}

bool Restaurant::removeChefFromService(int chefID) {
    priQueue<Order*> tempServiceQueue;
    Order* order;
    int priority;
    bool chefFound = false;

    while (inServiceList.dequeue(order, priority)) {
        if (order->getassignedchief() && order->getassignedchief()->getID() == chefID) {
           
            cout << "Order " << order->getID() << " returned to waiting due to chef emergency!" << endl;
            order->setassignedchief(nullptr);
            addToWaitingList(order);
            chefFound = true;
        }
        else {
            tempServiceQueue.enqueue(order, priority);
        }
    }

    while (tempServiceQueue.dequeue(order, priority)) {
        inServiceList.enqueue(order, priority);
    }

    return chefFound;
}

void Restaurant::processEmergencyChefs(int currentTime) {
    priQueue<Chief*> tempEmergencyQueue;
    Chief* chef;
    int emergencyTime;

    while (emergencyChefs.dequeue(chef, emergencyTime)) {
       
        int remainingTime = chef->getEmergencyTimeRemaining() - 1;
        chef->setEmergencyTimeRemaining(remainingTime);

        if (remainingTime <= 0) {
           
            chef->setInEmergency(false);
            chef->setEmergencyTimeRemaining(0);

            cout << "Chef " << chef->getID() << " (" << chef->getType()
                << ") recovered from emergency and returned to work!" << endl;

            if (chef->getType() == 'V') {
                availableVIPChefs.enqueue(chef, chef->getspeed());
                chef->setspeed(chef->getspeed() * 0.5);
            }
            else if (chef->getType() == 'N') {
                availableNormalChefs.enqueue(chef, chef->getspeed());
                chef->setspeed(chef->getspeed() * 0.5);
            }
            else if (chef->getType() == 'G') {
                availableVeganChefs.enqueue(chef, chef->getspeed());
                chef->setspeed(chef->getspeed() * 05);
            }
        }
        else {
            tempEmergencyQueue.enqueue(chef, remainingTime);
        }
    }

    // Restore emergency queue
    while (tempEmergencyQueue.dequeue(chef, emergencyTime)) {
        emergencyChefs.enqueue(chef, emergencyTime);
    }
}

void Restaurant::reportEmergencyNeed(const string& chefType, int currentTime) {
    emergencyReports++;
    cout << "\n!!! EMERGENCY REPORT !!! At time " << currentTime
        << ": Need " << chefType << " chef but all are unavailable due to emergencies!" << endl;
    cout << "Total emergency shortage reports: " << emergencyReports << endl;
}

void Restaurant::simulate(int mode) {
    this->loadInputFile("Text6.txt");
    int timestep = 1;
    emergencyReports = 0;

    if (mode == 1) {

        while (!CheckEmpty()) {
            currentTime = timestep;
            cout << "\nTimestep " << timestep << " ---\n";
            processEvents(timestep);


            processEmergencyChefs(timestep);
            assignVIPOrders(timestep);
            assignNormalOrders(timestep);
            assignVeganOrders(timestep);
            completeorders(timestep);
            processChefsOnBreak(timestep);

            ui->printSimulationStatus(eventsList, waitingNormal, waitingVegan, waitingVIP,
                availableVIPChefs, availableVeganChefs, availableNormalChefs,
                inServiceList, InBreak_chief, doneList, timestep);

            ui->waitForEnter();
            timestep++;
        }

        cout << "\n=== EMERGENCY SUMMARY ===" << endl;
        cout << "Total emergency shortage reports: " << emergencyReports << endl;

        generateOutputFile("interactive_output.txt");
    }
    if (mode == 2) {
        cout << "Silent simulation mode started" << endl;
        while (!CheckEmpty()) {
            currentTime = timestep;
            processEvents(timestep);
            processEmergencyChefs(timestep);
            checkAutoPromotion(timestep);      // ADD THIS LINE!
            assignVIPOrders(timestep);
            assignNormalOrders(timestep);
            assignVeganOrders(timestep);       // Correct order
            completeorders(timestep);
            processChefsOnBreak(timestep);
            timestep++;
        }
        cout << "Emergency shortage reports: " << emergencyReports << endl;
        generateOutputFile("projectID_output.txt");
        cout << "Simulation ends, output file created..." << endl;
    }
}

void Restaurant::checkAutoPromotion(int currentTime) {
    vector<Order*> ordersToPromote;
    Node<Order*>* current = waitingNormal.getfrontptr();

    while (current) {
        Order* order = current->getItem();
        int waitingTime = currentTime - order->getRT();  // Defined here

        if (waitingTime >= autoPromotionLimit) {
            ordersToPromote.push_back(order);
        }
        current = current->getNext();
    }

    for (Order* order : ordersToPromote) {
        // waitingTime is NOT ACCESSIBLE here! Need to recalculate:
        int currentWaitingTime = currentTime - order->getRT(); // RECALCULATE

        waitingNormal.cancelOrder(order->getID());
        order->setType('V');
        int priority = order->getMoney() + currentWaitingTime * 10;  // Use recalculated value
        waitingVIP.enqueue(order, priority);
        autoPromotedOrders++;

        cout << "AUTO-PROMOTED Order " << order->getID()
            << " (waited " << currentWaitingTime << " timesteps)" << endl;
    }
}


//void Restaurant::generateOutputFile(const char* fileName) {
//    ofstream outFile(fileName);
//    if (!outFile) {
//        cout << "Error: Unable to create output file: " << fileName << endl;
//        return;
//    }
//
//    
//    vector<Order*> completedOrders;
//    ArrayStack<Order*> tempStack = doneList; 
//
//    
//    Order* order;
//    while (doneList.pop(order)) {
//        completedOrders.push_back(order);
//    }
//
//    for (int i = completedOrders.size() - 1; i >= 0; i--) {
//        doneList.push(completedOrders[i]);
//    }
//
//    sort(completedOrders.begin(), completedOrders.end(),
//        [](const Order* a, const Order* b) {
//            return a->getFinishTime() > b->getFinishTime();
//        });
//
//    outFile << "FT\tID\tRT\tWT\tST" << endl;
//
//    int totalOrders = completedOrders.size();
//    int normalOrders = 0, veganOrders = 0, vipOrders = 0;
//    int autoPromotedOrders = 0; 
//    double totalWaitTime = 0, totalServiceTime = 0;
//
//    for (const Order* order : completedOrders) {
//        outFile << order->getFinishTime() << "\t"
//            << order->getID() << "\t"
//            << order->getRT() << "\t"
//            << order->getwaitingtime() << "\t"
//            << order->getServiceTime() << endl;
//
//        totalWaitTime += order->getwaitingtime();
//        totalServiceTime += order->getServiceTime();
//
//        switch (order->getType()) {
//        case 'N': normalOrders++; break;
//        case 'G': veganOrders++; break;
//        case 'V': vipOrders++; break;
//        }
//    }
//
//    int totalNormalChefs = 0, totalVeganChefs = 0, totalVipChefs = 0;
//
//    LinkedQueue<Chief*> tempNormalQueue = availableNormalChefs;
//    Chief* chef;
//    while (tempNormalQueue.dequeue(chef)) {
//        totalNormalChefs++;
//    }
//
//    LinkedQueue<Chief*> tempVeganQueue = availableVeganChefs;
//    while (tempVeganQueue.dequeue(chef)) {
//        totalVeganChefs++;
//    }
//
//    LinkedQueue<Chief*> tempVipQueue = availableVIPChefs;
//    while (tempVipQueue.dequeue(chef)) {
//        totalVipChefs++;
//    }
//
//    priQueue<Chief*> tempBreakQueue = InBreak_chief;
//    int priority;
//    while (tempBreakQueue.dequeue(chef, priority)) {
//        switch (chef->getType()) {
//        case 'N': totalNormalChefs++; break;
//        case 'G': totalVeganChefs++; break;
//        case 'V': totalVipChefs++; break;
//        }
//    }
//
//    outFile << "Orders: " << totalOrders
//        << " [Norm:" << normalOrders
//        << ", Veg:" << veganOrders
//        << ", VIP:" << vipOrders << "]" << endl;
//
//    outFile << "Chiefs: " << (totalNormalChefs + totalVeganChefs + totalVipChefs)
//        << " [Norm:" << totalNormalChefs
//        << ", Veg:" << totalVeganChefs
//        << ", VIP:" << totalVipChefs << "]" << endl;
//
//    double avgWait = (totalOrders > 0) ? (totalWaitTime / totalOrders) : 0.0;
//    double avgServ = (totalOrders > 0) ? (totalServiceTime / totalOrders) : 0.0;
//    double autoPromPercent = (normalOrders > 0) ? ((double)autoPromotedOrders / normalOrders * 100) : 0.0;
//
//    outFile << fixed << setprecision(1);
//    outFile << "Avg Wait = " << avgWait
//        << ", Avg Serv = " << avgServ
//        << ", Auto-promoted = " << autoPromPercent << "%" << endl;
//
//    outFile.close();
//    cout << "Output file '" << fileName << "' generated successfully!" << endl;
//}
