/*
 * File: Subsequences.cpp
 * ----------------------
 * Name: [TODO: enter name here]
 * Section: [TODO: enter section leader here]
 * This file is the starter project for the Subsequences problem
 * on Assignment #3.
 * [TODO: extend the documentation]
 */

#include <iostream>
#include <string>
#include "console.h"
#include "simpio.h"
using namespace std;

/* Given two strings, returns whether the second string is a
 * subsequence of the first string.
 */
bool isSubsequence(string text, string subsequence) {
	if(subsequence.size() > text.size()) return false;
	if(text == subsequence) return true;
	if(subsequence.size() == 0) return true;

	if(text[0] == subsequence[0])
		return isSubsequence(text.substr(1), subsequence.substr(1));

	return isSubsequence(text.substr(1), subsequence);
}

int main() {
	while(true) {
		string a = getLine("Enter the first string or input exit: ");
		if(a == "exit") break;
		string b = getLine("Enter the second string: ");
		cout << isSubsequence(a, b) << endl;
	}
    return 0;
}
