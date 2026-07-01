Restaurant Management System (C++ Data Structures Project)

A robust, event-driven simulation of a restaurant environment built entirely in C++ using custom-implemented data structures. The system models the complete lifecycle of restaurant operations, including order processing, chef assignment, priority handling, and dynamic emergency management.


Project Overview

This project was developed to demonstrate an advanced understanding of Abstract Data Types (ADTs) and Object-Oriented Programming (OOP) in C++. Instead of using the C++ Standard Template Library (STL), all underlying data structures were implemented from scratch to manage the complex state of the restaurant simulation. 

The simulation reads a list of events from an input file, processes them timestep by timestep, manages the assignment of orders to available chefs, handles VIP prioritization and auto-promotions, and finally outputs a detailed statistical report.


Key Features

- Event-Driven Simulation: Processes arrival, cancellation, and promotion events dynamically at specific timesteps.
- Priority Queue Management: VIP orders and in-service orders are managed using custom priority queues based on order value and finish times.
- Auto-Promotion System: Normal orders that exceed a predefined waiting time limit are automatically promoted to VIP status to ensure service quality.
- Chef State Management: Tracks chef availability across multiple states (Available, In-Service, On Break, In Emergency).
- Dynamic Emergency Handling: Simulates health emergencies where chefs become unavailable, temporarily halting their active orders and returning them to the waiting list. Recovering chefs return with a 50% speed reduction.
- Dual Simulation Modes: Supports an Interactive mode (printing timestep-by-timestep status requiring user input to proceed) and a Silent mode (running the entire simulation instantly and outputting the final file).
- Comprehensive File I/O: Parses complex configuration files for initial setup and generates detailed output reports with average wait times, service times, and order distributions.


Custom Data Structures Implemented

To handle the restaurant logic efficiently, the following ADTs were built from scratch:

1. LinkedQueue
Used for standard First-In-First-Out (FIFO) processing. It manages the waiting Normal and Vegan orders, as well as the queues for available Normal, Vegan, and VIP chefs.

2. priQueue (Priority Queue)
Used for elements that require sorting by a specific metric. 
- Waiting VIP Orders: Prioritized by order money and waiting time.
- In-Service Orders: Prioritized by nearest finish time.
- Chefs on Break / In Emergency: Prioritized by remaining break or recovery time.

3. waitNorm (Custom Linked List)
A specialized linked list for the waiting Normal orders. Because Normal orders can be cancelled or promoted mid-queue, this structure allows for searching and removing specific nodes by Order ID, which a standard queue cannot do.

4. ArrayStack
Used to store completed orders (Done List) in a Last-In-First-Out manner. This allows the system to efficiently pop orders when generating the final output file.

5. Node and priNode
The foundational building blocks for the linked lists and priority queues, managing pointers to subsequent elements and carrying priority weights.


Simulation Workflow

1. Initialization: The system loads chef configurations (speeds, break durations, orders before break) and a list of events from an input file.
2. Event Processing: At each timestep, the system dequeues and executes events scheduled for that time (Arrivals, Cancellations, Promotions, Emergencies).
3. Auto-Promotion Check: The system scans the normal waiting list. Any order waiting longer than the auto-promotion limit is moved to the VIP priority queue.
4. Order Assignment: The system attempts to assign waiting orders to available chefs. VIP orders are assigned first, followed by Normal, then Vegan. VIP chefs can serve Normal orders if necessary.
5. Completion & Breaks: Orders that reach their finish time are moved to the Done stack. Their assigned chefs either return to the available pool or are sent to the break queue if they hit their order quota.
6. Emergency Processing: Chefs in emergency states have their recovery time decremented. Once recovered, they return to their respective available queues with a reduced speed.
7. Termination: The simulation runs until all events are processed and all waiting/in-service queues are empty. The system then generates the final output file.


How to Compile and Run

Prerequisites
- A C++ compiler (MSVC recommended as the project includes Visual Studio files).
- Windows OS (if using the provided Visual Studio project files).

Installation and Execution
1. Clone the repository.
2. Open the Restaurant_Management_System.vcxproj file in Visual Studio.
3. Build the solution.
4. Ensure the input file (e.g., Text6.txt or input.txt) is in the same directory as the executable.
5. Run the executable. The program will prompt you to select a simulation mode (Interactive or Silent).
6. Upon completion, check the generated output file (interactive_output.txt or projectID_output.txt) for the final simulation statistics.


Developed by Mennatullah Mahmoud (https://github.com/mennatullahmahmoud06-del) as a university project demonstrating advanced C++, data structures, and Object-Oriented Design.
