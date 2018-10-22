#include <iostream>
#include <string>
#include <ostream>
#include <fstream>
#include <cstdlib>
#include <sstream>
#include <time.h>
#include <numeric>
#include "dsvector.hpp"
#include "page.h"
using namespace std;
#ifndef DRIVER_H
#define DRIVER_H

class Driver
{
private:
string inputFile;
string outputFile;
string contextOfBook;
DSvector<int> abVector; //Angle brackets position vector 
DSvector<Page> pageVector;
DSvector<string> contentVector;
DSvector<string> allWords;
DSvector<int> pageNoVector;
DSvector<char> alphabet;
public:
    Driver(string input, string out);		//CONSTRUCTOR
	void setPageNoVector();					//Push page number onto pageNo vector
	void setContentVector();				//Push content associate with page number onto content vector
	void setAlphabetVector();				//Push a-z on alphabet vector
	void setAllWordsVector();				//Store all the words exist on to vector
	string displayResult();					//Display result
	void run();								//run everything
};

#endif // DRIVER_H
