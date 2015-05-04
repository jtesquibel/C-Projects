#include "user.h"
using namespace std;

User::User() : name_("unknown"), age_(0), balance_(0.0), type_(1)
{

}
User::User(std::string name, int age, double balance, int type, long long password) : 
  name_(name), age_(age), balance_(balance), type_(type), password_(password)
{
	// dist_
}

User::~User()
{

}


int User::getAge() const
{
  return age_;
}

std::string User::getName() const
{
  return name_;
}

double User::getBalance() const
{
  return balance_;
}

long long User::getPassword() const
{
	return password_;
}

map<std::string, double> User::getSimilarities()
{
	return similarities_;
}

void User::setSimilarities(std::string name, double sim)
{
	similarities_.insert(pair <std::string, double >(name, sim));
}

void User::deductAmount(double amt)
{
  balance_ -= amt;
}

void User::dump(std::ostream& os)
{
  os << name_ << " " << age_ << " " << balance_ << " " << type_ << " " << password_ << endl;
}
