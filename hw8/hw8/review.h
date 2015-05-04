#ifndef REVIEW_H
#define REVIEW_H
#include <string>

/**
 * Models a review for the product identified by prodName
 */
struct Review
{
  Review() :  prodName(), rating(), userName(), date(), reviewText()
  { }
  Review(std::string& prod, 
	 int& rate, 
   std::string& userName_,
	 std::string& d, 
	 std::string& review_text) :
    prodName(prod), 
    rating(rate), 
    userName(userName_),
    date(d), 
    reviewText(review_text)
  { }
  
  std::string displayReview() const;
  
  std::string prodName;
  int rating;
  std::string userName;
  std::string date;
  std::string reviewText;
};

#endif
