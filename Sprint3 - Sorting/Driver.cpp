#include "Driver.h"

using namespace std;

unsigned int maxSizeOfString = 30; //maximum length a string can be
unsigned int numOfElement = 0; //number of words in file
unsigned int elementsToDisplay = 0; //number of elements to Display to screen

Driver::Driver(string input, string output)
{
    this->input = input;
    this->output = output;
}

unsigned int a;
int b;
int Driver::partition(DSvector<string>& stringVector, int start, int end)
{
    //choose pivot pos
    int pivotInt = int((start + end)/2);

    stringVector.swap(pivotInt, start);
    string pivot = stringVector[start];

    a = start;
    b = end;

    int i = start;  //Iterate from start to end
    while(i <= b)
    {
        if(stringVector[i] < pivot)
        {
            stringVector.swap(a, i);
            a++;
            i++;
        }
        else if(stringVector[i] > pivot)
        {
            stringVector.swap(b, i);
            b--;
        }
        else if(stringVector[i] == pivot)
            i++;
    }
}

void Driver::quickSort(DSvector<string> & stringVector, int start, int end)
{
    if (start < end)
    {
        //Three way partition
        partition(stringVector, start, end);

        //Sort set S1 on the left hand side
        quickSort(stringVector, start, a - 1);
        //Sort set S2 on the right hand side
        quickSort(stringVector, b + 1, end);
    }
}

void Driver::bucketSort(DSvector<string>& stringVector)
{
    //Store strings with same length into each bucket
    for (unsigned int i = maxSizeOfString + elementsToDisplay + 1; i < stringVector.size(); i++)
    {
        string str = stringVector[i];
        stringVector[str.length() - 1].append(str);
        //bucket with length of string in each bucket
    }

    unsigned int count2 = 0;//count
    unsigned int index = 0;//index in string vector
    unsigned int j = maxSizeOfString + 1;//index to start store elements to display

    while (index < maxSizeOfString)
    {
        DSvector<string> localStringVector;
        string giantStr = stringVector[index];//This is string consisting of all words that have same length
        string element;
        stringstream ss(giantStr);

        while (ss.good())
        {

            getline(ss, element, '\n');
            if(element != "")
                localStringVector.push_back(element);
        }
        //Call quickSort on each individual bucket
        quickSort(localStringVector, 0, localStringVector.size() - 1);

        //Assign sorted vector to index for elements to display on original vector
        for (unsigned int i = 0; i < localStringVector.size(); i++)
        {
            count2++;
            stringVector[j] = localStringVector[i];
            j++;
            //Only sort and extract enough to display to screen
            if (count2 >= elementsToDisplay)
                goto finish;
        }
        index++;
    }
finish:
    cout << "";
}

void Driver::run()
{
    ifstream inFile(input);
    ofstream outFile(output);

    //Read in the ENTIRE file at once
    string entireFile((istreambuf_iterator<char>(inFile)),
               istreambuf_iterator<char>());
    string element;
    stringstream ss(entireFile);

    maxSizeOfString = 30;

    //Number of total words
    getline(ss, element, '\n');
    numOfElement = stoi(element);

    //Number of words to display
    getline(ss, element, '\n');
    elementsToDisplay = stoi(element);

    //Dynamically allocate vector before performing anything
    unsigned int totalSize = numOfElement + maxSizeOfString + elementsToDisplay + 1;
    DSvector<string> stringVector(totalSize);

    //Allocate space for buckets
    for (unsigned int i = 0; i <= maxSizeOfString + elementsToDisplay; i++)
        stringVector.push_back("");

    element = "";

    //Get all words in file to vector
    while (ss.good())
    {
        getline(ss, element, '\n');
        element += "\n";
        stringVector.push_back(element);
    }

    /*
    *
    *Quick Sort
    *If data is larger than 1002 elements
    *
    */
    bucketSort(stringVector);
    for (unsigned int i = maxSizeOfString + 1; i < maxSizeOfString + 1 + elementsToDisplay; i++)
    {
        outFile << stringVector[i];
        outFile << "\n";
    }
}
