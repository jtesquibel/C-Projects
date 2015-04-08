#include <iostream>
#include <vector>
#include <functional> 
#include "heap.h"

using namespace std;

int main()
{
	// less<int> comp;
	greater<int> comp;
	
	// Heap<int, less<int> > h(3, comp);
	Heap<int, greater<int> > h(3, comp);

	h.push(5);
	h.push(10);
	h.push(3);
	h.push(6);
	h.push(29);

	cout << "Top = " << h.top() << endl;

	// h.push(1);
	// h.push(8);
	// h.push(66);

	cout << "Top = " << h.top() << endl;

	h.pop();
	cout << "Top = " << h.top() << endl;

	h.pop();
	cout << "Top = " << h.top() << endl;




return 0;

}