//#define CATCH_CONFIG_MAIN  // This tells Catch to provide a main() - only do this in one cpp file
#include "catch.hpp"
#include "dsvector.hpp"
#include "Classroom.h"

TEST_CASE("string class") //If String vector works => char vector works too
{
  DSvector<string> stringVector;
  stringVector.push_back("Zero");
  stringVector.push_back("One");
  stringVector.push_back("Two");
  stringVector.push_back("Three");
  stringVector.push_back("Four");
  stringVector.push_back("Five");
  stringVector.push_back("Six");
  stringVector.push_back("Seven.");

  SECTION("COPY CONSTRUCTOR")
  {
      DSvector<string> stringVectorCopy(stringVector);
      REQUIRE(stringVectorCopy.capacity() == 10);
      REQUIRE(stringVectorCopy.size() == 8);
      REQUIRE_THROWS_AS(stringVectorCopy.at(20), out_of_range);
      REQUIRE(stringVectorCopy.capacity() == 10);
  }
  SECTION("Size")
  {
      REQUIRE(stringVector.size() == 8);
  }

  SECTION("Capacity")
  {
      REQUIRE(stringVector.capacity() == 10);
  }

  SECTION("isEmpty() Function")
  {
      REQUIRE(stringVector.isEmpty() == false);
  }

  SECTION("front() and back()")
  {
      //Check FRONT and BACK return value
      REQUIRE(stringVector.front() == "Zero");
      REQUIRE(stringVector.back() == "Seven.");
  }

  SECTION("resize() function")
  {
        stringVector.resize();
        stringVector.resize();
        stringVector.resize();
        //Check capacity, should be 80
        REQUIRE(stringVector.capacity() == 80);
  }

  SECTION("push_back() and check for size")
  {
      stringVector.push_back("I'm a");
        REQUIRE(stringVector.size() == 9);
      stringVector.push_back("human ");
        REQUIRE(stringVector.size() == 10);
      stringVector.push_back("being!");
        REQUIRE(stringVector.size() == 11);
  }

  SECTION("pop_back() and check for size")
  {
      REQUIRE(stringVector.size() == 8);
      REQUIRE(stringVector.capacity() == 10);

      stringVector.pop_back();
      stringVector.pop_back();
      stringVector.pop_back();

      REQUIRE(stringVector.size() == 5);
      REQUIRE_THROWS_AS(stringVector.at(6), out_of_range);
      REQUIRE(stringVector.capacity() == 10);
  }

  SECTION("erase() and swap()")
  {
      //Swap element at 3 and 6 and check
      stringVector.swap(3,6);
      REQUIRE(stringVector.at(3) == "Six");
      REQUIRE(stringVector.at(6) == "Three");

      //Erase element at index 4 which is "Four" and check
      stringVector.erase(4);
      REQUIRE(stringVector.at(4) == "Five");
  }

  SECTION("equality and inequality check")
  {
      DSvector<string> stringVectorCopy2(stringVector);

      REQUIRE((stringVectorCopy2 == stringVector) == true);

      DSvector<string> stringVectorCopy;
      stringVectorCopy.push_back("Zero");
      stringVectorCopy.push_back("One");
      stringVectorCopy.push_back("Two");

      REQUIRE((stringVectorCopy != stringVector) == true);
  }

  SECTION("operator[] and operator=")
  {
      stringVector[6] = "One Hundred";
      REQUIRE(stringVector[6] == "One Hundred");
      REQUIRE(stringVector[2] == "Two");

      DSvector<string> stringVector2, stringVector3;
      stringVector2.operator=(stringVector);
      stringVector3 = stringVector2;

      REQUIRE(stringVector2[3] == "Three");
      REQUIRE(stringVector2[7] == "Seven.");
      REQUIRE(stringVector3[1] == "One");
      REQUIRE(stringVector3[6] == "One Hundred");
      REQUIRE_THROWS_AS(stringVector2[16], out_of_range);
      REQUIRE_THROWS_AS(stringVector2[12], out_of_range);

	  stringVector3 = stringVector3;
	  REQUIRE(stringVector3[6] == "One Hundred");
	  //Print to check content - Correct
        //stringVector2.print();
        //stringVector3.print();
  }
}

TEST_CASE("int vector")         //integer vector
{
    DSvector<int> intVector;
    //vector has 0 -> 9 as index 0 -> 9
    for(unsigned int i = 0; i < 10; i++)
        intVector.push_back(i);

    SECTION("COPY CONSTRUCTOR")
    {
        DSvector<int> intVectorCopy(intVector);
        REQUIRE(intVectorCopy.size() == 10);
        //Try to access non-existing element in vector => catch error
        REQUIRE_THROWS_AS(intVectorCopy.at(20), out_of_range);
        REQUIRE(intVectorCopy.at(4) == 4);
        REQUIRE_THROWS_AS(intVectorCopy.at(15), out_of_range);
    }
    SECTION("Size")
    {
        REQUIRE(intVector.size() == 10);
    }

    SECTION("Capacity")
    {
        REQUIRE(intVector.capacity() == 10);
    }

    SECTION("at() Function")
    {
        REQUIRE(intVector.size() == 10);
        //Try to access non-existing element in vector => catch error
        REQUIRE_THROWS_AS(intVector.at(20), out_of_range);

        REQUIRE(intVector.at(4) == 4);
        //Out Of Bound
        //REQUIRE(intVector.at(10) == 4);
    }

    SECTION("isEmpty Function")
    {
        //pop back 10 times and check if vector is empty or not
        for(unsigned int i = 0; i < 10; i++)
            intVector.pop_back();
        REQUIRE(intVector.isEmpty() == true);
    }

    SECTION("front and back function")
    {
        //Check FRONT and BACK return value
        REQUIRE(intVector.front() == 0);
        REQUIRE(intVector.back() == 9);
    }

    SECTION("resize() function")
    {
        intVector.resize();
        intVector.resize();
        intVector.resize();
        //Check capacity, should be 80
        REQUIRE(intVector.capacity() == 80);
    }

    SECTION("push_back() Function")
    {
        //Call function and check size and content
        for(int i = 10; i < 20; i++)
            intVector.push_back(i);
        REQUIRE(intVector.size() == 20);
        REQUIRE(intVector.at(15) ==15);
    }

    SECTION("pop_back() Function")
    {
        //pop back 5 times and check size, capacity and content
        for(unsigned int i = 0; i < 5; i++)
            intVector.pop_back();
        REQUIRE(intVector.size() == 5);
        REQUIRE(intVector.capacity() == 10);

        //print content - Correct
            //intVector.print();
    }

    SECTION("erase() and swap()")
    {
        //SWAP element at index 1 and 6 and check
        intVector.swap(1,8);
        REQUIRE(intVector.at(1) == 8);
        REQUIRE(intVector.at(8) == 1);

        //ERASE element 5 which is int 5 and check size and vector content
        intVector.erase(5);
        //check size and content
        REQUIRE(intVector.size() == 9);
        REQUIRE(intVector.at(5) == 6);

        //Check the output - Correct
              //intVector.print();
    }

    SECTION("equality and inequality check")
    {
        DSvector<int> intVectorCopy2(intVector);

        REQUIRE((intVectorCopy2 == intVector) == true);

        DSvector<int> intVectorCopy;
        intVectorCopy.push_back(0);
        intVectorCopy.push_back(1);
        intVectorCopy.push_back(2);

        REQUIRE((intVectorCopy != intVector) == true);
    }

    SECTION("operator[] and operator=")
    {

        intVector[6] = 100;
        REQUIRE(intVector[6] == 100);
        REQUIRE(intVector[2] == 2);
        REQUIRE(intVector[9] == 9);

        DSvector<int> intCopy, intCopy2;
        intCopy.operator=(intVector);
        intCopy2 = intCopy;

        REQUIRE(intCopy[3] == 3);
        REQUIRE(intCopy[8] == 8);
        REQUIRE(intCopy2[1] == 1);
        REQUIRE(intCopy2[6] == 100);
        REQUIRE_THROWS_AS(intCopy[16], out_of_range);
        REQUIRE_THROWS_AS(intCopy2[14], out_of_range);
        //Print to check content - Correct
          //intCopy.print();
          //intCopy2.print();
    }
}

TEST_CASE("Custom Class (Classroom)")
{
	DSvector<Classroom> crVector;
	Classroom crObj;
	crObj = Classroom(10, 12, "Tom");
	crVector.push_back(crObj);
	crObj = Classroom(20, 22, "Jerry");
	crVector.push_back(crObj);
	crObj = Classroom(14, 10, "Mike");
	crVector.push_back(crObj);
	crObj = Classroom(10, 5, "Skyler");
	crVector.push_back(crObj);
	crObj = Classroom(50, 30, "Leafre");
	crVector.push_back(crObj);
	crObj = Classroom(70, 20, "Darth Vader");
	crVector.push_back(crObj);
	crObj = Classroom(30, 15, "Batman");
	crVector.push_back(crObj);
	//size == 7

    SECTION("COPY CONSTRUCTOR")
    {
        DSvector<Classroom> crVectorCopy(crVector);
        REQUIRE(crVectorCopy[6].getChairs() == 15);
        REQUIRE(crVectorCopy[3].getRoomName() == "Skyler");
        REQUIRE_THROWS_AS(crVectorCopy[60], out_of_range);
    }

	SECTION("capacity")
	{
		REQUIRE(crVector.capacity() == 10);
	}
	
	SECTION("size")
	{
		REQUIRE(crVector.size() == 7);
	}

	SECTION("at() Function")
    {
		REQUIRE(crVector.at(4).getRoomName() == "Leafre");
		REQUIRE(crVector.at(0).getChairs() == 12);
    }

	SECTION("isEmpty Function")
    {
		REQUIRE(crVector.isEmpty() == false);
		crVector.pop_back();
		crVector.pop_back();
		crVector.pop_back();
		crVector.pop_back();
		crVector.pop_back();
		crVector.pop_back();
		crVector.pop_back();
		crVector.pop_back();
		crVector.pop_back();
		REQUIRE(crVector.isEmpty() == true);
    }

    SECTION("front and back function")
    {
		Classroom dummy;
		dummy = crVector.back();
		REQUIRE(dummy.getChairs() == 15);
		REQUIRE(dummy.getRoomName() == "Batman");
		dummy = crVector.front();
		REQUIRE(dummy.getRoomName() == "Tom");
		REQUIRE(dummy.getDesks() == 10);
    }

    SECTION("resize() function")
    {
		crVector.resize();
		crVector.resize();
		REQUIRE(crVector.capacity() == 40);
    }

    SECTION("push_back() Function")
    {
		crVector.push_back(Classroom(11, 12, "Harry Potter"));
		REQUIRE(crVector[7].getRoomName() == "Harry Potter");
    }

    SECTION("pop_back() Function")
    {
		crVector.pop_back();
		crVector.pop_back();
		REQUIRE(crVector.size() == 5);
		REQUIRE(crVector[3].getRoomName() == "Skyler");
    }

    SECTION("erase() and swap()")
    {
		crVector.swap(2, 4);
		REQUIRE(crVector[2].getRoomName() == "Leafre");
		REQUIRE(crVector[4].getDesks() == 14);
		crVector.erase(3);
		REQUIRE(crVector[3].getRoomName() == "Mike");
		REQUIRE(crVector.size() == 6);
    }

    SECTION("operator[] and operator=")
    {
		Classroom dummy;
		Classroom dummy2 = Classroom(33, 44, "Replacement");
		dummy = crVector[3];
		crVector[4] = dummy2;
		REQUIRE(dummy.getRoomName() == "Skyler");
		REQUIRE(crVector[4].getDesks() == 33);
		REQUIRE(crVector[4].getRoomName() == "Replacement");
    }
}
