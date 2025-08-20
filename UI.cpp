#include "UI.h"
#include"Restaurant.h"

void UI::printSimulationStatus(

    const LinkedQueue<Event*>& events,
    const waitNorm<Order*>& waitingNormal,
    const LinkedQueue<Order*>& waitingVegan,
    const priQueue<Order*>& waitingVIP,
    const priQueue<Chief*>& availableVIP,
    const priQueue<Chief*>& availableVegan,
    const priQueue<Chief*>& availableNormal,
    const priQueue<Order*>& inService,
    const priQueue<Chief*>& inBreak,
    const ArrayStack<Order*>& done,
    int timestep
) {
    std::cout << "\n Current Timestep: " << timestep << std::endl;

    // === Events List ===
    std::cout << "=============== Events List =============== \n";
    events.printFirst10();

    // === Waiting Orders ===
    std::cout << "\n\n";
    std::cout << "--------------- Waiting Orders --------------- \n";
    std::cout << waitingNormal.getCount()<< " NRM orders: ";
    waitingNormal.printIDs();

    std::cout << waitingVegan.getCount() << " VEG orders: ";
    waitingVegan.printIDs();

    std::cout << waitingVIP.count() << " VIP orders: ";
    waitingVIP.printIDs();

    // === Available Chiefs ===
   
    std::cout << "--------------- Available Chiefs ---------------\n";
    std::cout << availableNormal.count() << " NRM chiefs: ";
    availableNormal.printIDs();

    std::cout << availableVegan.count() << " VEG chiefs: ";
    availableVegan.printIDs();

    std::cout << availableVIP.count() << " VIP chiefs: ";
    availableVIP.printIDs();

    // === In-Service Orders ===
    std::cout << "\n";
    std::cout << "--------------- In-Service Orders ---------------\n";
    std::cout << inService.count() << " orders: ";
    inService.printIDs();

    // === In-Break Chiefs ===
    std::cout << "\n";
    std::cout << "--------------- In-Break Chiefs ---------------\n";
    std::cout << inBreak.count() << " chiefs: ";
    inBreak.printIDs();

    // === Done Orders ===
    std::cout << "\n";
    std::cout << "--------------- Done Orders ---------------\n";
    std::cout << done.count() << " orders: ";
    done.printAll();

    std::cout << "Press any key to continue...";
}

void UI::interactivemode(Restaurant* R)
{
    R->runSimpleSimulator();
}



void UI::waitForEnter()
{
    cin.get();
}

