
#include "deck.hpp"

#include <vector>
#include <stack>
#include <iostream>
#include <ctime>
#include <iomanip>
#include <unistd.h>
#include <signal.h>
#include <sys/time.h>

int numOfTested (0), numOfPassed (0), numOfFailed (0), numOfIgnored (0);

#define TEST_ASSERT_EQUAL(x)				\
	numOfTested++;							\
	x ? numOfPassed++ : numOfFailed++;

#define TEST_SUMMARY()                      \
    cout << "====================" << endl; \
    cout << "OVERALL TEST SUMMARY" << endl; \
	cout << endl;							\
	cout << "TESTED:   " << numOfTested << endl; \
	cout << "PASSED:   " << numOfPassed << endl; \
	cout << "FAILED:   " << numOfFailed << endl; \
	cout << "IGNORED:  " << numOfIgnored << endl; \
	cout << endl;								\
    cout << "====================" << endl;

using namespace std;

void testMemberMethods(void)
{
	card::Deck<int> card_deck;

	// Test empty method
	for (int i=1; i<=10; i++){
		card_deck.add(i);
	}
	
	while (!card_deck.empty())
	{
		card_deck.draw();
	}
	
	TEST_ASSERT_EQUAL(card_deck.size() == 0);

}
	
int main(void)
{

    testMemberMethods();


	TEST_SUMMARY();

	return 0;
}

