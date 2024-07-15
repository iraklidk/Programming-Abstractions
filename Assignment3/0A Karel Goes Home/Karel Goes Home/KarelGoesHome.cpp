/*
 * File: KarelGoesHome.cpp
 * ----------------------
 * Name: [TODO: enter name here]
 * Section: [TODO: enter section leader here]
 * This file is the starter project for the Karel Goes Home
 * warmup problem for Assignment #3.
 * [TODO: extend the documentation]
 */

#include <iostream>
#include "console.h"
#include "simpio.h"
using namespace std;

/* Given a street number and avenue number, which are 1-indexed,
 * returns the number of paths Karel can take back home that only
 * moves left or down.
 */

void userInterface(int& street, int& avenue) {
	while(true) {
		cout << "Enter the -1, if u want to exit" << endl;
		avenue = getInteger("Enter the avenue: ");
		street = getInteger("Enter the street: ");
		if(avenue > 0 && street > 0) break;
		else if(avenue < 0 && street < 0 && avenue != -1 && street != -1)
			cout << "Enter the valid avenue and street!";
		else if(avenue == -1 && street == -1) break;
	}
}

int numPathsHome(int street, int avenue, int& count) {
	if(street == 1 && avenue == 1) {
		count++;
	}
	if(street > 1)
	numPathsHome(street - 1, avenue, count);
	if(avenue > 1)
	numPathsHome(street, avenue - 1, count);

	return count;
}

int main() {
	while(true) {
	int street, avenue;
	userInterface(street, avenue);
	if(avenue == -1 && street == -1) {
		cout << "Good Luck!" << endl;
		break;
	}
	int count = 0;
	cout << "Total number of paths is: " << numPathsHome(street, avenue, count) << endl;
	}

    return 0;
}
