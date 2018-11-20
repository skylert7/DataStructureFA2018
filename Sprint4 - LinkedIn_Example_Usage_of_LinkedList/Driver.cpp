#include "Driver.h"

Driver::Driver(string connection, string requestConnection, string output)
{
    this->connection = connection;
    this->requestConnect = requestConnection;
    this->outputFile = output;
}

void Driver::run()
{
    ifstream connect(connection);
	ifstream request(requestConnect);
	ofstream outFile(outputFile);
	AdjList<string> adjList;
	Stack<string> stack;
	string entireConnectFile((istreambuf_iterator<char>(connect)),
		istreambuf_iterator<char>());
	stringstream ss(entireConnectFile);

	string entireRequestFile((istreambuf_iterator<char>(request)),
		istreambuf_iterator<char>());
	stringstream ss1(entireRequestFile);

    int const number = 500;//size of array
	string str = "";
	getline(ss, str);//get the number of the beginning of the file

	int noOfEntry = stoi(str);//number of lines
	string connectNames[number];//array to store all the names in order based on the input file

	int index = 0;
	str = "";

	//Start reading from line 2 and storing names onto the array
	while (ss.good())
	{
		getline(ss, str, '|');
		connectNames[index] = str;
		index++;
		getline(ss, str);
		connectNames[index] = str;
		index++;
	}

    string tempStr = "";
    int count = 0;
    int doubleEntry = noOfEntry * 2;
	int numOfPeople = 0;//This is the size the adjacency list

	//Take unique person out of the array
    for (int i = 0; i < noOfEntry * 2; i++)
	{
		tempStr = connectNames[i];
		for (int j = noOfEntry * 2; j < noOfEntry * 3; j++)
		{
			if (tempStr == connectNames[j])
				count++;
		}
		if (count == 0)
		{
			numOfPeople++;
			connectNames[doubleEntry++] = tempStr;
		}
		count = 0;
	}

	doubleEntry = noOfEntry * 2;
	for (int i = doubleEntry; i < doubleEntry + numOfPeople; i++)
	{
		LinkedList<string> temp;
		temp.push_back(connectNames[i]);
		adjList.insert(temp);
	}

	//Build ADJACENCY LIST
	for (int i = 0; i < noOfEntry * 2; i += 2)
	{
		adjList.insertWhereFirstEquals(connectNames[i], connectNames[i + 1]);
		adjList.insertWhereFirstEquals(connectNames[i + 1], connectNames[i]);
	}

	/*
	*
	*
	* Iterative back-tracking
    * Distance
	*
	*
	*/

	string requestNames[number];//Array to store names in request file
	getline(ss1, str);//get the number of the beginning of the file
	int noOfRequest = stoi(str);
	index = 0;

	//Start reading from line 2 and storing names onto the array
	while (ss1.good())
	{
		getline(ss1, str, '|');
		requestNames[index++] = str;
		getline(ss1, str);
		requestNames[index++] = str;
	}

	count = 0;//keep track of index of request
	DSvector<int> myVector;//vector to keep track of distance for each request
	for(int i = 0; i < noOfRequest; i++)//initialize vector with big number
		myVector.push_back(100000);

	//Start counting connections
	for (int a = 0; a < noOfRequest * 2; a += 2)
	{	
		//resetIters
		for (int i = 0; i < numOfPeople; i++)
			adjList.getMem()[i].resetIter();

		//Push start person
		stack.push(requestNames[a]);

		//Back-tracking
		while (!stack.isEmpty())
		{
			if (stack.peek() == requestNames[a + 1])//check to see if top of stack is target
			{
				//Save distance for each request
				if (stack.getSize() - 1 <= myVector[count])
					myVector[count] = (stack.getSize() - 1);
				stack.pop();
			}
			else //Using top of the stack and scan through adjacency list
			{
				adjList.findFirst(stack.peek()).next();
				if (adjList.findFirst(stack.peek()).getCurrent() == nullptr)
				{//If falls out of scope => resetIter and pop stack
					adjList.findFirst(stack.peek()).resetIter();
					stack.pop();
				}
				else
				{
					while (stack.notOnStack(adjList.findFirst(stack.peek()).get()))//while top iter not on stack
					{
						if (adjList.findFirst(stack.peek()).getCurrent() != nullptr)
							stack.push(adjList.findFirst(stack.peek()).get());
					}
				}
			}
		}
		count++;//keep track of index of request
	}

	/*
	*
	*
	* Iterative back-tracking
	* Second degree connection
	*
	*
	*/
	DSvector<string> peopleVector;
    DSvector<int> numOfConnection;
	doubleEntry = noOfEntry * 2;
	for (int i = doubleEntry; i < doubleEntry + numOfPeople; i++) //Vector of all the unique person in file
		peopleVector.push_back(connectNames[i]);
	
	//Sort vector
	peopleVector.sort();
	//Start counting connections
    for (int a = 0; a < peopleVector.size(); a++)
    {
        //resetIters
        for (int i = 0; i < numOfPeople; i++)
            adjList.getMem()[i].resetIter();

        //Push start person
        stack.push(peopleVector[a]);
        //Back-tracking
        while (adjList.findFirst(stack.bottom()).getCurrent() != nullptr)
        {
            adjList.findFirst(stack.bottom()).next();
            if(adjList.findFirst(stack.bottom()).getCurrent() != nullptr)
            {//If iter of the base person LL is not nullptr
                if (stack.notOnStack(adjList.findFirst(stack.bottom()).get()))
                { //If the the person next to the base person is not on stack
                    while (adjList.findFirst(adjList.findFirst(stack.bottom()).get()).getCurrent() != nullptr)
                    {//while iterator of the linkedlist of the person who is next to base person is not nullptr
                        if (stack.notOnStack(adjList.findFirst(adjList.findFirst(stack.bottom()).get()).get()))
                        {//if iterator at the person who is next to bottom person is not on the stack
                            stack.push(adjList.findFirst(adjList.findFirst(stack.bottom()).get()).get());
                            adjList.findFirst(adjList.findFirst(stack.bottom()).get()).next();//step iterator
                        }
                        else //if iterator at the person who is next to bottom person is on the stack
                            adjList.findFirst(adjList.findFirst(stack.bottom()).get()).next();//step iterator
                    }
                }
            }
        }
        //Store number of connections on vector accordingly
        numOfConnection.push_back(stack.getSize() - 1);
        //Clear stack
        stack.clear();
    }

    /*------------------------------------Print to File-----------------------------------------*/
    //Display number of connections
    for(int i = 0; i < numOfPeople; i++)
        outFile << peopleVector[i] << ": " << numOfConnection[i] << "\n";

    //Display distance
    for (int i = 0; i < noOfRequest; i++)
        outFile << requestNames[i * 2] << '|' << requestNames[i * 2 + 1] << ": " << myVector[i] << "\n";
}
