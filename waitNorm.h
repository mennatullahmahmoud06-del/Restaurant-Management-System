#pragma once
#include "LinkedQueue.h"
#include "Order.h"
template <typename T>
class waitNorm :public LinkedQueue <T>
{
public:
    bool cancelOrder(int ID) {
        Node<T>* current = this->frontPtr;
        Node<T>* prev = nullptr;

        while (current != nullptr) {
            T item = current->getItem();
            if (item->getID() == ID) {
                if (prev == nullptr) {
                    // Removing the first node
                    T X;
                    this->dequeue(X);
                }
                else {
                    // Removing a middle or last node
                    prev->setNext(current->getNext());

                    if (current == this->backPtr)
                        this->backPtr = prev;

                    delete current;
                }
                return true;
            }

            // FIXED: Move these lines inside the while loop but outside the if block
            prev = current;
            current = current->getNext();
        }

        return false; // Order not found
    }

    T getOrder(int ID) {
        Node<T>* current = this->frontPtr;
        while (current != nullptr) {
            T orderPtr = current->getItem();
            if (orderPtr->getID() == ID)
                return orderPtr;
            current = current->getNext();
        }
        return nullptr;
    }

    int getcount() const {
        return this->getCount();
    }
};