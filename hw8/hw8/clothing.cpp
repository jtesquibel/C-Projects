#include <sstream>
#include <string>
#include <iomanip>
#include "clothing.h"
#include "util.h"

using namespace std;

Clothing::Clothing(const std::string category, const std::string name, double price, int qty, std::string brand,
std::string size) : Product(category, name, price, qty)
{
	brand_ = brand;
	size_ = size; 
}

Clothing::~Clothing()
{

}

std::set<std::string> Clothing::keywords() const
{
	std::set<std::string> set1 = parseStringToWords(name_);
	std::set<std::string> set2 = parseStringToWords(brand_);

	std::set<std::string> end = setUnion(set1, set2);

	return end;
} 

bool Clothing::isMatch(std::vector<std::string>& searchTerms) const
{
	return false;
}

std::string Clothing::displayString() const
{
	std::string s1 = getName();
	std::string newline = "\n";
	std::string s2 = "Size: ";
	std::string s3 = getSize();
	std::string space = " ";
	std::string s4 = "Brand: ";
	std::string s5 = getBrand();
	// new line
	double s6 = getPrice();
	stringstream ss; std::string s7; std::string s9;
	ss << s6;
	ss >> s7;
	// space
	int s8 = getQty();
	stringstream ss1;
	ss1 << s8;
	ss1 >> s9;
	std::string s10 = " left.";

	std::string end = s1 + newline + s2 + s3 + space + s4 + s5 + newline + s7 + space + s9 + s10;
	return end;
}

void Clothing::dump(std::ostream& os) const
{ 
	os << category_ << "\n" << name_ << "\n" << price_ << "\n" << qty_ << "\n" << size_ << "\n" << brand_ << endl;
}

std::string Clothing::getSize() const
{
	return size_;
}

std::string Clothing::getBrand() const
{
	return brand_;
}
