#include "LinkedList.hpp"

using namespace std;

template<class T>
class AdjList
{
private:
	LinkedList<LinkedList<T>> content;

public: 
    AdjList();                                      //CONSTRUCTOR
    void insert(LinkedList<T>& val);                //insert a big LinkedList
    void insertWhereFirstEquals(T val, T toInsert); //insert toInsert to a LinkedList where first value of specific LinkedList = val
    LinkedList<T>& findFirst(T val);                //return LinkedList where first value = val
    LinkedList<LinkedList<T>>& getMem();            //get private member: LinkedList of LinkedList
};

template <class T>
AdjList<T>::AdjList()
{
    content.setSize(0);
}

template <class T>
void AdjList<T>::insert(LinkedList<T>& val)
{
    content.push_back(val);
}

template <class T>
void AdjList<T>::insertWhereFirstEquals(T val, T toInsert)
{//insert toInsert to a LinkedList where first value of specific LinkedList = val
    for (int i = 0; i < content.getSize(); i++)
    {
        if (content[i][0] == val)
        {
            content[i].push_back(toInsert);
        }
    }
}

template <class T>
LinkedList<T>& AdjList<T>::findFirst(T val)
{//return LinkedList where first value = val
    int index = 0;
    for (int i = 0; i < content.getSize(); i++)
        if (content[i][0] == val)
            return content[i];
    cout << "Name is not valid!! DNE!!\n";
    return content[0];
}

template <class T>
LinkedList<LinkedList<T>>& AdjList<T>::getMem()
{
    return content;
}
