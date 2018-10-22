#include "Classroom.h"

Classroom::Classroom()
{
}
Classroom::Classroom(int d, int c, string n)
{
	this->desks = d;
	this->chairs = c;
	this->nameOfRoom = n;
}

//Classroom::Classroom(Classroom &object)
//{
//	this->desks = object.desks;
//	this->chairs = object.chairs;
//	this->nameOfRoom = object.nameOfRoom;
//}

int Classroom::getChairs()
{
	return this->chairs;
}
int Classroom::getDesks()
{
	return this -> desks;
}
string Classroom::getRoomName()
{
	return this->nameOfRoom;
}

Classroom& Classroom::operator=(const Classroom &object)
{
	this->desks = object.desks;
	this->chairs = object.chairs;
	this->nameOfRoom = object.nameOfRoom;
	return *this;
}

bool Classroom::operator==(const Classroom& object)
{
	bool boolean = false;
	if (&object.chairs == &this->chairs)
		if (&object.desks == &this->desks)
			if (&object.nameOfRoom == &this->nameOfRoom)
				boolean = true;
	return boolean;
}
