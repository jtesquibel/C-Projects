#include "llistdbl.h"
#include <cstdlib>
#include <iostream>

using namespace std;

LListDbl::LListDbl()
{
  head_ = NULL;
  tail_ = NULL;
  size_ = 0;
}

LListDbl::~LListDbl()
{
  clear();
}

bool LListDbl::empty() const
{
  return size_ == 0;
}

int LListDbl::size() const
{
  return size_;
}

/**
 * Complete the following function
 */
void LListDbl::insert(int loc, const double& val)
{
  // if the list is empty
  if (size() == 0)
  {
    Item *temp = new Item();
    head_ = temp;
    head_->val = val;
    head_->next = NULL;
    head_->prev = NULL;
    size_++;
    // cout << size() << size_ << endl;
    return;
  }
  // if the list isn't empty and you want to add to the beginning
  else if (size() != 0 && loc == 0)
  {
    Item *temp = new Item();
    temp->val = val;
    temp->next = head_;
    temp->prev = NULL;
    head_->prev = temp;
    head_ = temp;
    size_++;
    return;
  }
  // if you want to add to the end
  else if (loc == size())
  {
    Item *temp = new Item();
    Item *p = getNodeAt(loc-1);
    temp->val = val;
    temp->next = NULL;
    temp->prev = p;
    p->next = temp;
    tail_= temp;
    size_++;
    return;
  }
  // if you want to add to the middle somewhere
  else if (loc > 0 && loc < size())
  {
    Item *temp = new Item();
    Item *p = getNodeAt(loc-1);
    Item *n = getNodeAt(loc);
    temp->val = val;
    temp->prev = p;
    temp->next = n;
    p->next = temp;
    n->prev = temp;
    size_++;
    return;
  }
}

/**
 * Complete the following function
 */
void LListDbl::remove(int loc)
{
  // if the list is empty
  if (size() == 0)
  {
    return;
  }
  // if there is only 1 item
  else if (size() == 1)
  {
    //Item *temp = getNodeAt(loc);
    head_ = NULL;
    size_--;
  }
  // if the list isn't empty and you want to remove from the beginning
  else if (size() != 0 && loc == 0)
  {
    Item *n = getNodeAt(loc+1);
    n->prev = NULL;
    head_ = n;
    size_--;
    return;
  }
  // if you want to remove from the end
  else if (loc == size()-1)
  {
    Item *temp = getNodeAt(loc);
    Item *p = getNodeAt(loc-1);
    p->next = NULL;
    tail_ = p;
    size_--;
    return;
  }
  // if you want to remove from somewhere in the middle
  else
  {
    Item *p = getNodeAt(loc-1);
    Item *n = getNodeAt(loc+1);
    p->next = n;
    n->prev = p;
    size_--;
    return;
  }


}

void LListDbl::set(int loc, const double& val)
{
  Item *temp = getNodeAt(loc);
  temp->val = val;
}

double& LListDbl::get(int loc)
{
  Item *temp = getNodeAt(loc);
  return temp->val;
}

double const & LListDbl::get(int loc) const
{
  Item *temp = getNodeAt(loc);
  return temp->val;
}

void LListDbl::clear()
{
  while(head_ != NULL){
    Item *temp = head_->next;
    delete head_;
    head_ = temp;
  }
  tail_ = NULL;
  size_ = 0;
}


LListDbl::Item* LListDbl::getNodeAt(int loc) const
{
  Item *temp = head_;
  if(loc >= 0 && loc < size_){
    while(temp != NULL && loc > 0){
      temp = temp->next;
      loc--;
    }
    return temp;
  }
  else {
    //throw std::invalid_argument("bad location");
    return NULL;
  }
}