#include <iostream>
#include <string>
#include <ostream>
#include <fstream>
#include <list>
#include <cstdlib>
#include <vector>
#include <map>
#include <sstream>
#ifndef UserRecord_H
#define UserRecord_H
using namespace std;

class UserRecord {
private: 
	string tuple;
	char target;
	string ID;
	string tweet;
	string userName;
	multimap<string, string> myMap;
public:
	UserRecord();
	UserRecord(string tweet);
	UserRecord(const UserRecord &object);
	void makeMap();
	void splitComponents();
	char  getTarget();
	string  getID();
	multimap<string, string>getmyMap();
	void displayMap();
	string getUserName();
	string  getTuple();
	string  getTweet();
};
#endif


