#include <iostream>
#include "lib/setint.h"

using namespace std;

int main()
{
	SetInt * set = new SetInt();

	if (set->empty())
	{
		cout << "CORRECT: Set is empty" << endl;
	}
	else
	{
		cout << "FALSE: Set is not empty" << endl;
	}

	set->insert(1);
	set->insert(2);
	set->insert(3);
	set->insert(4);

	/*if (!set->empty())
	{
		cout << "CORRECT: Set is not empty after one insertion" << endl;
	}
	else
	{
		cout << "FALSE: Set is still empty after one insertion" << endl;
	}

	if (set->exists(4) == false)
	{
		cout << set->exists(4) << endl;
		// cout << "CORRECT: The Set does not contain the val 4" << endl;
	}

	if (set->exists(5) == true)
	{
		cout << set->exists(5) << endl;
		// cout << "CORRECT: The Set contains 5 after 1 insertion" << endl;
	}

	set->remove(5);
	set->insert(6);
	set->insert(8);
	set->insert(10);
	set->insert(12);

	if (set->size() == 1)
	{
		cout << "CORRECT: The set has size of 1" << endl;
	}
	else
	{
		cout << "FALSE: Wrong size" << endl;
	}

	cout << "Trying to remove the last item" << endl;

	// set->remove(8);

	// cout << "Removed the last item" << endl;

 */

	cout << *set->first() << endl;
	for (int i = 0; i < 3; i++)
	{
		cout << *set->next() << endl;
	}

	SetInt * set2 = new SetInt();
	set2->insert(7);
	set2->insert(8);
	set2->insert(9);
	set2->insert(10);

	/* SetInt * set3 = new SetInt();
	set3 = set | set2;

	cout << *set3->first() << endl;
	for (int i = 0; i < 8; i++)
	{
		cout << *set3->next() << endl;
	}
*/
	SetInt set3;
	set3.insert(12);
	set3.insert(13);
	set3.insert(14);
	set3.insert(21);

	SetInt set4;
	set3.insert(20);
	set3.insert(21);
	set3.insert(22);
	set3.insert(23);

	SetInt set5;
	set5 = set3 & set4;

	cout << *set5.first() << endl;
	for (int i = 0; i < set5.size(); i++)
	{
		cout << *set5.next() << endl;
	}

	cout << "EVERYTHING CHECKS" << endl;

	delete set;
	delete set2;
}