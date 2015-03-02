#include <iostream>
#include <sstream>
#include <set>
#include <string>
#include <iomanip>
#include <cctype>
#include <algorithm>
#include "user.h"
#include "product.h"
#include "book.h"
#include "clothing.h"
#include "movie.h"


void MyDataStore::addToCart(User* u, Product* p)
{

	map_.find(u)->second.push_back(p);
	p->subtractQty(1);
}


void MyDataStore::viewCart(User* u)
{
	// int cartSize = map_.find(u)->second.size();
	std::vector<Product*>::iterator it;
	for (unsigned int i = 0; i < map_.find(u)->second.size(); i++)
	{
		map_.find(u)->second[i]->displayString();
	}
}


int main()
{

	
	return 0;
}