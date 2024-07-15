/*
 * File: RandomSubsets.cpp
 * ----------------------
 * Name: [TODO: enter name here]
 * Section: [TODO: enter section leader here]
 * This file is the starter project for the Random Subsets problem
 * on Assignment #3.
 * [TODO: extend the documentation]
 */

#include <iostream>
#include "set.h"
#include "random.h"
#include "console.h"
#include "simpio.h"
using namespace std;

/* Given a set of integers, returns a uniformly-random subset of that
 * set.
 */
Set<int> randomSubsetOf(Set<int>& s) {
	if(s.size() == 0) return s;

	int x = s.first();
	if(randomChance(0.5))
		return randomSubsetOf(s - x) + x;

	return randomSubsetOf(s - x);
}

int main() {
	cout << "Lets generated random subset of set." << endl;
	Set<int> set;
	while(true) {
		string s;
		s = getLine("Enter the number or input exit: ");
		if(s == "exit") break;
		int x = stringToInteger(s);
		set.add(x);
	}
	cout << "Generating random subset.."  << endl;
	cout << "Generated random subset is: " << randomSubsetOf(set) << endl;
    return 0;
}
