/*
 * File: Combinations.cpp
 * ----------------------
 * Name: [TODO: enter name here]
 * Section: [TODO: enter section leader here]
 * This file is the starter project for the Combinations problem.
 * [TODO: rewrite the documentation]
 */

#include <iostream>
#include "console.h"
using namespace std;

int Combinations(int n, int k) {
	if(n <= 1 || k == 0 || k == n) return 1;

	return Combinations(n-1,k) + Combinations(n-1, k-1);
}

int main() {
    // [TODO: fill in the code]

	int x = Combinations(7,3); // must be 35
	cout << x << endl;

    return 0;
}
