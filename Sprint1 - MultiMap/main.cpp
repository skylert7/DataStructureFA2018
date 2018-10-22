#include <iostream>
#include <string>
#include <ostream>
#include <fstream>
#include <list>
#include <cstdlib>
#include <vector>
#include <sstream>
#include <time.h>
#include "Driver.h"
using namespace std;


int main(int argc, char *argv[])
{
    Driver driver = Driver(argv[1], argv[2], argv[3]);
    driver.run();
	return 0;
}



