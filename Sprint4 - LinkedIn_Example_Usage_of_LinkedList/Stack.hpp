#include "LinkedList.hpp"

using namespace std;

template <class T>
class Stack
{
private:
	LinkedList<T> stack;
public:
    Stack();                    //CONSTRUCTOR
    void push(T val);           //Push value onto stack
    T pop();                    //Pop the top of stack
    bool isEmpty();             //Check to see if stack is empty or not
    T peek();                   //Get element at top of the stack
    T bottom();                 //Get element at bottom of the stack
    void print();               //Print stack
    bool notOnStack(T val);     //Check to see if val is on stack or not, return true if val not on stack
    void clear();               //Clear stack
    int getSize() const;        //Get size of stack
};

template<class T>
Stack<T>::Stack() {}

template<class T>
void Stack<T>::push(T val)
{
    stack.push_back(val);
}	//push to the end with val

template<class T>
T Stack<T>::pop()
{
    return stack.pop_back();
}//remove element at the top of the stack


template<class T>
bool Stack<T>::isEmpty()
{
    return stack.isEmpty();
}	//return true if stack is empty

template<class T>
T Stack<T>::peek()
{
    if (!isEmpty())
        return stack.at(stack.getSize() - 1);
    else
        throw out_of_range("Stack is empty!!!");
}

template<class T>
T Stack<T>::bottom()
{//Get bottom of the stack
    if (!isEmpty())
        return stack.at(0);
    throw out_of_range("Stack is empty!!!");
}

template<class T>
void Stack<T>::print()
{
    stack.print();
}

template<class T>
bool Stack<T>::notOnStack(T val)
{
    bool value = true;
    for (int i = 0; i < stack.getSize(); i++)
        if (val == stack[i])
            return false;
    return value;//return true if val is not on stack, false otherwise
}

template<class T>
void Stack<T>::clear()
{
    while (!stack.isEmpty())
        stack.pop_back();//Pop stack until stack is empty
}

template<class T>
int Stack<T>::getSize() const
{
    return stack.getSize();//return size of stack
}
