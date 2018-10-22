#include "userRecord.h"
UserRecord::UserRecord()
{}
UserRecord::UserRecord(const UserRecord &object)
{
	tuple = object.tuple;
	target = object.target;
	ID = object.ID;
	tweet = object.tweet;
	myMap = object.myMap;
}
UserRecord::UserRecord(string tweet)
{
	this->tweet = tweet;
}
void UserRecord::splitComponents()
{


	stringstream ss(tweet);
	string chunks;
	//Get userName of one tweet
	unsigned int pos1 = 0;
	while (ss.good())
	{
		getline(ss, chunks, ',');
		pos1++;
		if (pos1 == 2)
		{
			userName = chunks;
			break;
		}
	}

	//Separate ID and Target
	int pos2 = 0;
	while (ss.good())
	{
		getline(ss, chunks, ',');
		pos2++;
		if (pos2 == 1)
			this->ID = chunks;
		if (chunks == "4" || chunks == "0")
			this->target = chunks[0];
	}

	//Find big tuple
	unsigned int firstLim = 0;
	unsigned int lastLim = 0;
	for (unsigned int i = 0; i < tweet.length(); i++)
	{
		if (tweet[i] == '[')
			firstLim = i;
		if (tweet[i] == ']')
			lastLim = i;
	}
	if (tweet.length() > 5)
	{
		tuple = tweet.substr(firstLim + 1, lastLim - firstLim - 1);
	}//Find big tuple ends
}

//create multiMap for tuple
void UserRecord::makeMap()
{
	string word, typeOfWord, chunks, smallerTuple;
	stringstream ss2(tuple);
	//Find smaller tuple
	unsigned int firstLim = 0;
	unsigned int lastLim = 0;
	unsigned int index = 0;
	vector<string> tupleVector;
	do
	{
		if (tuple[index] == '(')
			firstLim = index;
		if (tuple[index] == ')' && tuple.length() > 5)
		{
			lastLim = index;
			smallerTuple = tuple.substr(firstLim + 1, lastLim - firstLim - 1);
			tupleVector.push_back(smallerTuple);
		}
		index++;
	} while (index < tuple.length());//Find smaller tuple ends

	//Find word and typeOfWord and store on multimap myMap
	string firstPart, secondPart;
    unsigned int a = 0;
	while (a < tupleVector.size())
	{
		stringstream ss3(tupleVector[a]);
		int dummy = 0;

		//Check for double quotes

		int counter = 0;
		for (unsigned int j = 0; j < tupleVector[a].length(); j++)
		{
			if (tupleVector[a][j] == '\"')
			{
				string chunks1, chunks2, chunks3, chunksTest;
				
				if (counter == 0)
				{
					while (!ss3.eof() && counter == 0)
					{
						getline(ss3, chunks1, '\"');
						getline(ss3, chunksTest, '\"');
						getline(ss3, chunks2, '\"');
						getline(ss3, chunks, '\"');
						getline(ss3, chunks3, '\'');
						getline(ss3, secondPart, '\'');
						++counter;
						myMap.insert(pair<string, string>(secondPart, chunks2));
					}
				}
			}
			else
			{
				while (!ss3.eof())
				{
					getline(ss3, chunks, '\'');
					getline(ss3, firstPart, '\'');
					getline(ss3, secondPart, ',');
					if (dummy == 0)
						word = firstPart;
					if (dummy != 0 && (dummy % 2) == 1)
					{
						typeOfWord = firstPart;
						myMap.insert(pair<string, string>(typeOfWord, word));
					}
					dummy++;
				}
			}
		}
		a++;
	}

}

/*
*
*GET METHODS
*
*/

char UserRecord::getTarget()
{
	return target;
}
string  UserRecord::getID()
{
	return ID;
}
string  UserRecord::getTuple()
{
	return tuple;
}
string  UserRecord::getTweet()
{
	return tweet;
}
string	UserRecord::getUserName()
{
	return userName;
}
multimap<string, string> UserRecord::getmyMap()
{
	return myMap;
}

//display multimap for word and partOfSpeech
void UserRecord::displayMap()
{
	multimap<string, string>::iterator i;
	for (i = myMap.begin(); i != myMap.end(); ++i)
		cout << (*i).first << "\t" << (*i).second << '\n';
}



