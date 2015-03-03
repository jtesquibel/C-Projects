#ifndef DATASTORE_H
#define DATASTORE_H
#include <string>
#include <set>
#include <vector>
#include <map>
#include "product.h"
#include "user.h"

/** 
 * DataStore Interface needed for parsing and instantiating products and users
 *
 * A derived version of the DataStore can provide other services as well but
 * must support those below
 */
class DataStore {
 public:
  virtual ~DataStore() { }

  /**
   * Adds a product to the data store
   */
  virtual void addProduct(Product* p) = 0;
 
  /**
   * Adds a user to the data store
   */
  virtual void addUser(User* u) = 0;

  /**
   * Performs a search of products whose keywords match the given "terms"
   *  type 0 = AND search (intersection of results for each term) while
   *  type 1 = OR search (union of results for each term)
   */
  virtual std::vector<Product*> search(std::vector<std::string>& terms, int type) = 0;

  /**
   * Reproduce the database file from the current Products and User values
   */
  virtual void dump(std::ostream& ofile) = 0;


};

class MyDataStore : public DataStore {
 public:
  ~MyDataStore();
  void addProduct(Product* p);
  void addUser(User* u);
  std::vector<Product*> search(std::vector<std::string>& terms, int type);
  void dump(std::ostream& ofile);

  void addToCart(std::string username, Product* p);
  void viewCart(std::string username);
  void buyCart(std::string username);

 private:
  std::vector<Product*> products_;
  std::vector<User*> users_;
  std::map<std::string, std::vector<Product*> > map_;


};

#endif
