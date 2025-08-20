#include <cstdlib>
#include <iostream>
#include <ctime>
#include "Restaurant.h"
#include "UI.h"

using namespace std;

int main() {
    
    srand(time(0));

    
    cout << "Select Mode:\n";
    cout << "1 - Interactive Mode\n";
    cout << "2 - Silent Mode \n";
    cout << "Enter choice: ";

    int choice;
    cin >> choice;
    Restaurant restaurant;
    restaurant.simulate(choice);

    //if (choice == 2) {
    //    //will be added later
    //    
    //}
    //
    //restaurant.loadInputFile("Text.txt");  
    //restaurant.runSimpleSimulator();        

    exit(0);
}