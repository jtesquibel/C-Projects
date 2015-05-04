#ifndef MSORT_H
#define MSORT_H
#include <vector>
#include <iterator>
#include <iostream>
#include <string>
#include <utility>
#include "product.h"

using namespace std;

template <class T, class Comparator>
void mergeSort(std::vector<T>& myArray, Comparator comp)
{
	if (myArray.size() == 1)
	{
		return;
	}
	else
	{
		// template<class T, class Comparator>
		typename std::vector<T>::iterator middleVec = myArray.begin()+(myArray.size()/2);
		std::vector<T> leftVec(myArray.begin(), middleVec);
		std::vector<T> rightVec(middleVec, myArray.end());

		mergeSort(leftVec, comp);
		mergeSort(rightVec, comp);
		helperMerge(myArray, leftVec, rightVec, comp);
	} 
}

template<class T, class Comparator>
std::vector<T> helperMerge(std::vector<T>& myArray, const std::vector<T>& leftVec, const std::vector<T>& rightVec, Comparator comp)
{
	std::vector<T> temp;
	unsigned int l_it = 0, r_it = 0;
	while (l_it < leftVec.size() && r_it < rightVec.size())
	{
		if (comp(leftVec[l_it], rightVec[r_it]))
		{
			temp.push_back(leftVec[l_it]);
			l_it++;
		}
		else
		{
			temp.push_back(rightVec[r_it]);
			r_it++;
		}
	}

	while (l_it < leftVec.size())
	{
		temp.push_back(leftVec[l_it]);
		l_it++;
	}

	while (r_it < rightVec.size())
	{
		temp.push_back(rightVec[r_it]);
		r_it++;
	}

	myArray = temp;
	return myArray;
} 
  

struct AlphaStrComp
{
	bool operator()(const Product* lhs, const Product* rhs)
	{
		return lhs->getName() < rhs->getName();
	}
};

struct RatingComp
{
	bool operator()(const std::pair<double, Product*>& lhs, const std::pair<double, Product*>& rhs)
	{
		return lhs.first > lhs.first;
	}
};

struct DateComp
{
	bool operator()(const Review* lhs, const Review* rhs)
	{
		std::string date1 = lhs->date; std::string date2 = rhs->date;
		int year1 = atoi(date1.substr(0, 4).c_str()); int year2 = atoi(date2.substr(0, 4).c_str());
		
		if (year1 == year2)
		{
			int month1 = atoi(date1.substr(5, 2).c_str()); int month2 = atoi(date2.substr(5, 2).c_str());
			if (month1 == month2)
			{
				int day1 = atoi(date1.substr(9, 2).c_str()); int day2 = atoi(date2.substr(9, 2).c_str());
				if (day1 == day2)
				{
					return 1;
				}
				else
				{
					return day1 > day2;
				}
			}
			else
			{
				return month1 > month2;
			}
		}
		else
		{
			return year1 > year2;
		}

	}
};

#endif
