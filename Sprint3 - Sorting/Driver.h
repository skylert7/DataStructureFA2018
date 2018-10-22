#include <iostream>
#include <string>
#include <ostream>
#include <fstream>
#include <cstdlib>
#include <sstream>
#include <time.h>
#include <numeric>
#include <stdio.h>
#include <vector>
#include <stdlib.h>
#include "dsvector.hpp"
using namespace std;
#ifndef DRIVER_H
#define DRIVER_H

class Driver
{
private:
    string input, output;
    unsigned int elementsToDisplay;
public:
    Driver(string input, string out);		//CONSTRUCTOR
    int partition(DSvector<string>& stringVector, int start, int end);
    void quickSort(DSvector<string>& stringVector,  int start,  int end);//Quicksort
    void bucketSort(DSvector<string>& stringVector);//Bucket with quickSort inside
    void run();								//run everything
};

#endif // DRIVER_H
#pragma once
