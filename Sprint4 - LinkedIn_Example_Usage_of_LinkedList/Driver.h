#include "LinkedList.hpp"
#include "AdjList.hpp"
#include "Stack.hpp"
#include "dsvector.hpp"
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

using namespace std;
#ifndef DRIVER_H
#define DRIVER_H

class Driver
{
private:
    string connection;//inputFile 1
    string requestConnect;//inputFile 2
    string outputFile;//outputFile
public:
    Driver(string input, string input2, string output);	//CONSTRUCTOR
	void run();									//run everything
};
#endif
