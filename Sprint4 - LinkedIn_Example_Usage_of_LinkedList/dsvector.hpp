#ifndef DSVECTOR_H
#define DSVECTOR_H
#include <cstdlib>
#include <iostream>
#include <exception>
#include <stdexcept>

using namespace std;
template<class T>
class DSvector
{
private:
    T* data;
    int sizeOfVector;
    int my_capacity;
public:    

    typedef T * iter;                       //Future Purpose

    DSvector();                             //DEFAULT CONSTRUCTOR
    DSvector(int size);                     //CONSTRUCTOR WITH SIZE
    DSvector(const DSvector<T> &object);    //COPY CONSTRUCTOR
    ~DSvector();                            //DESTRUCTOR

    int capacity() const;                   //Get capacity of vector
    int size() const;                       //Get size of vector

    T at(int index);                        //Get element at specific index
    bool isEmpty();                         //Check if the vector is empty
    T & front();                            //Get the first element
    T & back();                             //Get the last element
    void resize();                          //Increase the capacity of vector
    void push_back(const T &object);        //Insert element to the back of the vector
    void pop_back();                        //Delete the last element of the vector
    void erase(int index);                  //Erase element in specific index
    void swap(int index1, int index2);      //Swap 2 elements between two different indexes
	void sort();							//Sort element alphabetically (Ascending order)
	void print();                           //Print element of the vector (ONLY WORKS ON PRIMITIVE TYPE)

    T &operator[](int index);               //Get reference of element of specific index
    bool operator!=(const DSvector<T> &);   //Check for inequality
    bool operator==(const DSvector<T> &);   //Check for equality
    DSvector<T> & operator=(const DSvector<T> &);//Assignment operator (same as copy constructor)
	DSvector<T> & clone(const DSvector<T> & source);

};

template<class T>
DSvector<T>::DSvector()
{
    sizeOfVector = 0;
    my_capacity = 10;
    this->data = new T[my_capacity];
}

template<class T>
//CONSTRUCTOR
DSvector<T>::DSvector(int size)
{
    sizeOfVector = size;
    if(size > 0)
        my_capacity = size * 2;
    else
        my_capacity = 10;
    this->data = new T[my_capacity];
}

template<class T>
DSvector<T>::DSvector(const DSvector<T> &object)
{
    //Deallocate existing memory
//    if(sizeOfVector > 0)
//        delete [] data;
    this->data = new T[object.capacity()];
    this->sizeOfVector = object.size();
    this->my_capacity = object.capacity();
    for(int i = 0; i < object.size(); i++)
        this->data[i] = object.data[i];
}

template<class T>
DSvector<T>::~DSvector()
{
        delete [] this->data;
}

template<class T>
int DSvector<T>::capacity() const
{
    return my_capacity;
}

template<class T>
T DSvector<T>:: at(int index)
{
    //Check if index is valid
    if(index > sizeOfVector - 1)
        throw out_of_range("Out Of Bound!!");
    else
        return this->data[index];
}

template<class T>
bool DSvector<T>::isEmpty()
{
    bool boolean = false;
    if(sizeOfVector == 0)
        boolean = true;
    return boolean;
}

template<class T>
T & DSvector<T>::front()
{
    if(sizeOfVector > 0)
        return this->data[0];
    else
        throw logic_error("Vector is empty.\n");
}

template<class T>
T & DSvector<T>::back()
{
    if(sizeOfVector > 0)
        return this->data[sizeOfVector - 1];
    else
        throw logic_error("Vector is empty.\n");
}

template<class T>
void DSvector<T>::resize()
{
    my_capacity *= 2;
    T* dataCopy = new T[my_capacity];
    for(int i = 0; i < sizeOfVector; i++)
        dataCopy[i] = this->data[i];
    //delete existing memory
    delete[] this->data;
    //Create a copy so that two pointers would point to the same object
    this->data = dataCopy;
}

template<class T>
void DSvector<T>::push_back(const T &object)
{
    if(sizeOfVector == my_capacity)
        resize();
    //Push object to the back of the vector
    sizeOfVector++;
    this->data[sizeOfVector-1] = object;
}

template<class T>
void DSvector<T>::pop_back()
{
    erase(sizeOfVector-1);
}

template<class T>
void DSvector<T>::erase(int index)
{
    //Check if index is valid
	if (index > sizeOfVector - 1)
		throw logic_error("Out Of Range.\n");
	else if (sizeOfVector == 0)
		sizeOfVector = 0;
    else if (sizeOfVector > 0)
    {
        for(int i = index; i < sizeOfVector; i++)
        {
            if(i != (sizeOfVector - 1))
                this->data[i] = this->data[i+1];
        }
        this->sizeOfVector--;
    }
}

template<class T>
void DSvector<T>::swap(int index1, int index2)
{
    T dummy;
    //Check to see if two elements exist
    if(index1 > sizeOfVector - 1 || index2 > sizeOfVector - 1)
        throw out_of_range("Out Of Range.\n");
    else
    {
        dummy = this->data[index1];
        this->data[index1] = this->data[index2];
        this->data[index2] = dummy;
    }
}

template<class T>
void DSvector<T>::sort()
{
	//Insertion Sort
	int i, j;
	T key;
	for (i = 1; i < sizeOfVector; i++)
	{
		key = data[i];
		j = i - 1;
		while (j >= 0 && data[j] > key)
		{
			data[j + 1] = data[j];
			j = j - 1;
		}
		data[j + 1] = key;
	}
}

template<class T>
int DSvector<T>::size() const
{
    return this->sizeOfVector;
}

template<class T>
void DSvector<T>::print()
{
    for(int i = 0; i < sizeOfVector; i++)
        cout << this->data[i] << "\n";
}

template<class T>
T &DSvector<T>::operator[](int index)
{
    if(index > sizeOfVector - 1)
        throw out_of_range("Out Of Range.\n");
    else
        return this->data[index];
}

template<class T>
bool DSvector<T>::operator!=(const DSvector<T> &object)
{
    int count = 0;
    bool boolean = true;
    if(sizeOfVector == object.sizeOfVector)
    {
        for(int i = 0; i < sizeOfVector; i++)
        {
            if(this->data[i] == object.data[i])
                count++;
        }
        if(count == sizeOfVector)
            boolean = false;
    }
    return boolean;
}

template<class T>
bool DSvector<T>::operator==(const DSvector<T> &object)
{
    bool boolean = false;
    if(sizeOfVector == object.sizeOfVector)
    {
        for(int i = 0; i < sizeOfVector; i++)
        {
            if(this->data[i] == object.data[i])
                boolean = true;
        }
    }
    return boolean;
}

template<class T>
DSvector<T> &DSvector<T>::operator=(const DSvector<T> &object)
{
	if (&object == this)
		return *this;
    //Deallocate existing memory
    delete [] data;
	//Start copying
    this->data = new T[object.capacity()];
    this->sizeOfVector = object.size();
    this->my_capacity = object.capacity();
    for(int i = 0; i < object.size(); i++)
    {
        this->data[i] = object.data[i];
    }
    return *this;
}

template<class T>
DSvector<T>& DSvector<T>::clone(const DSvector<T> &source)
{
	DSvector<T>copy(*this);
	return copy;
}
#endif // DSVECTOR_H


