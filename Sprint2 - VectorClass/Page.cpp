#include "page.h"

Page::Page(){}

Page::Page(int p, string c)
{
    this->pageNo = p;
    this->content = c;
}

void Page::storeOnVector()
{
	char c;
	int static count = 0;
	string stage2Str;
	stringstream ss(content);
	
	//Ignore punctuation and weird characters
	while (ss.get(c))
	{
        if (c == '\n')
        {
                stage2Str += c;
        }
        if (c == ',' || c == '^' || c == '?' || c == '%'
			|| c == '#' || c == '$' || c == '!' || c == ':' || c == '('
			|| c == '*' || c == ')' || c == '&')
			cout << "";
		else if (c == '.')
		{
			c = ' ';
			stage2Str += c;
		}
		else
			stage2Str += c;
	}//End

    //Store phrases on vector
    DSvector<int> sbPos; //square bracket vector
    DSvector<int> spacePos; //space char vector
	stringstream ss2(stage2Str);
    for(int i = 0; i < stage2Str.length(); i++)
    {
		//sbPos has square brackets indexes; sbPos[even] == '['; sbPos[odd] == ']';
        if(stage2Str[i] == '[')
            sbPos.push_back(i);
        if(stage2Str[i] == ']')
            sbPos.push_back(i);
    }
	for (int i = 0; i < sbPos.size(); i++)
		if (i % 2 == 0)
			words.push_back(stage2Str.substr(sbPos[i] + 1
				, sbPos[i + 1] - sbPos[i] - 1));
	//End storing phrases

	//delete space at the end of words in "phrase vector"
	for (int i = 0; i < words.size(); i++)
	{
		string s = words[i];
		stringstream ss1(s);
		if (s.length() > 1 && s[s.length() - 1] == ' ')
		{
			s = "";
			words.erase(i);
			for (int j = 0; j < ss1.str().size() - 1; j++)
			{
				ss1.get(c);
				s += c;
			}
			words.push_back(s);
		}
		
	}

	string stage3Str;
	//Erase phrases in sentence that were store on words vector
	while (ss2.get(c))
	{
		if (c == '[')
		{
			while (ss2.get(c))
				if (c == ']')
					goto finish;
		}
		stage3Str += c;
	finish:
		cout << "";
	}//End

	//Pushing individual words on vector
	string stage4Str;
	stringstream ss3(stage3Str);
	while (ss3.get(c))
	{
		if (c == ' ' || ss3.eof() == true || c == '\n')
		{
			if (stage4Str.length() == 1)
			{
				//Special cases
				if (stage4Str == "a" || stage4Str == "i" || stage4Str == "0" || stage4Str == "1" || stage4Str == "2"
					|| stage4Str == "3" || stage4Str == "4" || stage4Str == "5" || stage4Str == "6"
					|| stage4Str == "7" || stage4Str == "8" || stage4Str == "9")
				{
					words.push_back(stage4Str);
					stage4Str = "";
				}
			}
			else if (stage4Str.length() < 1)
			{
				stage4Str += c;
				do
				{
						ss3.get(c);
						stage4Str += c;
				} while ((c != ' ' || c!= '\n') && stage4Str.length() >= 3 && ss3.eof() == false);
			}
			else if (stage4Str.length() >= 2)
			{
				trim(stage4Str);
				words.push_back(stage4Str);
				stage4Str = "";
			}
		}
		else
			stage4Str += c;
	}
	if (ss3.eof())
	{
		//special cases
		if (stage4Str.length() >= 2)
		{
			trim(stage4Str);
			if (stage4Str != "" && stage4Str != " " && stage4Str != "  " && stage4Str != "   ")
			{
				words.push_back(stage4Str);
			}
		}
	}
	//End pushing words
	//Sort vector Words
	sortVectorWords();
}

void Page::sortVectorWords()
{
	//Alphabetically
	if (words.size() == 1)
        cout<<"";
	else
	{
        int a, b;
		for (a = 0; a < words.size() - 1; a++)
			// Last a elements are already in place   
			for (b = 0; b < words.size() - a - 1; b++)
				if (words[b][0] > words[b + 1][0])
					words.swap(b, b + 1);
	}

	//delete words that are the same
	for (int i = 0; i < words.size(); i++)
	{
		for (int j = i; j < words.size(); j++)
		{
			if (i == j)
				cout << "";
			else if(i != j)
			{
				if (words[i] == words[j])
					words.erase(j);
			}
		}
	}
}

string Page::toLower()
{
    transform(content.begin(), content.end(), content.begin(),
              ptr_fun<int, int>(tolower));
    return content;
}

void Page::trim(string &s)
{
	//trim '\n' and space character
	stringstream ss(s);
	s = "";
	char c;
	while (ss.get(c))
	{
		if (c == ' ')
			c = c;
		else if (c == '\n')
            c = c;
		else
			s += c;
	}
	stringstream ss1(s);
	if (s.length() > 1 && s[s.length() - 1] == ' ')
	{
		s = "";
        for (int j = 0; j < ss1.str().size() - 1; j++)
		{
			ss1.get(c);
			s += c;
		}
	}
}

void Page::setPage(int p)
{
    this->pageNo = p;
}

void Page::setPageContent(string c)
{
    this->content = c;
}

int Page::getPage()
{
    return this->pageNo;
}

string Page::getPageContent()
{
    return this->content;
}

DSvector<string>& Page::getWordsVector()
{
	return this->words;
}
