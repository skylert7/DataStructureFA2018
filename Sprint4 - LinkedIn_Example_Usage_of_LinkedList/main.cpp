#define CATCH_CONFIG_RUNNER
#include "catch.hpp"
#include "Driver.h"


using namespace std;

int main(int argc, char *argv[])
{
    if (strcmp(argv[1], "-t") == 0)
    {
        Catch::Session().run();
    }
    else if (strcmp(argv[1], "-r") == 0)
    {
        Driver driver = Driver(argv[2], argv[3], argv[4]);
        driver.run();
    }
    return 0;
}
