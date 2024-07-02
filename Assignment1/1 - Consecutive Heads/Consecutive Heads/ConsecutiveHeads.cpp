/*
 * File: ConsecutiveHeads.cpp
 * --------------------------
 * Name: [TODO: enter name here]
 * Section: [TODO: enter section leader here]
 * This file is the starter project for the Consecutive Heads problem.
 * [TODO: rewrite the documentation]
 */

#include <iostream>
#include "console.h"z
#include "random.h"
using namespace std;

int main() {

	
	int count = 0;
	int heads = 0;

	while(heads != 3) {
		count++;
		int x = randomInteger(0,1);
		if(x == 1) {
			cout << "tails" << endl;
			heads = 0;
		}
		if(x == 0) {
			cout << "heads" << endl;
			heads++;
		}
	}
	cout << "It took " << count << " flips to get 3 consecutive heads" << endl;
    
    return 0;
}
