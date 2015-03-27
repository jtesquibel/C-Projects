#include <iostream>
#include <sstream>
#include <cctype>
#include <algorithm>
#include "util.h"

using namespace std;
std::string convToLower(std::string src) 
{
  std::transform(src.begin(), src.end(), src.begin(), ::tolower);
  return src;
}

/** Complete the code to convert a string containing a rawWord 
    to a set of words based on the criteria given in the assignment **/
std::set<std::string> parseStringToWords(std::string rawWord) 
{
	std::set<std::string> set1;

	rawWord = convToLower(rawWord);

	if (rawWord.size() < 2)
	{
		return set1;
	}

	std::stringstream ss;
	std::string temp, word, word2, word3, word4;

	ss << rawWord;
	while (ss >> temp)
	{
		bool check = false, check2 = false;
		if (temp.size() < 2)
		{
			continue;
		}
		for (unsigned int i = 0; i < temp.size(); i++)
		{
			if (ispunct(temp[i]))
			{
				if (check2 == true)
				{
					break;
				}
				check = true;
				word = temp.substr(0, i);
				if (word.size() >= 2)
				{
					set1.insert(word);
				}
				word2 = temp.substr(i+1);
				if (word2.size() < 2)
				{
					break;
				}

				for (unsigned int j = 0; j < word2.size(); j++)
				{
					if (ispunct(word2[j]))
					{
						check2 = true;
						word3 = word2.substr(0, j);
						if (word3.size() >= 2)
						{
							set1.insert(word3);
						}

						word4 = word2.substr(j+1);
						if (word4.size() >= 2)
						{
							set1.insert(word4);
							break;
						}
					}
				}
				if (check2 == false)
				{
					set1.insert(word2);
				}
			}
		}
		if (check == false)
		{
			set1.insert(temp);
		}
	}
	return set1;
}

