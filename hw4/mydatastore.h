#ifndef MYDATASTORE_H
#define MYDATASTORE_H
#include <string>
#include <set>
#include <vector>
#include <map>
#include "datastore.h"
#include "product.h"
#include "user.h"

class MyDataStore : public DataStore {
 public:
  void addProduct(Product* p);
  void addUser(User* u);
  std::vector<Product*> search(std::vector<std::string>& terms, int type);
  void dump(std::ostream& ofile);

  void addToCart(User* u, Product* p);
  void viewCart(User* u);
  void buyCart(User* u);
  void quitFile();

 private:
  std::vector<Product*> products_;
  std::vector<User*> users_;
  std::map<User*, std::vector<Product*> > map_;


};

#endif
