#pragma once
#ifndef _LINKEDLIST
#define _LINKEDLIST

#include "Node.h"
#include <iostream>
using namespace std;

template <typename T>
class LinkedList
{
private:
	Node<T>* Head;	//Pointer to the head of the list
	//You can add tail pointer too (depending on your problem)
public:


	LinkedList()
	{
		Head = nullptr;
	}

	//List is being desturcted ==> delete all items in the list
	~LinkedList()
	{
		DeleteAll();
	}

	/*
	* Function: PrintList.
	* prints the values of all nodes in a linked list.
	*/
	void PrintList()	const
	{
		cout << "\nprinting list contents:\n\n";
		Node<T>* p = Head;

		while (p)
		{
			cout << "[ " << p->getItem() << " ]";
			cout << "--->";
			p = p->getNext();
		}
		cout << "*\n";
	}

	/*
	* Function: InsertBeg.
	* Creates a new node and adds it to the beginning of a linked list.
	*
	* Parameters:
	*	- data : The value to be stored in the new node.
	*/
	void InsertBeg(const T& data)
	{
		Node<T>* R = new Node<T>(data);
		R->setNext(Head);
		Head = R;
	}

	/*
	* Function: DeleteAll.
	* Deletes all nodes of the list.
	*/
	void DeleteAll()
	{
		Node<T>* P = Head;
		while (Head)
		{
			P = Head->getNext();
			delete Head;
			Head = P;
		}
	}

	////////////////     Requirements   ///////////////////
	//
	// Implement the following member functions


	//[1]InsertEnd 
	//inserts a new node at end if the list
	void InsertEnd(const T& data) {
		Node<T>* newNode = new Node<T>(data);
		if (!Head) {
			Head = newNode;
			return ;
		}
		Node<T>* current = Head;
		while (current->getNext()) {
			current = current->getNext();
		}
		current->setNext(newNode);

	}

	//[2]Find 
	//searches for a given value in the list, returns true if found; false otherwise.
	bool Find(const T& value) const {
		Node<T>* current = Head;
		while (current) {
			if (current->getItem() == value)
				return true;
			current = current->getNext();
		}
		return false;
	}


	//[3]CountOccurance
	//returns how many times a certain value appeared in the list
	int CountOccurance(const T& value) const {
		int count = 0;
		Node<T>* current = Head;
		while (current) {
			if (current->getItem() == value)
				count++;
			current = current->getNext();
		}
		return count;
	}


	//[4] DeleteFirst
	//Deletes the first node in the list
	bool DeleteFirst() {
		if (!Head)
			return false;

		Node<T>* temp = Head;
		Head = Head->getNext();
		delete temp;
		return true;
	}


	//[5] DeleteLast
	//Deletes the last node in the list
	bool DeleteLast() {
		if (!Head)
			return false;

		if (!Head->getNext()) {
			delete Head;
			Head = nullptr;
			return true;
		}
		Node<T>* current = Head;
		while (current->getNext() && current->getNext()->getNext()) {
			current = current->getNext();
		}

		delete current->getNext();
		current->setNext(nullptr);
		return true;
	}



	//[6] DeleteNode
	//deletes the first node with the given value (if found) and returns true
	//if not found, returns false
	//Note: List is not sorted
	bool DeleteNode(const T& value) {
		if (!Head)
			return false;

		if (Head->getItem() == value)
			return DeleteFirst();

		Node<T>* current = Head;
		while (current->getNext()) {
			if (current->getNext()->getItem() == value) {
				Node<T>* toDelete = current->getNext();
				current->setNext(toDelete->getNext());
				delete toDelete;
				return true;
			}
			current = current->getNext();
		}

		return false;
	}


	//[7] DeleteNodes
	//deletes ALL node with the given value (if found) and returns true
	//if not found, returns false
	//Note: List is not sorted
	bool DeleteNodes(const T& value) {
		bool deleted = false;

		// Remove all matching nodes at the beginning
		while (Head && Head->getItem() == value) {
			DeleteFirst();
			deleted = true;
		}

		if (!Head)
			return deleted;

		Node<T>* current = Head;
		while (current->getNext()) {
			if (current->getNext()->getItem() == value) {
				Node<T>* toDelete = current->getNext();
				current->setNext(toDelete->getNext());
				delete toDelete;
				deleted = true;
			}
			else {
				current = current->getNext();
			}
		}

		return deleted;
	}


	//[8]Merge
	//Merges the current list to another list L by making the last Node in the current list 
	//point to the first Node in list L
	void Merge(LinkedList<T>& L) {
		if (!Head) {
			Head = L.Head;
			L.Head = nullptr;
			return;
		}

		Node<T>* current = Head;
		while (current->getNext()) {
			current = current->getNext();
		}

		current->setNext(L.Head);
		L.Head = nullptr;
	}
    //[9] Reverse
	//Reverses the linked list (without allocating any new Nodes)
	void Reverse() {
		if (!Head || !Head->getNext())
			return;

		Node<T>* prev = nullptr;
		Node<T>* current = Head;
		Node<T>* next = nullptr;

		while (current) {
			next = current->getNext();
			current->setNext(prev);
			prev = current;
			current = next;
		}

		Head = prev;
	}
};

#endif	
