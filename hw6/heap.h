#ifndef HEAP_H
#define HEAP_H

#include <stdexcept>
#include <vector>
#include <functional>
#include <utility>

using namespace std;

template <typename T, typename Comparator >
class Heap
{
 public:
  /// Constructs an m-ary heap for any m >= 2
  Heap(int m, Comparator c);

  /// Destructor as needed
  ~Heap();

  /// Adds an item
  void push(const T& item);

  /// returns the element at the top of the heap 
  ///  max (if max-heap) or min (if min-heap)
  T const & top() const;

  /// Removes the top element
  void pop();

  /// returns true if the heap is empty
  bool empty() const;

  int size();

  vector<T> getHeap();

 private:
  /// Add whatever helper functions and data members you need below

  void trickleUp(int loc);
  void trickleDown(int idx);

  vector<T> heap_;
  Comparator comp_;
  int m_;


};

// Add implementation of member functions here

template <typename T, typename Comparator>
Heap<T,Comparator>::Heap(int m, Comparator c)
{
  vector<T> heap_;
  comp_ = c;
  m_ = m;
  // heap_.insert(heap_.begin(), 0);
}

template <typename T, typename Comparator>
Heap<T,Comparator>::~Heap()
{
  heap_.clear();
}

template <typename T, typename Comparator>
void Heap<T,Comparator>::push(const T& item)
{
  heap_.push_back(item);
  trickleUp(heap_.size()-1);
  // for (unsigned int i = 0; i < heap_.size(); i++)
  // {
    // cout << heap_[i] << ", ";
  // }
  // cout << endl;
}

template <typename T, typename Comparator>
void Heap<T,Comparator>::trickleUp(int loc)
{
  int parent = (loc-1)/m_;
  while (parent >= 0 && comp_(heap_[loc], heap_[parent]))
  {
    swap(heap_[parent], heap_[loc]);
    loc = parent;
    parent = (loc-1)/m_;
  }
}

template <typename T, typename Comparator>
bool Heap<T,Comparator>::empty() const
{
  if (heap_.size() == 0)
  {
    return true;
  }
  else
  {
    return false;
  }
}


// We will start top() for you to handle the case of 
// calling top on an empty heap
template <typename T, typename Comparator>
T const & Heap<T,Comparator>::top() const
{
  // Here we use exceptions to handle the case of trying
  // to access the top element of an empty heap
  if(empty()){
    throw std::logic_error("can't top an empty heap");
  }
  // If we get here we know the heap has at least 1 item
  // Add code to return the top element
  else
  {
    return heap_[0];
  }
}


// We will start pop() for you to handle the case of 
// calling top on an empty heap
template <typename T, typename Comparator>
void Heap<T,Comparator>::pop()
{
  if(empty()){
    throw std::logic_error("can't pop an empty heap");
  }
  else
  {
    heap_[0] = heap_.back();
    heap_.pop_back();
    trickleDown(0);
  }

  for (unsigned int i = 0; i < heap_.size(); i++)
  {
    // cout << heap_[i] << ", ";
  }

}

template <typename T, typename Comparator>
void Heap<T,Comparator>::trickleDown(int idx)
{
  // cout << "in pop" << endl;

  if (heap_.size() < (m_*idx)+m_)
  {
    return; 
  }
  int correctChild = (m_*idx)+1; 

  for (int i = 2; i <= m_; i++)
  {
    if ((m_*idx)+i < heap_.size())
    {
      // cout << "There is another child" << endl;
      // cout << "correct child + " << correctChild << endl;

      int nextChild = correctChild+1;
      // cout << "next child = " <<nextChild <<  endl;
    
      if (comp_(heap_[nextChild], heap_[correctChild]))
      {
        // cout << "in second if" << endl;
        correctChild = nextChild;
        // cout << "smaller child = " << correctChild << endl;
      }
    }
  }

  if (comp_(heap_[correctChild], heap_[idx]))
  {
    // cout << "in third if" << endl;
    // cout << "idx = " << idx << endl;
    swap(heap_[idx], heap_[correctChild]);
    trickleDown(correctChild);
  }
}

template <typename T, typename Comparator>
int Heap<T,Comparator>::size()
{
  return heap_.size();
}

template <typename T, typename Comparator>
vector<T> Heap<T,Comparator>::getHeap()
{
  return heap_;
}


#endif

