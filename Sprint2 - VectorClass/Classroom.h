/*
*
*	This is just a user-defined type class to test 
*	functions in testCases.cpp for Catch
*
*/
#include <iostream>
#include <string>
#include "dsvector.hpp"
using namespace std;
#ifndef CLASSROOM_H
#define CLASSROOM_H
class Classroom 
{
private:
	int desks;
	int chairs;
	string nameOfRoom;
public:
	Classroom();
	Classroom(int, int, string);
	//Classroom(Classroom &);

	int getChairs();
	int getDesks();
	string getRoomName();
	Classroom &operator=(const Classroom&);
	bool operator==(const Classroom&);

};
#endif // Classroom
