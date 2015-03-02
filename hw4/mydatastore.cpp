#include <iostream>
#include <string>
#include <vector>
#include <map>
#include "product_parser.h"
#include "datastore.h"
#include "product.h"
#include "util.h"
#include "user.h"

using namespace std;


/*MyDataStore::~MyDataStore() 
{

} */

  /**
   * Adds a product to the data store
   */
void MyDataStore::addProduct(Product* p)
{
	products_.push_back(p);
}
 
  /**
   * Adds a user to the data store
   */
void MyDataStore::addUser(User* u)
{
	users_.push_back(u);
}

  /**
   * Performs a search of products whose keywords match the given "terms"
   *  type 0 = AND search (intersection of results for each term) while
   *  type 1 = OR search (union of results for each term)
   */
std::vector<Product*> MyDataStore::search(std::vector<std::string>& terms, int type)
{
	std::vector<Product*> v;
	std::vector<std::string>::iterator it;

	if (type == 0)
	{
		for (unsigned int i = 0; i < products_.size(); i++)
		{
			int  count = 0;
			std::set<std::string> keywords_ = products_[i]->keywords();
			std::set<std::string>::iterator itt;
			for (it = terms.begin(); it != terms.end(); ++it)
			{
				*it = convToLower(*it);
				for (itt = keywords_.begin(); itt != keywords_.end(); ++itt)
				{
					if (*it == *itt)
					{
						count++;
					}

				}
			}
			int size = terms.size();
			if (count == size)
			{
				v.push_back(products_[i]);
			}
		}	
	}

	else if (type == 1)
	{
		for (unsigned int i = 0; i < products_.size(); i++)
		{
			bool found = false;
			std::set<std::string> keywords_ = products_[i]->keywords();
			std::set<std::string>::iterator itt;
			for (it = terms.begin(); it != terms.end(); ++it)
			{
				*it = convToLower(*it);

				for (itt = keywords_.begin(); itt != keywords_.end(); ++itt)
				{
					if (*it == *itt)
					{
						found = true;
						v.push_back(products_[i]);
						break;
					}

				}
				if (found == true)
				{
					break;
				}
			}
		}	
	}

	return v;

}

  /**
   * Reproduce the database file from the current Products and User values
   */
   /*
void MyDataStore::dump(std::ostream& ofile)
{
	std::vector<Product*>::iterator it;
	std::vecotr<User*>::iterator itt;


} */

void MyDataStore::addToCart(User* u, Product* p)
{

	map_.find(u)->second.push_back(p);
	p->subtractQty(1);
}


void MyDataStore::viewCart(User* u)
{
	// int cartSize = map_.find(u)->second.size();
	// std::vector<Product*>::iterator it;
	for (unsigned int i = 0; i < map_.find(u)->second.size(); i++)
	{
		map_.find(u)->second[i]->displayString();
	}
}

void MyDataStore::buyCart(User* u)
{
	std::vector<Product*>::iterator it;
	for (unsigned int i = 0; i < map_.find(u)->second.size(); i++)
	{
		if (map_.find(u)->second[i]->getQty() > 0)
		{
			if (map_.find(u)->first->getBalance() > map_.find(u)->second[i]->getPrice())
			{
				map_.find(u)->second[i]->subtractQty(1);
				map_.find(u)->first->deductAmount(map_.find(u)->second[i]->getPrice());
				map_.find(u)->second.erase(map_.find(u)->second.begin()+i);
			}
		}
	}
}

void MyDataStore::quitFile()
{

}