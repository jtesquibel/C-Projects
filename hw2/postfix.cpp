#include "stackdbl.h"
#include <iostream>
#include <cstring>
#include <string>
#include <sstream>
#include <fstream>
#include <cstdlib>

using namespace std;


double calculate(string& expr, bool& success)
{
	StackDbl * stack = new StackDbl();
	string temp;
	stringstream bb;
	bb << expr;
	while (bb >> temp)
	{	
		if (temp == "+")
		{
			if (stack->empty())
			{
				success = false;
				return 0;
			}
			else
			{
				double num2 = stack->top();
				stack->pop();
				if (stack->empty())
				{
					success = false;
					return 0;
				}
				else
				{
					double num1 = stack->top();
					stack->pop();
					double num3 = num1 + num2;
					stack->push(num3);
				}
			}
		}
		else if (temp == "-")
		{
			if (stack->empty())
			{
				success = false;
				return 0;
			}
			else
			{
				double num2 = stack->top();
				stack->pop();
				if (stack->empty())
				{
					success = false;
					return 0;
				}
				else
				{
					double num1 = stack->top();
					stack->pop();
					double num3 = num1 - num2;
					stack->push(num3);
				}
			}
		}
		else if (temp == "*")
		{
			if (stack->empty())
			{
				success = false;
				return 0;
			}
			else
			{
				double num2 = stack->top();
				stack->pop();
				if (stack->empty())
				{
					success = false;
					return 0;
				}
				else
				{
					double num1 = stack->top();
					stack->pop();
					double num3 = num1 * num2;
					stack->push(num3);
				}
			}
		}
		else if (temp == "/")
		{
			if (stack->empty())
			{
				success = false;
				return 0;
			}
			else
			{
				double num2 = stack->top();
				stack->pop();
				if (stack->empty())
				{
					success = false;
					return 0;
				}
				else
				{
					double num1 = stack->top();
					stack->pop();
					double num3 = num1 / num2;
					stack->push(num3);
				}
			}
		}
		else
		{
			double num;
			stringstream aa;
			aa << temp;
			aa >> num;
			stack->push(num);
		}
	}

	if (!stack->empty())
	{
		return stack->top();
	}
} 

int main(int argc, char* argv[])
{
	int numLines = 0, i = 0;
	bool success = true;;
	string buff;
	ifstream ifile(argv[1]);
	while (getline(ifile, buff))
	{
		stringstream ss;
		ss << buff;
		numLines++;
	}
	// cout << numLines << endl;

	string * line = new string[numLines];

	ifstream infile(argv[1]);
	while (getline(infile, buff))
	{
		stringstream s;
		s << buff;
		line[i] = buff;
		i++;
	}

	ofstream ofile;
	ofile.open("postfix.out");

	for (int f = 0; f < numLines; f++)
	{
		double num = calculate(line[f], success);
		if (num == 0)
		{
			ofile << "Invalid" << endl;
		}
		else
		{
		ofile << num << endl;
		}
	}
	
	ifile.close();
	infile.close();
	ofile.close();
	
	return 0;
}
