#include "lib/llistint.h"
#include <iostream>

using namespace std;

int main() {
  LListInt * list = new LListInt();

  // Check if the list is initially empty.
  if (list->empty()) {
    cout << "SUCCESS: List is empty initially." << endl;
  } else {
    cout << "FAIL: List is not empty initially when it should be." << endl;
  }

  // Insert an item at the head.
  list->insert(0, 3);

  // Check if the list is still empty.
  if (!list->empty()) {
    cout << "SUCCESS: List is not empty after one insertion." << endl;
  } else {
    cout << "FAIL: List is empty after one insertion." << endl;
  }

  if (list->size() == 1) {
    cout << "SUCCESS: List has size 1 after one insertion." << endl;
  } else {
    cout << "FAIL: List has size " << list->size() << " after one insertion.";
    cout << endl;
  }

  // Check if the value is correct.
  if (list->get(0) == 3.3) {
    cout << "SUCCESS: 3.3 is at the 0th index of the list." << endl;
  } else {
    cout << "FAIL: 3.3 is not at the 0th index of the list, " << list->get(0);
    cout << " is instead." << endl;
  }

  list->insert(1, 5.5);

   // Check if the value is correct.
  if (list->get(1) == 5.5) {
    cout << "SUCCESS: 5.5 is at the 1st index of the list." << endl;
  } else {
    cout << "FAIL: 5.5 is not at the 0th index of the list, " << list->get(0);
    cout << " is instead." << endl;
  }

  list->remove(1);

  if (list->size() == 1) {
    cout << "SUCCESS: List has size 1 after two insertions and one deletion." << endl;
  } else {
    cout << "FAIL: List has size " << list->size() << " after two insertions and one deletion.";
    cout << endl;
  }

  list->remove(0);

   // Check if the list is empty again
  if (list->empty()) {
    cout << "SUCCESS: List is empty again." << endl;
  } else {
    cout << "FAIL: List is not empty again when it should be." << endl;
  }

  list->insert(0, 3);
  list->insert(1, 5);
  list->insert(1, 7);

  if (list->size() == 3) {
    cout << "SUCCESS: List has size 3 after three insertions." << endl;
  } else {
    cout << "FAIL: List has size " << list->size() << " after three insertions.";
    cout << endl;
  }

  list->remove(1);
  list->remove(1);

  if (list->size() == 1) {
    cout << "SUCCESS: List has size 1 after stuff." << endl;
  } else {
    cout << "FAIL: List has size " << list->size() << " after stuff.";
    cout << endl;
  }

  // push back 2 numbers
  list->push_back(5);
  list->push_back(18);

  // test to make sure the push backs worked
  cout << "size = " << list->size() << endl << list->get(1) << endl << list->get(2) << endl;

  // create and new list by the copy constructor
  LListInt * list2 = new LListInt(*list);
  cout << "size = " << list2->size() << endl << list2->get(1) << endl << list2->get(2) << endl;

  // create a third list
  LListInt * list3 = new LListInt();

  // set it equal to list2 by the assignment operator
  list3 = list;
  cout << endl << "size = " << list3->size() << endl << list3->get(1) << endl << list3->get(2) << endl;


  cout << "EVERYTHING CHECKS" << endl;
  
  // Clean up memory.
  delete list;
}