#include <iostream>
#include <cstdlib>
#include "../lib/setint.h"

using namespace std;

SetInt::SetInt()
{

}

/*
SetInt::SetInt(const SetInt& other)
{
  this->list_.clear();
  SetInt * set2 = new SetInt();
  for (int i = 0; i < other.size(); i++)
  {
    if (i == 0)
    {
      set2->insert(*(other.first()));
    }
    set2->insert(*(other.next()));
  }
} */

/**
 * Destructor
 */
SetInt::~SetInt()
{
  list_.clear();
}

/**
 * Returns the current number of items in the list 
 */
int SetInt::size() const
{
  return list_.size();
}

/**
 * Returns true if the list is empty, false otherwise
 */
bool SetInt::empty() const
{
  return list_.empty();
}

/**
 * Inserts val into the set, do nothing if val already exists
 */
void SetInt::insert(const int& val)
{
  for (int i = 0; i < list_.size(); i++)
  {
    if (list_.get(i) == val)
    {
      return;
    }
  }

  if (iter_ > 1)
  {
    iter_ = 1;
  }

  list_.push_back(val);
}

/**
 * Removes the value from the set, do nothing if it doesn't exist
 */
void SetInt::remove(const int& val)
{
  for (int i = 0; i < list_.size(); i++)
  {
    if (list_.get(i) == val)
    {

      list_.remove(i);
    }
  }

  if (iter_ > 1)
  {
    iter_ = 1;
  }
}

/**
 * Returns true if the item is in the set
 */
bool SetInt::exists(const int& val) const
{
  for (int i = 0; i < list_.size(); i++)
  {
    if (list_.get(i) == val)
    {
      return true;
    }
  }
  return false;
}

/**
 * Return a pointer to the first item
 *  and support future calls to next()
 */
int const* SetInt::first()
{
  if (list_.empty())
  {
    cout << "List is empty" << endl;
    return NULL;
  }
  
  iter_ = 1;

  return &list_.get(0);
}

/**
 * Return a pointer to the next item
 *  after the previous call to next
 *  and NULL if you reach the end
 */
int const* SetInt::next()
{
  // check to see if you're at the end
  if (iter_ == list_.size())
  {
    return NULL;
  }

  iter_++;
  return &list_.get(iter_-1);

}

/**
 * Returns another (new) set that contains
 * the union of this set and "other"
 */ 
// SetInt SetInt::setUnion(const SetInt& other) const
/* {
  SetInt * temp = new SetInt();
  bool found = false;
  for (int i = 0; i < list_.size(); i++)
  {
    temp->list_.insert(list_.size(), list_.get(i));
  }
  for (int i = 0; i < other.list_.size(); i++)
  {
    for (int j = 0; j < list_.size(); i++)
    {
      if (list_.get(j) == other.list_.get(i))
      {
        found == true;
      }
    }
    if (found == false)
    {
      temp->list_.insert(list_.size(), other.list_.get(i));
    }
  }
  return &temp; 
} */

/**
 * Returns another (new) set that contains
 * the intersection of this set and "other"
 */ /*
SetInt SetInt::setIntersection(const SetInt& other) const
{

}
*/
SetInt SetInt::operator|(const SetInt& other) const
{
  SetInt temp;
  for (int i = 0; i < this->size(); i++)
  {
    temp.insert(this->list_.get(i));
  }
  for (int i = 0; i < other.size(); i++)
  {
    bool found = false;
    for (int j = 0; j < this->size(); j++)
    {
      if (this->list_.get(j) == other.list_.get(i))
      {
        found = true;
      }
    }
    if (found == true)
    {
      temp.insert(other.list_.get(i));
    }
  }
  return temp;
}

SetInt SetInt::operator&(const SetInt& other) const
{
  SetInt temp;
  for (int i = 0; i < this->size(); i++)
  {
    for (int j = 0; j < other.size(); j++)
    {
      if (this->list_.get(i) == other.list_.get(j))
      {
        temp.insert(other.list_.get(j));
      }
    }
  }
  return temp;
}
