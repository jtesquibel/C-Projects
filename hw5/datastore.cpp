#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <set>
#include "product_parser.h"
#include "datastore.h"
#include "product.h"
#include "book.h"
#include "clothing.h"
#include "movie.h"
#include "util.h"
#include "user.h"
#include "review.h"

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
	
	for (unsigned int i = 0; i < reviews_.size(); i++)
	{
		delete reviews_[i];
	}
	reviews_.clear();
}

  /**
   * Adds a product to the data store
   */
void MyDataStore::addProduct(Product* p)
{
	products_.push_back(p);
	std::vector<Review*> reviews;
	map2_.insert(pair <std::string, std::vector<Review*> >(p->getName(), reviews));
	// avgRatings_.push_back(std::make_pair(getProduct(p->getName()), avgRating));
}
 
  /**
   * Adds a user to the data store
   */
void MyDataStore::addUser(User* u)
{
	users_.push_back(u);
	std::vector<Product*> users;
	map_.insert(pair <std::string, std::vector<Product*> >(u->getName(), users));
}

void MyDataStore::addReview(Review* r)
{
	reviews_.push_back(r);
	map2_.find(r->prodName)->second.push_back(r);
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
			int count = 0;
			std::set<std::string> keywords_;
			keywords_ = products_[i]->keywords();
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
		return v;
	}
	else if (type == 1)
	{
		std::set<Product*> results;
		std::vector<Product*>::iterator it2;
		
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
						results.insert(products_[i]);
						break;
					}

				}
				if (found == true)
				{
					break;
				}
			}
		}	
		std::vector<Product*> v2(results.begin(), results.end());
		return v2;
	}
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
	std::vector<User*>::iterator it2;
	for (it2 = users_.begin(); it2 != users_.end(); ++it2)
	{
		ofile << (*it2)->getName() << " " << (*it2)->getAge() << " ";
		ofile << (*it2)->getBalance() << " " << '\n';
	}
	ofile << "</users>" << '\n';

	ofile << "<reviews>" << '\n';
	std::vector<Review*>::iterator it3;
	for (it3 = reviews_.begin(); it3 != reviews_.end(); ++it3)
	{
		ofile << (*it3)->prodName << '\n';
		ofile << (*it3)->rating << " " << (*it3)->date << " " << (*it3)->reviewText << '\n';
	}
	ofile << "</reviews>" << '\n';

} 

void MyDataStore::addToCart(std::string username, Product* p)
{
	map_.find(username)->second.push_back(p);
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

std::vector<int> MyDataStore::buyCart(std::string username)
{
	std::vector<int> rows;
	 
	for (unsigned int i = 0; i < users_.size(); i++)
	{
		if (users_[i]->getName() == username)
		{
			if (map_.count(username) != 0)
			{
				for (unsigned int j = 0; j < map_.find(username)->second.size(); j++)
				{
					std::cout << "Cart size = " << map_.find(username)->second.size() << std::endl;
					if (users_[i]->getBalance() > (map_.find(username)->second)[j]->getPrice())
					{
						if ((map_.find(username)->second)[j]->getQty())
						{
							(map_.find(username)->second)[j]->subtractQty(1);
							double price = (map_.find(username)->second)[j]->getPrice();
							users_[i]->deductAmount(price);
							rows.push_back(j);
							map_.find(username)->second.erase(map_.find(username)->second.begin()+j);
							std::cout << "New balance = " << users_[i]->getBalance() << std::endl;
							j--;
						}

					}
				}
			}
		}
	}
	return rows;

}

void MyDataStore::removeProduct(std::string username, std::string prodName)
{
	// map_.find(username)->second.size();
	for (unsigned int i = 0; i < map_.find(username)->second.size(); i++)
	{
		std::cout << "Inside" << std::endl;
		if ((map_.find(username)->second)[i]->getName() == prodName)
		{
			map_.find(username)->second.erase(map_.find(username)->second.begin()+i);
			i--;
			std::cout << "Erased from vector" << std::endl;
			std::cout << "Cart new size = " << map_.find(username)->second.size() << std::endl;
			break;
		}
	}
}



std::vector<Product*> MyDataStore::getProducts()
{
	return products_;
}

Product* MyDataStore::getProduct(std::string prodName)
{
	for (unsigned int i = 0; i < products_.size(); i++)
	{
		if (products_[i]->getName() == prodName)
		{
			return products_[i];
		}
	}
}

std::vector<User*> MyDataStore::getUsers()
{
	cout << "Hello" << endl;
	return users_;
}

User* MyDataStore::getUser(std::string userName)
{
	for (unsigned int i = 0; i < users_.size(); i++)
	{
		if (users_[i]->getName() == userName)
		{
			return users_[i];
		}
	}
}

std::vector<Review*> MyDataStore::getReviews(std::string prodName)
{
	// std::cout << "In getReviews" << std::endl;
	std::cout << "Certain # of reviews = " << map2_.find(prodName)->second.size() << std::endl;
	return map2_.find(prodName)->second;
}

std::vector<Product*> MyDataStore::getCart(std::string username)
{
	std::cout << "size = " << map_.find(username)->second.size() << std::endl;
	return map_.find(username)->second;
}

std::vector<std::pair<Product*, double> > MyDataStore::getAverageRatings()
{
	return avgRatings_;
}

double MyDataStore::calculateAvgRating(std::string prodName)
{
	double totalRating = 0;
	int count = 0;
	std::vector<Review*> reviews = getReviews(prodName);
	for (unsigned int i = 0; i < reviews.size(); i++)
	{
		double currRating = reviews[i]->rating;
		totalRating += currRating;
		count++;
	}

	std::cout << "rating count = " << count << std::endl;

	double avgRating;
	if (count == 0)
	{
		avgRating = 0;
	}
	else if (count > 0)
	{
		avgRating = totalRating/count;
	}
	return avgRating;
	// avgRatings_.push_back(std::make_pair(getProduct(prodName), avgRating));
}