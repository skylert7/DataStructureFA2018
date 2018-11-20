#ifndef Node_H
#define Node_H
#include <cstdlib>
#include <iostream>
#include <exception>
#include <stdexcept> 
template<class T>
class Node {
	template<class U> friend class LinkedList; // make List a friend

public:
	explicit Node(const T& val) // constructor
	{
		data = val;
		prevPtr = nullptr;
		nextPtr = nullptr;
	}

	T getData() const
	{
		return data;
	} // return data in node

private:
	T data; // data
	Node<T> * nextPtr; // next node in list
    Node<T> * prevPtr; // previous node in list
};

#endif
