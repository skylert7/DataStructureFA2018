#include "Driver.h"

//global variable multiMap
multimap<string, UserRecord> multiMap;
vector<string> partOfSpeeches = { "ADJECTIVE","ADJECTIVE OR NUMERAL","ADVERB","CLOSING PARENTHESIS","CLOSING QUOTATION MARK","COLON OR ELLIPSIS","COMMA","CONJUNCTION","DETERMINER",
"DOLLAR","EXISTENTIAL THERE","FOREIGN WORD","GENITIVE MARKER","HASHTAG","INTERJECTION","MODAL AUXILIARY","NOUN","NUMBER","NUMERAL","OPENING PARENTHESIS","PARTICLE","PREPOSITION OR CONJUNCTION",
"PRONOUN","SENTENCE TERMINATOR","SYMBOL","TO","URL","USERNAME", "VERB" };

Driver::Driver(string csvFile, string textFile, string outFile)
{
    this->csvFile = csvFile;
    this-> textFile = textFile;
    this->outFile = outFile;
}
Driver::Driver() {}

string Driver::getUserName2nd(string line)
{
	string userName2nd;
	stringstream ss(line);
	getline(ss, userName2nd, ' ');
	return userName2nd;
}

vector<string> Driver::getTypeOfWord(string line)
{
	vector<string> typeNeedsReplacement;
	string typeOfWord;
	//Find typeOfWord to fill in
	int firstLim, lastLim;
	//get string between [	]
	for (unsigned int i = 0; i < line.length(); i++)
	{
		if (line[i] == '[')
			firstLim = i;
		if (line[i] == ']')
		{
			lastLim = i;
			typeOfWord = line.substr(firstLim + 1, lastLim - firstLim - 1);
			typeNeedsReplacement.push_back(typeOfWord);
		}
	}
	return typeNeedsReplacement;
}

vector<string> Driver::getWordFromRecord(string userName2nd, vector<string> typeOfWordVector)
{
	pair<multimap<string, UserRecord>::iterator, multimap<string, UserRecord>::iterator>
		result1 = multiMap.equal_range(userName2nd);
	vector<string> localVector;
	vector<string> returnVector;
	string typeOfWord;
	for (unsigned int a = 0; a < typeOfWordVector.size(); a++)
	{
		//get Object associates with userName
		typeOfWord = typeOfWordVector[a];
		for (auto i = result1.first; i != result1.second; i++)
		{
			multimap<string, string> localMap;
			UserRecord user = i->second;
			localMap = user.getmyMap();

			pair<multimap<string, string>::iterator, multimap<string, string>::iterator>
				result2 = localMap.equal_range(typeOfWord);

			//get word associates with typeOfWord
			for (auto j = result2.first; j != result2.second; j++)
			{
				localVector.push_back(j->second);
			}
		}
	}
	//randomly pick a word
	srand(time(0));
	string word;
	for (unsigned int i = 0; i < typeOfWordVector.size(); i++)
	{
		if (localVector.size() > 0)
		{
			int b = (rand() % localVector.size());
			word = localVector[b];
			returnVector.push_back(word);
		}
		else
			returnVector.push_back("No Word of this PartOfSpeech");
	}
	return returnVector;
}

string Driver::appendLineForMadLibs(string line, vector<string> wordVector)
{
	string newline;
	string word;
	int delim1, delim2;
	if (wordVector.size() == 1)
	{
		for (unsigned int i = 0; i < line.length(); i++)
		{
			if (line[i] == '[')
			{
				delim1 = i;
			}
			if (line[i] == ']')
			{
				delim2 = i;
			}
		}
		word = wordVector[0];
		newline = line.substr(0, delim1) + "[" + word + line.substr(delim2, line.length() - delim2) + "\n";
	}
	if (wordVector.size() == 2)
	{
		string chunks1, chunks2, chunks3, chunks4, chunks5;
		stringstream ss(line);
		while (ss.good())
		{
			getline(ss, chunks1, '[');
			getline(ss, chunks2, ']');
			getline(ss, chunks3, '[');
			getline(ss, chunks4, ']');
			getline(ss, chunks5);
		}
		newline = chunks1 + '[' + wordVector[0] + ']' + chunks3 + 
			'[' + wordVector[1] + ']' + chunks5 + "\n";
	}
	
	if (wordVector.size() == 3)
	{
		string chunks1, chunks2, chunks3, chunks4, chunks5, chunks6, chunks7;
		stringstream ss(line);
		while (ss.good())
		{
			getline(ss, chunks1, '[');
			getline(ss, chunks2, ']');
			getline(ss, chunks3, '[');
			getline(ss, chunks4, ']');
			getline(ss, chunks5, '[');
			getline(ss, chunks6, ']');
			getline(ss, chunks7);
		}
		newline = chunks1 + '[' + wordVector[0] + ']' + chunks3 +
			'[' + wordVector[1] + ']' + chunks5 + '[' + wordVector[2] + chunks7 + "\n";
	}
	if (wordVector.size() == 4)
	{
		string chunks1, chunks2, chunks3, chunks4, chunks5, chunks6, chunks7, chunks8, chunks9, chunks10;
		stringstream ss(line);
		while (ss.good())
		{
			getline(ss, chunks1, '[');
			getline(ss, chunks2, ']');
			getline(ss, chunks3, '[');
			getline(ss, chunks4, ']');
			getline(ss, chunks5, '[');
			getline(ss, chunks6, ']');
			getline(ss, chunks7, '[');
			getline(ss, chunks8, ']');
			getline(ss, chunks9);
		}
		newline = chunks1 + '[' + wordVector[0] + ']' + chunks3 +
			'[' + wordVector[1] + ']' + chunks5 + '[' + wordVector[2] + chunks7 + '['
			+ wordVector[3] + ']' + chunks9 + '\n';
	}
	return newline;
}

int Driver::getNegativeTweet()
{
	UserRecord user = UserRecord();
	int count = 0;
	for (auto i = multiMap.begin(); i != multiMap.end(); i++)
	{
		user = (*i).second;
		if (user.getTarget() == '0')
			count++;
	}
	return count;
}

int Driver::getPositiveTweet()
{
	UserRecord user = UserRecord();
	int count = 0;
	for (auto i = multiMap.begin(); i != multiMap.end(); i++)
	{
		user = (*i).second;
		if (user.getTarget() == '4')
			count++;
	}
	return count;
}

double Driver::getAvgWordPerPositive()
{
	double avg = 0;
	if (getPositiveTweet() > 0)
	{
		UserRecord user = UserRecord();
		int countOfWord = 0;
		for (auto i = multiMap.begin(); i != multiMap.end(); i++)
		{
			user = (*i).second;
			if (user.getTarget() == '4')
				countOfWord += user.getmyMap().size();
		}
		avg = double(countOfWord / (getPositiveTweet()));
	}
	return avg;
}

double Driver::getAvgWordPerNegative()
{
	double avg;
	if (getNegativeTweet() > 0)
	{
		UserRecord user = UserRecord();
		int countOfWord = 0;
		for (auto i = multiMap.begin(); i != multiMap.end(); i++)
		{
			user = (*i).second;
			if (user.getTarget() == '0')
				countOfWord += user.getmyMap().size();
		}
		avg = double(countOfWord / (getPositiveTweet()));
	}
	return avg;
}

string Driver::displayTopThreeNeg()
{
	string str;
	int count;
	vector<string> words;
	multimap<string, string> localMap; //map for for each user
	multimap<string, string> localMap2;
	multimap<string, int> localMap3;
	multimap<int, string> localMap4;
	multimap<int, string> localMap5;
	UserRecord userObject = UserRecord();
	//Store words of each part of speech on to localMap2
	for (auto i = multiMap.begin(); i != multiMap.end(); i++)
	{
		userObject = (*i).second;
		localMap = userObject.getmyMap();
		count = 0;
		if (userObject.getTarget() == '0')
		{
			
			for (unsigned int i = 0; i < partOfSpeeches.size(); i++)
			{
				string partOfSpeech = partOfSpeeches[i];
				pair<multimap<string, string>::iterator, multimap<string, string>::iterator>
					result = localMap.equal_range(partOfSpeech);
				for (auto j = result.first; j != result.second; j++)
				{
					localMap2.insert(pair<string, string>(partOfSpeech, (*j).second));
				}
			}
		}
	}
	//store words onto vector words
	for (unsigned int i = 0; i < partOfSpeeches.size(); i++)
	{
		string partOfSpeech = partOfSpeeches[i];
		pair<multimap<string, string>::iterator, multimap<string, string>::iterator>
			result = localMap2.equal_range(partOfSpeech);
		for (auto k = result.first; k != result.second; k++)
		{
			words.push_back((*k).second);
		}
	}
	//store words and number of times they appear on to localMap3 and localMap4
	sort(words.begin(), words.end());
	count = 1;
	for (unsigned int i = 0; i < words.size(); i++)
	{
		string word = words[i];
		if (i == words.size() - 1)
		{}
		else
		{
			if (words[i + 1] == word)
			{
				count++;
			}
			else
			{
				localMap3.insert(pair<string, int>(word, count));
				localMap4.insert(pair<int, string>(count, word));
				count = 1;
			}
		}
	}

    //find top 3 instances of each word of same part of speech
	for (unsigned int i = 0; i < partOfSpeeches.size(); i++)
	{
		int first = 0;
		int second = 0;
		int third = 0;
		vector<string> mostCommon;
		string partOfSpeech = partOfSpeeches[i];
		pair<multimap<string, string>::iterator, multimap<string, string>::iterator>
			result = localMap2.equal_range(partOfSpeech);
        //get count of word associate with part of speech
		for (auto j = result.first; j != result.second; j++)
		{
			string dummyWord = (*j).second;
			pair<multimap<string, int>::iterator, multimap<string, int>::iterator>
				result2 = localMap3.equal_range(dummyWord);
			for (auto k = result2.first; k != result2.second; k++)
			{
				if (first <= (*k).second)
					first = (*k).second;
 				if (second <= (*k).second && first > (*k).second && first > second)
					second = (*k).second;
				if (third <= (*k).second)
					if (first > (*k).second)
						if (second > (*k).second)
							third = (*k).second;
			}
     	}

        for (auto j = result.first; j != result.second; j++)
        {
            string dummyWord = (*j).second;
            pair<multimap<string, int>::iterator, multimap<string, int>::iterator>
                result2 = localMap3.equal_range(dummyWord);
            for (auto k = result2.first; k != result2.second; k++)
            {
                //get word with top 1
                if (first == (*k).second)
                    mostCommon.push_back((*k).first);
                //get word with top 2
                if (second == (*k).second)
                    mostCommon.push_back((*k).first);
                //get word with top 3
                if (third == (*k).second)
                    mostCommon.push_back((*k).first);
            }
        }
		//Append string
		if(mostCommon.size() >= 3)
		{ 
			str += partOfSpeech + " has top 3 most common words respectively are " + mostCommon[0] + " and "
				+ mostCommon[1] + " and " + mostCommon[2] + '\n';
		}
		else
		{
			str += partOfSpeech + " has most common words are ";
            for (unsigned int k = 0; k < mostCommon.size(); k++)
			{
				if (k != mostCommon.size() - 1)
					str += mostCommon[k] + " and ";
				else
					str += mostCommon[k];
			}
			str += '\n';
		}
	}
		return str;
}

string Driver::displayTopThreePos()
{
    string str;
    int count;
    vector<string> words;
    multimap<string, string> localMap; //map for for each user
    multimap<string, string> localMap2;
    multimap<string, int> localMap3;
    multimap<int, string> localMap4;
    multimap<int, string> localMap5;
    UserRecord userObject = UserRecord();
    //Store words of each part of speech on to localMap2
    for (auto i = multiMap.begin(); i != multiMap.end(); i++)
    {
        userObject = (*i).second;
        localMap = userObject.getmyMap();
        count = 0;
        if (userObject.getTarget() == '4')
        {

            for (unsigned int i = 0; i < partOfSpeeches.size(); i++)
            {
                string partOfSpeech = partOfSpeeches[i];
                pair<multimap<string, string>::iterator, multimap<string, string>::iterator>
                    result = localMap.equal_range(partOfSpeech);
                for (auto j = result.first; j != result.second; j++)
                {
                    localMap2.insert(pair<string, string>(partOfSpeech, (*j).second));
                }
            }
        }
    }
    //store words onto vector words
    for (unsigned int i = 0; i < partOfSpeeches.size(); i++)
    {
        string partOfSpeech = partOfSpeeches[i];
        pair<multimap<string, string>::iterator, multimap<string, string>::iterator>
            result = localMap2.equal_range(partOfSpeech);
        for (auto k = result.first; k != result.second; k++)
        {
            words.push_back((*k).second);
        }
    }
    //store words and number of times they appear on to localMap3 and localMap4
    sort(words.begin(), words.end());
    count = 1;
    for (unsigned int i = 0; i < words.size(); i++)
    {
        string word = words[i];
        if (i == words.size() - 1)
        {}
        else
        {
            if (words[i + 1] == word)
            {
                count++;
            }
            else
            {
                localMap3.insert(pair<string, int>(word, count));
                localMap4.insert(pair<int, string>(count, word));
                count = 1;
            }
        }
    }

    //find top 3 instances of each word of same part of speech
    for (unsigned int i = 0; i < partOfSpeeches.size(); i++)
    {
        int first = 0;
        int second = 0;
        int third = 0;
        vector<string> mostCommon;
        string partOfSpeech = partOfSpeeches[i];
        pair<multimap<string, string>::iterator, multimap<string, string>::iterator>
            result = localMap2.equal_range(partOfSpeech);
        //get count of word associate with part of speech
        for (auto j = result.first; j != result.second; j++)
        {
            string dummyWord = (*j).second;
            pair<multimap<string, int>::iterator, multimap<string, int>::iterator>
                result2 = localMap3.equal_range(dummyWord);
            for (auto k = result2.first; k != result2.second; k++)
            {
                if (first <= (*k).second)
                    first = (*k).second;
                if (second <= (*k).second && first > (*k).second && first > second)
                    second = (*k).second;
                if (third <= (*k).second)
                    if (first > (*k).second)
                        if (second > (*k).second)
                            third = (*k).second;
            }
        }

        for (auto j = result.first; j != result.second; j++)
        {
            string dummyWord = (*j).second;
            pair<multimap<string, int>::iterator, multimap<string, int>::iterator>
                result2 = localMap3.equal_range(dummyWord);
            for (auto k = result2.first; k != result2.second; k++)
            {
                //get word with top 1
                if (first == (*k).second)
                    mostCommon.push_back((*k).first);
                //get word with top 2
                if (second == (*k).second)
                    mostCommon.push_back((*k).first);
                //get word with top 3
                if (third == (*k).second)
                    mostCommon.push_back((*k).first);
            }
        }
        //Append string
        if(mostCommon.size() >= 3)
        {
            str += partOfSpeech + " has top 3 most common words respectively are " + mostCommon[0] + " and "
                + mostCommon[1] + " and " + mostCommon[2] + '\n';
        }
        else
        {
            str += partOfSpeech + " has most common words are ";
            for (unsigned int k = 0; k < mostCommon.size(); k++)
            {
                if (k != mostCommon.size() - 1)
                    str += mostCommon[k] + " and ";
                else
                    str += mostCommon[k];
            }
            str += '\n';
        }
    }
        return str;
}


void Driver::run()
{
    ofstream outTestFile(outFile);
    ifstream inSampleFile(csvFile);
    ifstream inTestFile(textFile);

	/*
	*Read from sample file and sort
	*/
	string value, userName;
	int count = 0;
	while (!inSampleFile.eof())
	{
		getline(inSampleFile, value, '\n'); //get everything on one line from IDD to target = value
		//ignore first line
		if (count >= 1)
		{
			//Create object of userRecord that stores all elements of a tweet
			UserRecord tweet = UserRecord(value);
			//split elements in a tweet
			tweet.splitComponents();
			//get username from tweeet
			userName = tweet.getUserName();
			//make multimap for tuple
			tweet.makeMap();
			//Create multimap that takes userName as key and object of userRecord as value
			multiMap.insert(pair<string, UserRecord>(userName, tweet));
		}
		count++;
	}
	inSampleFile.close();

	/*
	*Read from test file and write lines to new file
	*/
	string line, userName2nd, typeOfWord;
	while (!inTestFile.eof())
	{
		getline(inTestFile, line, '\n');

		//get userName from madlib
		userName2nd = getUserName2nd(line);
		//get typeOfWord that needs to fill in
		vector<string> typeOfWord = getTypeOfWord(line);
		//print output to text file
		outTestFile << appendLineForMadLibs(line, getWordFromRecord(userName2nd, typeOfWord));
	}

	/*
	*
	*STATISTICS and write
	*
	*/
	outTestFile << "Number of Tweets is " << count - 2 << endl;
	outTestFile << "Number of Negative Tweets is " << getNegativeTweet() << '\n';
	outTestFile << "Number of Average Word per Negative Tweet is " << getAvgWordPerNegative() << '\n';
	outTestFile << "Number of Positive Tweets is " << getPositiveTweet() << '\n';
	outTestFile << "Number of Average Word per Positive Tweet is " << getAvgWordPerPositive() << '\n';
    outTestFile << "Most Common Words For Negative Tweets\n";
    outTestFile << displayTopThreeNeg();
    outTestFile << "Most Common Words For Positive Tweets\n";
    outTestFile << displayTopThreePos();
}

