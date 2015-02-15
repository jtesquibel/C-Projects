#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <cstring>
#include <cstdlib>
#include <cctype>
#include <map>
#include "lib/alistint.h"

using namespace std;


string lowercase(string word)
{
	string other;
	for (unsigned int i = 0; i < word.size(); i++)
	{
		char c = word[i];
		if(c <= 'Z' && c >= 'A')
		{
    		word[i] = c -'A'+'a';
		}
	}

	return word;
} 

int main(int argc, char* argv[])
{
	if (argc < 3) // change to 3 at the end
	{
		cout << "Not enough command line arguments, try again" << endl;
		return 1;
	}

	map<string, AListInt> map1;

	ifstream ifile(argv[1]);
	string buff, word;
	int pagenum = 1;
	bool punct = false;
	while (getline(ifile, buff))
	{
		stringstream ss;
		ss << buff;

		while (ss)
		{
			ss >> word;
			word = lowercase(word);

			if (word.size() < 2)
			{
				continue;
			}
			if (word == "<pagebreak>")
			{
				pagenum++;
				continue;
			}

			string word2, word3;
			
			if (ispunct(word[0]))
			{
				word = word.substr(1, word.size());
				cout << "First cap, now: " << word << endl;
			}
			if (word[word.size()-1] == '"')
			{
				word = word.substr(0, word.size()-2);
			}
			while (ispunct(word[word.size()]))
			{
				word = word.substr(0, word.size()-2);
			}
			
			for (unsigned int i = 0; i < word.size(); i++)
			{
				if (ispunct(word[i]))
				{
					if (i == 0)
					{
						word = word.substr(i+1, word.size());
					}
					else if (i == word.size()-1)
					{
						word = word.substr(0, i);
					} 
					else if (i > 0 && i < word.size()-1)
					{
						if (word[i] == '-')
						{
							word = word.substr(0, i-1);
							word2 = word.substr(i+1, word.size());
							for (unsigned int j = 0; j < word2.size(); j++)
							{
								if (i == 0)
								{
									word2 = word2.erase(0, 1);
								}
								if (i > 0 && i < word.size())
								{
									if (word[j] == '-')
									{
										word2 = word2.substr(0, j-1);
										word3 = word2.substr(j+1, word2.size());
									}
									else 
									{
										word2 = word2.erase(i, 1);
									}
								}
							}
						}
						else 
						{
							punct = true;
							break;
						}
					}
				}
				punct = false;
			}

			if (word.size() < 2)
			{
				continue;
			}

			if (punct == true)
			{
				continue;
			}
			if(!punct)
			{
				// cout << endl << word << endl; // << word2 << endl << word3 << endl;
			}

			// word = lowercase(word);

			cout << endl << word << endl;

			if (map1.count(word) == 0)
			{
				AListInt * list = new AListInt();
				list->insert(list->size(), pagenum);
				map1.insert(pair<string, AListInt>(word, *list));
			}
			else 
			{
				for (int i = 0; i < map1.find(word)->second.size(); i++)
				{
					if (map1.find(word)->second.get(i) != pagenum)
					{
						map1.find(word)->second.insert(map1.find(word)->second.size(), pagenum);
					}
				}
			}


		}
	}

	// for (int i = 0; i < map1.find(word)->second.get(i); j++)
	// cout << map1.find

	ofstream ofile;
	ofile.open("output.txt");

	for (int i = 3; i < argc; i++)
	{
		string word = lowercase(argv[i]);
		cout << endl << word << endl;
		ofile << argv[i] << ": ";
		if (map1.count(word) == 1)
		{
			for (int j = 0; j < map1.find(word)->second.get(j); j++)
			{
				ofile << map1.find(word)->second.get(j) << " ";
			}

			ofile << endl;
		}
		else
		{
			ofile << "None" << endl;
		}

	}

	ifile.close();
	ofile.close();

	return 0;
}