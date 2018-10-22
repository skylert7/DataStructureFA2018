#include <iostream>
#include <string>
#include <ostream>
#include <fstream>
#include <cstdlib>
#include <sstream>
#include <cctype>
#include <algorithm>
#include <functional>
#include <time.h>
#include "dsvector.hpp"
using namespace std;
#ifndef PAGE_H
#define PAGE_H


class Page
{
private:
    int pageNo;
    string content;
    DSvector<string> words;
public:
    Page();								//Default CONSTRUCTOR
    Page(int p, string c);				//CONSTRUCTOR
    void storeOnVector();				//store Words and Phrases on to Vector Word
	void sortVectorWords();				//sort vector Word and delete duplicate word
    string toLower();					//make all characters to lower cases
	void trim(string&);					//trim all unneccsary characters
    void setPage(int);					//set method
    void setPageContent(string);		//set method
    int getPage();						//get pagenumber
    string getPageContent();			//get pagecontent
	DSvector<string>& getWordsVector(); //get vector of words
};

#endif // PAGE
