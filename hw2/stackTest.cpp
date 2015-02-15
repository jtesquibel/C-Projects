#include "stackdbl.h"
#include <iostream>

using namespace std;

int main() {
  StackDbl * stack = new StackDbl();

  // Check if the list is initially empty.
  if (stack->empty()) {
    cout << "SUCCESS: Stack is empty initially." << endl;
  } else {
    cout << "FAIL: Stack is not empty initially when it should be." << endl;
  }

  // Insert an item at the head.
  stack->push(3.3);

  // Check if the Stack is still empty.
  if (!stack->empty()) {
    cout << "SUCCESS: Stack is not empty after one insertion." << endl;
  } else {
    cout << "FAIL: Stack is empty after one insertion." << endl;
  }

  /*
  if (Stack->size() == 1) {
    cout << "SUCCESS: Stack has size 1 after one insertion." << endl;
  } else {
    cout << "FAIL: Stack has size " << Stack->size() << " after one insertion.";
    cout << endl;
  } */

  // Check if the value is correct.
  if (stack->top() == 3.3) {
    cout << "SUCCESS: 3.3 is at the top of the Stack." << endl;
  } else {
    cout << "FAIL: 3.3 is not at the top of the Stack, " << stack->top();
    cout << " is instead." << endl;
  }

  stack->push(5.5);

   // Check if the value is correct.
  if (stack->top() == 5.5) {
    cout << "SUCCESS: 5.5 is at the top of the Stack now." << endl;
  } else {
    cout << "FAIL: 5.5 is not at the top of the Stack now, " << stack->top();
    cout << " is instead." << endl;
  }

  stack->pop();

  /*
  if (!Stack->empty()) {
    cout << "SUCCESS: Stack is not empty after two insertions and one deletion." << endl;
  } else {
    cout << "FAIL: Stack has size " << Stack->size() << " after two insertions and one deletion.";
    cout << endl;
  } */

  stack->pop();

   // Check if the Stack is empty again
  if (stack->empty()) {
    cout << "SUCCESS: Stack is empty again." << endl;
  } else {
    cout << "FAIL: Stack is not empty again when it should be." << endl;
  }

  stack->push(3.3);
  stack->push(5.5);
  stack->push(7.7);

  /*
  if (Stack->size() == 3) {
    cout << "SUCCESS: Stack has size 3 after three insertions." << endl;
  } else {
    cout << "FAIL: Stack has size " << Stack->size() << " after three insertions.";
    cout << endl;
  } */

  stack->pop();
  stack->pop();

  /*
  if (Stack->size() == 1) {
    cout << "SUCCESS: Stack has size 1 after stuff." << endl;
  } else {
    cout << "FAIL: Stack has size " << list->size() << " after stuff.";
    cout << endl;
  } */

  // Clean up memory.
  delete stack;
}