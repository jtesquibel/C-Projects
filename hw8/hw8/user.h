#ifndef USER_H
#define USER_H
#include <iostream>
#include <string>
#include <map>

/**
 * Implements User functionality and information storage
 *  You should not need to derive anything from User at this time
 */
class User{
 public:
  User();
  User(std::string name, int age, double balance, int type, long long password);
  virtual ~User();

  int getAge() const;
  double getBalance() const;
  std::string getName() const;
  long long getPassword() const;
  std::map<std::string, double> getSimilarities();
  void setSimilarities(std::string, double);
  void deductAmount(double amt);
  virtual void dump(std::ostream& os);

 private:
  std::string name_;
  int age_;
  double balance_;
  int type_;
  long long password_;
  // double dist_;
  // User* pred_;
  std::map<std::string, double> similarities_;
};
#endif
