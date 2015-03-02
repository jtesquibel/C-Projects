#include <sstream>
#include <string>
#include <iomanip>
#include "book.h"
#include "util.h"

using namespace std;

Book::Book(const std::string category, const std::string name, double price, int qty, std::string isbn,
std::string author) : Product(category, name, price, qty)
{
	author_ = author;
	isbn_ = isbn; 
}

Book::~Book()
{

}

std::set<std::string> Book::keywords() const
{
	std::set<std::string> set1 = parseStringToWords(name_);
	std::set<std::string> set2 = parseStringToWords(author_);
	set2.insert(isbn_);

	std::set<std::string> end = setUnion(set1, set2);

	return end;
} 

bool Book::isMatch(std::vector<std::string>& searchTerms) const
{
	return false;
}

std::string Book::displayString() const
{
	std::string s1 = getName();
	std::string newline = "\n";
	std::string s2 = "Author: ";
	std::string s3 = getAuthor();
	std::string space = " ";
	std::string s4 = "ISBN: ";
	std::string s5 = getIsbn();
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

void Book::dump(std::ostream& os) const
{ 
	os << category_ << "\n" << name_ << "\n" << price_ << "\n" << qty_ << "\n" << isbn_ << "\n" << author_ << endl;
}

std::string Book::getAuthor() const
{
	return author_;
}

std::string Book::getIsbn() const
{
	return isbn_;
}
