#include <iostream>
#include <string>
#include <vector>
#include <map>
#include "product_parser.h"
#include "datastore.h"
#include "product.h"
#include "book.h"
#include "clothing.h"
#include "movie.h"
#include "util.h"
#include "user.h"

using namespace std;


MyDataStore::~MyDataStore() 
{
	for (unsigned int i = 0; i < products_.size(); i++)
	{
		delete products_[i];
	}
	products_.clear();

	for (unsigned int i = 0; i < users_.size(); i++)
	{
		delete users_[i];
	}
	users_.clear();
}

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
	// cout << "Got to search function" << endl;
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
   
void MyDataStore::dump(std::ostream& ofile)
{
	ofile << "<products>" << '\n';
	std::vector<Product*>::iterator it;
	for (it = products_.begin(); it != products_.end(); ++it)
	{
		(*it)->dump(ofile);
	}
	ofile << "</products>" << '\n';

	ofile << "<users>" << '\n';
	std::vector<User*>::iterator itt;
	for (itt = users_.begin(); itt != users_.end(); ++itt)
	{
		ofile << (*itt)->getName() << " " << (*itt)->getAge() << " ";
		ofile << (*itt)->getBalance() << " " << '\n';
	}
	ofile << "</users>" << '\n';

} 

void MyDataStore::addToCart(std::string username, Product* p)
{
	std::vector<User*>::iterator it;
	bool found = false;
	for (it = users_.begin(); it != users_.end(); ++it)
	{
		if ((*it)->getName() == username)
		{
			found = true;
		}
	}
	
	if (found == false)
	{
		cout << "That user does not exist, try again" << endl;
	}
	else
	{
		if (map_.count(username) == 0 )
		{
			std::vector<Product*> cart;
			cart.push_back(p);
			map_.insert(pair<std::string, std::vector<Product*> >(username, cart));
			cout << "Added: " << map_.find(username)->second.back()->getName() << endl;
		}
		else if (map_.count(username) != 0) 
		{
			map_.find(username)->second.push_back(p);
			cout << "Added: " << map_.find(username)->second.back()->getName() << endl;
		}
	}
}


void MyDataStore::viewCart(std::string username)
{
	std::vector<Product*>::iterator it;
	if (map_.count(username) != 0)
	{
		if (map_.find(username)->second.size() == 0)
		{
			cout << "Cart is empty" << endl;
		}
		int i = 1;
		for (it = map_.find(username)->second.begin(); it != map_.find(username)->second.end(); ++it)
		{
			cout << "Item " << i << endl;
			cout << (*it)->displayString() << endl << endl;
			i++;
		}
	}
} 

void MyDataStore::buyCart(std::string username)
{
	std::vector<User*>::iterator it;
	std::vector<Product*>::iterator itt;
	bool done = false;
	 
	for (it = users_.begin(); it != users_.end(); ++it)
	{
		if ((*it)->getName() == username)
		{
			if (done == true)
			{
				break;
			}
			if (map_.count(username) != 0)
			{			
				for (itt = map_.find(username)->second.begin(); itt != map_.find(username)->second.end(); ++itt)
				{
					// cout << "Cart size = " << map_.find(username)->second.size() << endl;
						if ((*it)->getBalance() > (*itt)->getPrice() && (*itt)->getQty() > 0)
						{
							// cout << "Previous quantity: " << (*itt)->getQty()  << "or ";
							// cout << "Old quantity: " << (*itt)->getQty() << endl;
							(*itt)->subtractQty(1);
							// cout << "New quantity: " << (*itt)->getQty() << endl;
							// cout << "Old balance: " << (*it)->getBalance() << endl;
							(*it)->deductAmount((*itt)->getPrice());
							cout << "Bought: " << (*itt)->getName() << endl;
							// cout << "About to remove: " << map_.find(username)->second.at(itt) << endl;
							
							map_.find(username)->second.erase(itt); 
							// cout << "New cart size = " << map_.find(username)->second.size() << endl;
							// cout << "A1: " << map_.find(username)->second.at(i) << " A2: " << map_.find(username)->second.at(i+1) << endl;
							cout << "New balance for " << (*it)->getName() << "s: " << (*it)->getBalance() << endl;
							itt--;
						}
				}
			}
		}
	}
}
