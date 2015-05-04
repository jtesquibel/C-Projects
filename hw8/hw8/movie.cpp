#include <sstream>
#include <string>
#include <iomanip>
#include "movie.h"
#include "util.h"

using namespace std;

Movie::Movie(const std::string category, const std::string name, double price, int qty, std::string genre,
std::string rating) : Product(category, name, price, qty)
{
	genre_ = genre;
	rating_ = rating; 
}

Movie::~Movie()
{

}

std::set<std::string> Movie::keywords() const
{
	std::set<std::string> set1 = parseStringToWords(name_);
	std::set<std::string> set2 = parseStringToWords(genre_);

	std::set<std::string> end = setUnion(set1, set2);

	return end;
} 

bool Movie::isMatch(std::vector<std::string>& searchTerms) const
{
	return false;
}

std::string Movie::displayString() const
{
	std::string s1 = getName();
	std::string newline = "\n";
	std::string s2 = "Genre: ";
	std::string s3 = getGenre();
	std::string space = " ";
	std::string s4 = "Rating: ";
	std::string s5 = getRating();
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

void Movie::dump(std::ostream& os) const
{ 
	os << category_ << "\n" << name_ << "\n" << price_ << "\n" << qty_ << "\n" << genre_ << "\n" << rating_ << endl;
}

std::string Movie::getGenre() const
{
	return genre_;
}

std::string Movie::getRating() const
{
	return rating_;
}
