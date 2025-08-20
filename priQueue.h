#pragma once
#include <iostream> 
#include "priNode.h"


//This class impelements the priority queue as a sorted list (Linked List)
//The item with highest priority is at the front of the queue
template <typename T>
class priQueue
{
    priNode<T>* head;
public:
    priQueue() : head(nullptr) {}

    ~priQueue() {
        T tmp;
        int p;
        while (dequeue(tmp, p));
    }

    //insert the new node in its correct position according to its priority
    void enqueue(const T& data, int priority) {
        priNode<T>* newNode = new priNode<T>(data, priority);

        if (head == nullptr || priority > head->getPri()) {

            newNode->setNext(head);
            head = newNode;
            return;
        }

        priNode<T>* current = head;
        while (current->getNext() && priority <= current->getNext()->getPri()) {
            current = current->getNext();
        }
        newNode->setNext(current->getNext());
        current->setNext(newNode);
    }

    bool dequeue(T& topEntry, int& pri) {
        if (isEmpty())
            return false;

        topEntry = head->getItem(pri);
        priNode<T>* temp = head;
        head = head->getNext();
        delete temp;
        return true;
    }

    bool peek(T& topEntry, int& pri) {
        if (isEmpty())
            return false;

        pri = head->getPri();          
        topEntry = head->getItem(pri);  
        return true;
    }

    bool isEmpty() const {
        return head == nullptr;
    }

    int count() const
    {
        priNode<T>* curr = head;
        int count = 0;
        while (curr) {
            count++;
            curr = curr->getNext();
        }
        return count;
    

    }


    void print() const
    {
        priNode<T>* curr = head;
        while (curr) {
            std::cout << "[P:" << curr->getPri() << "] " << curr->getItem() << " ";
            curr = curr->getNext();
        }
        std::cout << std::endl;



    }

  
    void printIDs() const {
        priNode<T>* curr = head;
        bool first = true;
        while (curr) {
            if (!first) std::cout << ", ";
            int pri=curr->getPri();
            std::cout << curr->getItem(pri)->getID();
            curr = curr->getNext();
            first = false;
        }
        std::cout << std::endl;
    }



};
