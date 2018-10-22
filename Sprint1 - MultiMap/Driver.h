#include <iostream>
#include <string>
#include <ostream>
#include <fstream>
#include <list>
#include <cstdlib>
#include <vector>
#include <sstream>
#include <time.h>
#include "userRecord.h"
#include <map>
#include <algorithm>
#ifndef Driver_H
#define Driver_H
using namespace std;

class Driver
{
private:
    string csvFile;
    string textFile;
    string outFile;
public:
	string getUserName2nd(string line);
	vector<string> getTypeOfWord(string line);
	vector<string> getWordFromRecord(string userName2nd, vector<string> typeOfWordVector);
	string appendLineForMadLibs(string line, vector<string> word);
	int getPositiveTweet();
	int getNegativeTweet();
	double getAvgWordPerPositive();
	double getAvgWordPerNegative();
	string displayTopThreeNeg();
	string displayTopThreePos();
	void run();
    Driver(string csvFile, string textFile, string outFile);
	Driver();
};
#endif



