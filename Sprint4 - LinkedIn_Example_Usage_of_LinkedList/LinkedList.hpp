#ifndef LinkedList_H
#define LinkedList_H
#include "Node.h"
#include <iostream>
using namespace std;
template <class T>
class LinkedList
{
private:
	int size = 0;
	Node<T> * head;
	Node<T> * tail;
	Node<T> * current = head;//iterator for back-tracking

public:
	LinkedList();							//CONSTRUCTOR
	~LinkedList();							//DESTRUCTOR
	LinkedList(const LinkedList<T> &object);//COPY CONSTRUCTOR

	bool isEmpty();							//Indicate whether or not list is empty
	int getSize() const;					//Get size of the list
	T front() const;						//Access first element 
	T back() const;							//Access last element
	void push_front(T val);					//Add element at the front
	T pop_front();							//Delete first element
	void push_back(T val);					//Add element at the end
	T pop_back();							//Delete last element
	T at(int pos);							//Get element at index pos
	void insertAt(int pos, T val);			//Insert element at specific index
	void swap(int pos1, int pos2);			//Swap content of two nodes
	void removeAt(int pos);					//Remove element at specific index
	void remove(T val);						//Remove elements with specific value
	void next();							//Step iterator
	void resetIter();						//Reset iterator
	T get() const;							//Get data at (current) iterator
	Node<T> * getCurrent();					//get Current pointer
	void setSize(int s);					//set size for linkedList
	void sort();							//Sort elements in the list
	void print();							//Print element in list (only applies for int and string type)

	T& operator[](int index);				//return node at specific index
	bool operator ==(const LinkedList<T> &);	//Compare two lists
	LinkedList<T> & operator=(const LinkedList<T> &);	//Assignment operator (same as copy constructor)
};

template <class T>
LinkedList<T>::LinkedList() 
{
	this->size = 0;
	head = nullptr;
	tail = nullptr;
	current = nullptr;
}

template <class T>
LinkedList<T>::LinkedList(const LinkedList<T> &object) 
{
	Node<T> * temp = object.head;
	while(temp != nullptr)
	{
		push_back(temp->data);
		temp = temp->nextPtr;
	}
}

template <class T>
LinkedList<T>::~LinkedList() {
	if (!isEmpty())
	{ // List is not empty
		Node<T> * currentPtr = head;
		Node<T> * tempPtr = nullptr;

		while (currentPtr != nullptr)
		{ //delete remaining nodes
			tempPtr = currentPtr;
			currentPtr = currentPtr->nextPtr;
			delete tempPtr;
		}
	}

}


template <class T>
bool LinkedList<T>::isEmpty()
{
	bool value = false;
	if (size == 0)
	{
		value = true;
		return value;
	}
	return value;
}

template <class T>
int LinkedList<T>::getSize() const
{
	return this->size;
}

template <class T>
T LinkedList<T>::front() const
{
	return head->data;
}

template <class T>
T LinkedList<T>::back() const
{
	return tail->data;
}

template <class T>
void LinkedList<T>::push_front(T val)
{
	Node<T> * newNode = new Node<T>(val);
	this->size++;
	if (isEmpty())// List is empty
		this->head = this->tail = newNode;// new list has only one node

	else // List is not empty
	{
		newNode->nextPtr = this->head;		// point temp node to old 1st node
		this->head->prevPtr = newNode;
		this->head = newNode;				// aim head at new node
	}
}

template <class T>
T LinkedList<T>::pop_front()
{
	if (isEmpty())
	{
		cout << "List is empty!!\n";
		return 0;
	}
	else
	{// List has one element
		Node<T> * temp = head; //hold item to delete
		if (head == tail)	
			head = tail = nullptr; //no nodes remain after removal
		else
		{
			head = head->nextPtr; //point to previous 2nd node
			head->prevPtr = nullptr;
		}
		T tempData = temp->data;
		delete temp; //reclaim previous front node
		this->size--;
		return tempData;
	}
}

template <class T>
void LinkedList<T>::push_back(T val)
{
	Node<T> * newNode = new Node<T>(val);
	if (isEmpty())
	{// List is empty
		head = newNode;	// new list has only one 
		tail = newNode;
		current = newNode;
		this->size++;
	}
	else
	{// List is not empty
		tail->nextPtr = newNode;// update previous last node
		newNode->prevPtr = tail;// new node points to last node
		tail = newNode;// new tail
		current = head;
		this->size++;
	}
}

template <class T>
T LinkedList<T>::pop_back()
{
	if (isEmpty())// List is empty
	{
		cout << "List is empty!!\n";
		return 0;
	}
	else
	{
		Node<T> * temp = tail;// hold item to delete
		
		if (head == tail)
		// List has one element
			head = tail = nullptr; // no nodes remain after removal

		else
		{
			tail = tail->prevPtr; //new tail points to the second to last element
			tail->nextPtr = nullptr; //this is now the last node
		}
		this->size--;
		T tempData = temp->data;
		delete temp;
		return tempData;
	}
}

template <class T>
T LinkedList<T>::at(int pos)
{
	if (pos < size && pos >= 0)
	{
		Node<T> * temp1 = head;
		for (int i = 0; i < pos; i++)//get element at pos
			temp1 = temp1->nextPtr;
		return temp1->data;
	}
	else
		throw out_of_range("Out Of Bound!!");
}

template <class T>
void LinkedList<T>::insertAt(int pos, T val)
{
	Node<T> * curr = head;
	while (curr->nextPtr != nullptr && pos > 0)
	{
		curr = curr->nextPtr;
		pos--;
	}

	if (curr == head)
		push_front(val);
	else if (curr == tail)
		push_back(val);
	else
	{
		Node<T> * temp = new Node<T>(val);
		temp->prevPtr = curr;
		temp->nextPtr = curr->nextPtr;
		curr->nextPtr->prevPtr = temp;
		curr->nextPtr = temp;
	}
	this->size++;
}

template <class T>
void LinkedList<T>::swap(int pos1, int pos2)
{
	if (pos1 < size && pos2 < size)
	{//If indexes are valid
		Node<T> * temp1 = head;
		Node<T> * temp2 = head;
		T tempData;
		for (int i = 0; i < pos1; i++)//get element at pos1
			temp1 = temp1->nextPtr;
		for (int i = 0; i < pos2; i++)//get element at pos2
			temp2 = temp2->nextPtr;

		//Swap content
		tempData = temp1->data;
		temp1->data = temp2->data;
		temp2->data = tempData;
	}
	else
		cout << "Invalid index!!\n";
}

template <class T>
void LinkedList<T>::removeAt(int pos)
{
	if(isEmpty())
		//List is empty
		cout << "List is empty!!\n";

	else
	{
		if (pos < size && pos >= 0)
		{//Valid index
			Node<T> * temp = head;
			for (int i = 0; i < pos; i++)//get element at index pos
				temp = temp->nextPtr;

			temp->prevPtr->nextPtr = temp->nextPtr;//connect two nearby elements
			temp->nextPtr->prevPtr = temp->prevPtr;

			delete temp;//Remove node at index pos
			this->size--;
		}
		else
			cout << "Invalid index!!\n";
	}
}

template <class T>
void LinkedList<T>::remove(T val)
{
	if (isEmpty())
		//List is empty
		cout << "List is empty!!\n";

	else
	{
		Node<T> * curr = head;
		while (curr->nextPtr != nullptr)
		{
			if (curr->data == val)
			{//Node with value of val found
				curr->prevPtr->nextPtr = curr->nextPtr;//connect two nearby elements
				curr->nextPtr->prevPtr = curr->prevPtr;

				delete curr;//Remove node at index pos
				this->size--;
				break;
			}
			else
				curr = curr->nextPtr;
		}
	}
}

template <class T>
void LinkedList<T>::next()
{
	if (current == nullptr)
		throw out_of_range("Out Of Bound!!");
	if (current->nextPtr == nullptr)
		current = nullptr;
	else
		current = current->nextPtr;
}

template <class T>
void LinkedList<T>::resetIter()
{
	current = head;
}

template <class T>
T LinkedList<T>::get() const
{
	return current->data;
}

template <class T>
Node<T> * LinkedList<T>::getCurrent()
{
	return current;
}

template <class T>
void LinkedList<T>::setSize(int s)
{
	this->size = s;
}
template <class T>
void LinkedList<T>::sort()
{}

template <class T>
void LinkedList<T>::print()
{
	Node<T> * curr = this->head;
	while (curr)
	{//iterate through the list and print out data in each node
		cout << curr->data << " ";
		curr = curr->nextPtr;
	}
}
template <class T>
T& LinkedList<T>::operator[](int index)
{
	if (index < size && index >= 0)
	{
		Node<T> * temp = head;
		for (int i = 0; i < index; i++)//get element at pos
			temp = temp->nextPtr;
		return temp->data;//return node
	}
	else
		throw out_of_range("Out Of Bound!!");
}

template <class T>
bool LinkedList<T>::operator==(const LinkedList<T> & object)
{
	bool value = false;
	if (this->size == object.size)
	{//size is the same
		Node<T> * temp1 = head; //LHS object
		Node<T> * temp2 = object.head; //RHS object
		for (int i = 0; i < size; i++)
		{
			if (temp1->data == temp2->data)
			{//if content is the same, keep iterating through the list
				temp1 = temp1->nextPtr;
				temp2 = temp2->nextPtr;
			}
			else
				return value;
		}
		//return true because content of both lists are the same
		value = true;
		return value;
	}
	else //size is not the same
		return value;
}

template <class T>
LinkedList<T> &LinkedList<T>::operator=(const LinkedList<T> &object)
{
	Node<T> * temp = object.head;
	while (temp != nullptr)//get element at pos
	{
		push_back(temp->data);
		temp = temp->nextPtr;
	}
	return *this;
}
#endif
