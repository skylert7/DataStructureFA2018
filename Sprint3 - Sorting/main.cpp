#include "Driver.h"

using namespace std;

int main(int argc, char* argv[])
{
    Driver driver = Driver(argv[1], argv[2]);
    driver.run();
	return 0;
}
