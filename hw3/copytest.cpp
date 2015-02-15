#include "lib/llistint.h"
#include "gtest/gtest.h"

class LListIntTest : public testing::Test {
protected:
	// You can remove any or all of the following functions if its body is empty.

	LListIntTest() {
		// You can do set-up work for each test here.
	}

	virtual ~LListIntTest() {
		// You can do clean-up work that doesn't throw exceptions here.		
	}

	// If the constructor and destructor are not enough for setting up
	// and cleaning up each test, you can define the following methods:
	virtual void SetUp() {
		// Code here will be called immediately after the constructor (right
		// before each test).
		
	}

	virtual void TearDown() {
		// Code here will be called immediately after each test (right
		// before the destructor).
	}

	// Objects declared here can be used by all tests in the test case.
	// LListInt list;
};

TEST(LListIntTest, CopyConstructor) {

	LListInt * list = new LListInt();
	list->push_back(6);
	list->push_back(11);
	list->push_back(18);

	LListInt * list2 = new LListInt(*list);
	
	EXPECT_EQ(list2->get(0), 6);
	EXPECT_EQ(list2->get(1), 11);
	EXPECT_EQ(list2->get(2), 18);

}

TEST(ArrayListTest, OperatorCall) {

	LListInt * list = new LListInt();
	list->push_back(6);
	list->push_back(11);
	list->push_back(18);

	LListInt * list2 = new LListInt();
	list2 = list;

	EXPECT_EQ(list2->get(0), 6);
	EXPECT_EQ(list2->get(1), 11);
	EXPECT_EQ(list2->get(2), 18);
}
