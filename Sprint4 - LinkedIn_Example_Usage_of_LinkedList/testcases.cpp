//#define CATCH_CONFIG_MAIN  // This tells Catch to provide a main() - only do this in one cpp file
#include "catch.hpp"
#include "LinkedList.hpp"
#include "Stack.hpp"
#include "AdjList.hpp"


TEST_CASE("string class") //If String list works => char list works too
{
	LinkedList<string> stringList;
	stringList.push_back("Zero");
	stringList.push_back("One");
	stringList.push_back("Two");
	stringList.push_back("Three");
	stringList.push_back("Four");
	stringList.push_back("Five");
	stringList.push_back("Six");
	stringList.push_back("Seven.");

	SECTION("getSize()")
	{
		REQUIRE(stringList.getSize() == 8);
	}

	SECTION("isEmpty() Function")
	{
		REQUIRE(stringList.isEmpty() == false);
	}

	SECTION("front() and back()")
	{
		REQUIRE(stringList.front() == "Zero");
		REQUIRE(stringList.back() == "Seven.");
	}

	SECTION("push_front() and push_back()")
	{
		stringList.push_front("I'm a");
			REQUIRE(stringList.getSize() == 9);
		stringList.push_back("human ");
			REQUIRE(stringList.getSize() == 10);
		stringList.push_front("being!");
			REQUIRE(stringList.getSize() == 11);
	}

	SECTION("pop_back() and check for size")
	{
		REQUIRE(stringList.getSize() == 8);

		stringList.pop_back();
		stringList.pop_back();
		stringList.pop_back();

		REQUIRE(stringList.getSize() == 5);
		REQUIRE_THROWS_AS(stringList.at(6), out_of_range);
	}

	SECTION("pop_front() and check for size")
	{
		REQUIRE(stringList.getSize() == 8);

		stringList.pop_front();
		stringList.pop_front();
		stringList.pop_front();

		REQUIRE(stringList.getSize() == 5);
		REQUIRE_THROWS_AS(stringList.at(6), out_of_range);
	}

	SECTION("at() function")
	{
		REQUIRE(stringList.at(3) == "Three");
		REQUIRE(stringList.at(7) == "Seven.");
		REQUIRE(stringList.at(1) == "One");

		REQUIRE_THROWS_AS(stringList.at(12), out_of_range);
	}

	SECTION("insertAt() funtion")
	{
		stringList.insertAt(3, "Three point five");
		REQUIRE(stringList.at(4) == "Three point five");
		stringList.insertAt(2, "Two point five");
		REQUIRE(stringList.at(3) == "Two point five");
	}

	SECTION("swap() funtion")
	{
		stringList.swap(2, 4);
		REQUIRE(stringList.at(2) == "Four");
		REQUIRE(stringList.at(4) == "Two");
	}

	SECTION("removeAt() funtion")
	{
		REQUIRE(stringList.getSize() == 8);

		stringList.removeAt(3);
		REQUIRE(stringList.at(3) == "Four");
		REQUIRE(stringList.at(2) == "Two");
		REQUIRE(stringList.getSize() == 7);
	}

	SECTION("remove() funtion")
	{
		REQUIRE(stringList.getSize() == 8);

		stringList.remove("Four");
		REQUIRE(stringList.at(4) == "Five");
		REQUIRE(stringList.getSize() == 7);

		stringList.remove("Six");
		REQUIRE(stringList.at(5) == "Seven.");
		REQUIRE(stringList.getSize() == 6);
	}

	SECTION("print() funtion")
	{
		stringList.print();
	}

	SECTION("operator[] and operator= and operator==")
	{
		LinkedList<string> stringList2, stringList3;
		stringList2.operator=(stringList);
		stringList3 = stringList2;
		REQUIRE(stringList2[3] == "Three");
		REQUIRE(stringList2[7] == "Seven.");
		REQUIRE(stringList3[1] == "One");
		stringList3[1] = "Two";
		REQUIRE(stringList3[1] == "Two");

		REQUIRE_THROWS_AS(stringList2.at(16), out_of_range);
		REQUIRE_THROWS_AS(stringList3.at(12), out_of_range);
	}
}

TEST_CASE("int vector")         //integer list
{
	LinkedList<int> intList;
	//list has 0 -> 9 as index 0 -> 9
	for (unsigned int i = 0; i < 10; i++)
		intList.push_back(i);

	SECTION("getSize()")
	{
		REQUIRE(intList.getSize() == 10);
	}

	SECTION("isEmpty() Function")
	{
		REQUIRE(intList.isEmpty() == false);

		//pop back 10 times and check if vector is empty or not
		for (unsigned int i = 0; i < 10; i++)
			intList.pop_back();
		REQUIRE(intList.isEmpty() == true);
	}

	SECTION("front() and back()")
	{
		//Check FRONT and BACK return value
		REQUIRE(intList.front() == 0);
		REQUIRE(intList.back() == 9);
	}

	SECTION("push_front() and push_back()")
	{
		//Call function and check size and content
		for (int i = 10; i < 20; i++)
			intList.push_back(i);
		REQUIRE(intList.getSize() == 20);
		REQUIRE(intList.at(15) == 15);

		//Call function and check size and content
		for (int i = 20; i < 30; i++)
			intList.push_front(i);
		REQUIRE(intList.getSize() == 30);
		REQUIRE(intList.at(25) == 15);

	}


	SECTION("pop_back() and check for size")
	{
		//pop back 5 times and check size, capacity and content
		for (unsigned int i = 0; i < 5; i++)
			intList.pop_back();
		REQUIRE(intList.getSize() == 5);

		//print content - Correct
			//intList.print();
	}

	SECTION("pop_front() and check for size")
	{
		//pop front 5 times and check size, capacity and content
		for (unsigned int i = 0; i < 5; i++)
			intList.pop_front();
		REQUIRE(intList.getSize() == 5);

		//print content - Correct
			//intList.print();
	}

	SECTION("at() Function")
	{
		REQUIRE(intList.getSize() == 10);
		//Try to access non-existing element in vector => catch error
		REQUIRE_THROWS_AS(intList.at(20), out_of_range);

		REQUIRE(intList.at(4) == 4);
	}

	SECTION("insertAt() funtion")
	{
		intList.insertAt(3, 6);
		REQUIRE(intList.at(4) == 6);
		intList.insertAt(2, 10);
		REQUIRE(intList.at(3) == 10);
	}

	SECTION("swap() funtion")
	{
		intList.swap(2, 6);
		REQUIRE(intList.at(2) == 6);
		REQUIRE(intList.at(6) == 2);
	}

	SECTION("removeAt() funtion")
	{
		REQUIRE(intList.getSize() == 10);

		intList.removeAt(3);
		REQUIRE(intList.at(3) == 4);
		REQUIRE(intList.at(2) == 2);
		REQUIRE(intList.getSize() == 9);
	}

	SECTION("remove() funtion")
	{
		REQUIRE(intList.getSize() == 10);

		intList.remove(4);
		REQUIRE(intList.at(4) == 5);
		REQUIRE(intList.getSize() == 9);

		intList.remove(6);
		REQUIRE(intList.at(5) == 7);
		REQUIRE(intList.getSize() == 8);
	}

	SECTION("print() funtion")
	{
		intList.print();
	}

	SECTION("operator[] and operator= and operator==")
	{
		LinkedList<int> intList2, intList3;
		intList2.operator=(intList);
		intList3 = intList;

		REQUIRE(intList2.at(3) == 3);
		REQUIRE(intList2.at(7) == 7);
		REQUIRE(intList3.at(1) == 1);

		REQUIRE_THROWS_AS(intList2.at(16), out_of_range);
		REQUIRE_THROWS_AS(intList3[12], out_of_range);
	}
}


TEST_CASE("Stack")
{
    Stack<int> stack;
    for (unsigned int i = 0; i < 10; i++)
        stack.push(i);// Stack has 10 elements which are equal to their indexes
                      // top element is 9
	SECTION("push function")
	{
        stack.push(100);
        REQUIRE(stack.peek() == 100);
	}
    SECTION("pop function")
    {
        stack.pop();
        REQUIRE(stack.peek() == 8);
        REQUIRE(stack.getSize() == 9);
    }
    SECTION("isEmpty function")
    {
         REQUIRE(stack.isEmpty() == false);
    }
    SECTION("peek function")
    {
        REQUIRE(stack.peek() == 9);
    }
    SECTION("notOnStack function")
    {
        REQUIRE(stack.notOnStack(1000) == true);
    }
    SECTION("clear function")
    {
        stack.clear();
        REQUIRE(stack.getSize() == 0);
    }
    SECTION("getSize function")
    {
        REQUIRE(stack.getSize() == 10);
    }
}
TEST_CASE("Adj List")
{
    AdjList<string> adjList;
    string str = "Skyler";
    string str2 = "Linh";
    string str3 = "Tran";
    LinkedList<string> llist1;
    LinkedList<string> llist2;
    llist1.push_back(str);
    llist2.push_back(str2);
    llist2.push_back(str3);
    adjList.insert(llist1);

    SECTION("insert")
    {
        adjList.insert(llist2);
        REQUIRE(adjList.getMem()[1][0] == "Linh");
    }
	SECTION("insertWhereFirstEquals")
	{
        adjList.insertWhereFirstEquals("Skyler", "Test");
        REQUIRE(adjList.getMem()[0][1] == "Test");
	}
	SECTION("findFirst")
	{
        REQUIRE(adjList.findFirst("Skyler")[0] == "Skyler");
	}
}

