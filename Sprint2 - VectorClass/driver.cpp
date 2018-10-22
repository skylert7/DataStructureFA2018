#include "driver.h"

Driver::Driver(string input, string out)
{
    inputFile = input;
    outputFile = out;
}

void Driver::setPageNoVector()
{
	int pageInt = 0;
	//Find position of angle brackets and store on vector
	for (int i = 0; i < contextOfBook.length(); i++)
		if (contextOfBook[i] == '<' || contextOfBook[i] == '>')
			abVector.push_back(i);

	//Collect page number (Include -1 senario if needed)
	for (int i = 0; i < abVector.size(); i++)
	{
		if (i != abVector.size() - 1)
		{
			if ((i % 2) == 0)
			{
				string substr = contextOfBook.substr(abVector[i] + 1, abVector[i + 1] - abVector[i] - 1);
				if (substr == "-1")
				{
					pageNoVector.push_back(-1);
					break;
				}
				pageInt = stoi(substr);
				pageNoVector.push_back(pageInt);
			}
		}
	}//End collecting page number
}

void Driver::setContentVector()
{
	string content;
	//Collect page content
	for (int i = 0; i < abVector.size(); i++)
	{
		if (i != abVector.size() - 1)
		{
			if ((i % 2) == 1)
			{
				content = contextOfBook.substr(abVector[i] + 1, abVector[i + 1] - abVector[i] - 1);
				contentVector.push_back(content);
			}
		}
	}//End collecting page content
}

void Driver::setAlphabetVector()
{
	//set alphabet Vector
	string str = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ";
	transform(str.begin(), str.end(), str.begin(),
		ptr_fun<int, int>(tolower));
	for (int i = 0; i < str.length(); i++)
		alphabet.push_back(str[i]);
}

void Driver::setAllWordsVector()
{
	//get words from each page and store onto vector
	for (int j = 0; j < pageVector.size(); j++)
	{
		DSvector<string> wordVec;
		wordVec = pageVector[j].getWordsVector();
		for (int k = 0; k < wordVec.size(); k++)
		{
			allWords.push_back(wordVec[k]);
		}
	}
    //Sort element
	int a, b;
	for (a = 0; a < allWords.size() - 1; a++)
	{
		//Last a elements are already in place   
		for (b = 0; b < allWords.size() - a - 1; b++)
		{
			if (allWords[b] > allWords[b + 1])
				allWords.swap(b, b + 1);
		}
    }//End
	
	//delete white space or empty string
    for(int i = 0; i < allWords.size(); i++)
    {
        for (int j = 0; j < allWords.size(); j++)
        {
            if (allWords[j].size() == 0 || allWords[j].length() == 0 ||
                allWords[j] == "" || allWords[j] == " ")
                    allWords.erase(j);
        }
    }//End

	//delete words that are the same
	int count = 1;
    //Check and delete until no there is no duplicate words on vector
	while (count != 0)
	{
		count = 0;
        //Check for duplicate words
		for (int i = 0; i < allWords.size(); i++)
		{
			for (int j = i; j < allWords.size(); j++)
			{
				if (i != j)
					if (allWords[i] == allWords[j])
						count++;
			}
		}

        //Delete duplicate words
		for (int i = 0; i < allWords.size(); i++)
		{
			for (int j = i; j < allWords.size(); j++)
			{
				if (i != j)
					if (allWords[i] == allWords[j])
						allWords.erase(j);
				if (j < (allWords.size() - 1))
				{
					if (allWords[j].size() == 0 || allWords[j].length() == 0 ||
						allWords[j] == "" || allWords[j] == " ")
						allWords.erase(j);
				}
			}
		}
	}
}

string Driver::displayResult()
{
	string str; //result will be set to str
	for (int i = 0; i < alphabet.size(); i++)
	{
		string alphabetString = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ";
		int count = 0;
		//Iterate through alphabet
		for (int j = 0; j < allWords.size(); j++)
		{
			//iterate through all the words in file
			if (allWords[j][0] == alphabet[i])
			{
				while (count == 0)
				{
					str += '[';
					char alpha = alphabetString[i];//for display purpose
					str += alpha;
					str += "]\n";
					count++;
				} 
				DSvector<int> pseudoPageNo;
				string stringAllWord = allWords[j];//for display purpose
				str += stringAllWord;
				str += ": ";
				for (int k = 0; k < pageVector.size(); k++)
				{
					//Find page has the words match and store on an int Vector
					Page psuedoPageObject = pageVector[k];
					DSvector<string> wordVec = psuedoPageObject.getWordsVector();
					for (int l = 0; l < wordVec.size(); l++)
					{
						if (allWords[j] == wordVec[l])
						{
							int p = psuedoPageObject.getPage();
							pseudoPageNo.push_back(p);
						}
					}
				}
				//sort page number
                int a, b;
				for (a = 0; a < pseudoPageNo.size() - 1; a++)
					// Last a elements are already in place
					for (b = 0; b < pseudoPageNo.size() - a - 1; b++)
						if (pseudoPageNo[b] > pseudoPageNo[b + 1])
							pseudoPageNo.swap(b, b + 1);
						else if (pseudoPageNo[pseudoPageNo.size() - 1] == pseudoPageNo[pseudoPageNo.size() - 2])
							pseudoPageNo.erase(pseudoPageNo.size() - 1);

				//Display page number
				for (b = 0; b < pseudoPageNo.size(); b++)
				{
					if (b != pseudoPageNo.size() - 1)
					{
						int number;
						number = pseudoPageNo[b];//for display purpose
						str += to_string(number);
						str += ", ";
					}
					else
					{
						int number;
						number = pseudoPageNo[b]; //for display purpose
						str += to_string(number);
					}
				}
				str += '\n';
			}
		}
	}
	return str;
}
void Driver::run()
{
	//Open inFile, outFile and set contextOfBook
	ifstream inFile(inputFile);
	ofstream outFile(outputFile);
	char c;
	while (inFile.get(c))
		contextOfBook += c;

	//set Page number vector, content vector and alphabet vector
	setPageNoVector();
	setContentVector();
	setAlphabetVector();

	//Create object Page with page number and page content and store on PageVector
	for (int i = 0; i < contentVector.size(); i++)
	{
		Page pageObject = Page(pageNoVector[i], contentVector[i]);
		pageObject.toLower();
		pageObject.storeOnVector();
		pageVector.push_back(pageObject);
	}

	//set all the words in file onto allWords vector
	setAllWordsVector();
	cout<< displayResult();
	outFile << displayResult();
}

