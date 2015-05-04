#include <sstream>
#include "review.h"

std::string Review::displayReview() const
{
	std::string s1 = prodName;
	std::string newLine = "\n";
	std::stringstream ss; std::string s3;
	int s2 = rating;
	ss << s2;
	ss >> s3;
	std::string s6 = userName;
	std::string s4 = date;
	std::string s5 = reviewText;

	std::string end = s1 + newLine + s3 + " " + s6 + " " + s4 + " " + s5;
	return end;
}