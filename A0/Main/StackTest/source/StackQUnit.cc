
#ifndef STACK_TEST_CC
#define STACK_TEST_CC

#include "QUnit.h"
#include "Stack.h"

#include <iostream>

int main (int numArgs, char **args) {

	QUnit::UnitTest qunit(std :: cerr, QUnit :: verbose);
	
	if (numArgs == 2) {
		int which = atoi (args[1]);
		if (which == 1) 
			goto test1;
		if (which == 2) 
			goto test2;
		if (which == 3) 
			goto test3;
		if (which == 4) 
			goto test4;
		if (which == 5) 
			goto test5;
		if (which == 6) 
			goto test6;
		if (which == 7) 
			goto test7;
		if (which == 8) 
			goto test8;
	}

	test1:
	std :: cout << "Test 1\n";
	// UNIT TEST 1
	// just make sure we can create an empty stack, and that it is empty
	{
		
		Stack <int> myStack;
		QUNIT_IS_EQUAL (myStack.isEmpty (), true);

	}

	test2:
	std :: cout << "Test 2\n";
	// UNIT TEST 2
	// make sure we can push/pop a bunch of items
	{

		Stack <int> myStack;
		for (int i = 0; i < 10; i++) {
			myStack.push (i);
		}

		int counter = 0;
		for (int i = 0; i < 10; i++) {
			if (myStack.pop () == 9 - i)
				counter++;
		}

		QUNIT_IS_EQUAL (counter, 10);
	}

	test3:
	std :: cout << "Test 3\n";
	// UNIT TEST 3
	// make sure that the destructor works correctly... unless the stack correctly deallocates
	// all of the items it contains, this test will fail
	{
		static int temp = 0;
		struct Tester {
			Tester () {temp++;}
			~Tester () {temp--;}
		};

		{
			Stack <std :: shared_ptr <Tester>> myStack;
			std :: shared_ptr <Tester> myGuy = std :: make_shared <Tester> ();
			for (int i = 0; i < 10; i++) {
				myStack.push (myGuy);
			}
		}

		QUNIT_IS_EQUAL (temp, 0);
	}

	test4:
	std :: cout << "Test 4\n";
	// UNIT TEST 4
	// make sure we can push/pop a bunch of items and then do it again
	{

		Stack <int> myStack;
		for (int i = 0; i < 10; i++) {
			myStack.push (i);
		}

		int counter = 0;
		for (int i = 0; i < 5; i++) {
			if (myStack.pop () == 9 - i)
				counter++;
		}

		for (int i = 5; i < 20; i++) {
			myStack.push (i);
		}

		for (int i = 0; i < 20; i++) {
			if (myStack.pop () == 19 - i)
				counter++;
		}
		
		if (myStack.isEmpty ())
			counter++;

		QUNIT_IS_EQUAL (counter, 26);
	}

	test5:
	std :: cout << "Test 5\n";
	// UNIT TEST 5
	// make sure that we can completely fill and empty the stack many times
	{

		Stack <int> myStack;
		for (int i = 0; i < 10; i++) {
			for (int j = 0; j < 10; j++) {
				myStack.push (j);
			}
			for (int j = 0; j < 10; j++) {
				myStack.pop ();
			}
		}

		QUNIT_IS_EQUAL (myStack.isEmpty (), true);
	}

	test6:
	std :: cout << "Test 6\n";
	// UNIT TEST 6
	// make sure isEmpty works
	{

		Stack <int> myStack;
		for (int i = 0; i < 10; i++) {
			myStack.push (i);
		}
		int counter = 10;
		while (!myStack.isEmpty ()) {
			myStack.pop ();
			counter--;
		}
		
		QUNIT_IS_EQUAL (counter, 0);
	}

	test7:
	std :: cout << "Test 7\n";
	// UNIT TEST 7
	// Make sure we can create a stack of strings
	{

		Stack <std :: string> myStack;
		for (int i = 0; i < 10; i++) {
			myStack.push (std :: string ("This is my string number ") + std :: to_string (i));
		}

		int counter = 0;
		for (int i = 9; i >= 0; i--) {
			if (myStack.pop () == std :: string ("This is my string number ") + std :: to_string (i)) {
				counter++;
			}	
		}

		QUNIT_IS_EQUAL (counter, 10);
	}

	test8:
	std :: cout << "Test 8\n";
	// UNIT TEST 8
	// make sure we can create two stacks
	{
		
		Stack <std :: string> myStack;
		for (int i = 0; i < 10; i++) {
			myStack.push (std :: string ("This is my string number ") + std :: to_string (i));
		}

		int counter = 0;
		Stack <std :: string> hisStack;
		for (int i = 9; i >= 0; i--) {
			hisStack.push (std :: string ("This is my string number ") + std :: to_string (i));
			if (myStack.pop () == std :: string ("This is my string number ") + std :: to_string (i)) {
				counter++;
			}	
		}

		for (int i = 0; i < 10; i++) {
			if (hisStack.pop () == std :: string ("This is my string number ") + std :: to_string (i)) {
				counter++;
			}
		}
	
		QUNIT_IS_EQUAL (counter, 20);
	}
}

#endif

