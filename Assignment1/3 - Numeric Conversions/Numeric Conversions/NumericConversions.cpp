/*
 * File: NumericConversions.cpp
 * ---------------------------
 * Name: [TODO: enter name here]
 * Section: [TODO: enter section leader here]
 * This file is the starter project for the Numeric Conversions problem.
 * [TODO: rewrite the documentation]
 */

#include <iostream>
#include <string>
#include "console.h"
using namespace std;

/* Function prototypes */

string intToString(int n) {
	if(n == 0) return "0";
	
	if(n <= 9 && n > 0) return string() + char(n + '0');

	if(n < 0) return '-' + intToString(n*-1);
	
	return intToString(n / 10) + char(n % 10 + '0');
}


int stringToInt(string str) { 
	if(str[0] == '-') return stringToInt(str.substr(1, str.length())) * -1;

	if(str.length() == 1) return str[0] - '0';

	return stringToInt(str.substr(0, str.length()-1)) * 10 + str[str.length()-1] - '0';
}

/* Main program */

int main() {
		
	string s = intToString(-19485);
	cout << s << endl;

	int k = stringToInt("1934");
	cout << k << endl;

    return 0;
}
