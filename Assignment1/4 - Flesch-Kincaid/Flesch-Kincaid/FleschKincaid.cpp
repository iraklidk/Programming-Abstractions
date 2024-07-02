/*
 * File: FleschKincaid.cpp
 * ----------------------
 * Name: [TODO: enter name here]
 * Section: [TODO: enter section leader here]
 * This file is the starter project for the Flesch-Kincaid problem.
 * [TODO: rewrite the documentation]
 */

const double C0 = -15.59, C1 = 0.39, C2 = 11.8;


#include <iostream>
#include <fstream>
#include <cctype> 
#include <sstream>
#include "tokenscanner.h"
#include "simpio.h"
#include "console.h"

using namespace std;

int countWords(ifstream& file) {
	TokenScanner scanner(file);
	int apostrophe = 0;
	int count = 0;
	scanner.ignoreWhitespace();
	while(scanner.hasMoreTokens()) {
		string token = scanner.nextToken();
		if(token != "," && token != "." && token != "!" && token != "?" && token != "\"" && token != "-")
		count++;
		if(token == "\'") apostrophe++;
	}
	count -= apostrophe;
	if(count == 0) return 1;

	return count;
}

int countSentences(ifstream& file) {
	TokenScanner scanner(file);
	scanner.ignoreWhitespace();
	int count = 0;
	while(scanner.hasMoreTokens()) {
		string token = scanner.nextToken();
		if(token == "," || token == "?" || token == "!" || token == ".")
			count++;
	}
	if(count == 0) return 1;

	return count;
}

int countVowel(ifstream& file) {
	TokenScanner scanner(file);
	scanner.ignoreWhitespace();
	int count = 0;
	while(scanner.hasMoreTokens()) {
		string token = scanner.nextToken();
		for(int i = 0; i < token.length(); i++) {
			if(token[i] == 'a' || token[i] == 'e' || token[i] == 'i' || token[i] == 'o' || token[i] == 'u' || token[i] == 'y') {
				if(token[i] == 'e' && i == token.length()-1) continue;
				if(token[i+1] == 'a' || token[i+1] == 'e' || token[i+1] == 'i' || token[i+1] == 'o' || token[i+1] == 'u' || token[i+1] == 'y')
					continue;
				count++;
			}
		}
	}

	return count;
}

double calculateGrade(ifstream& file) {
	
	int vowel = countVowel(file);
	cout << vowel << endl;
	file.clear();             
	file.seekg(0, ios::beg);
	int sentences = countSentences(file);
	file.clear();             
	file.seekg(0, ios::beg);
	cout << sentences << endl;
	int words = countWords(file);
	cout << words << endl;
	

	double grade = C0 + C1 * ((double)words / sentences) + C2 * ((double)vowel / words);

	return grade;
}


int main() {
	
	ifstream file("JFK-Berlin.txt");	
	double x = calculateGrade(file);
	cout << x << endl;

    return 0;
}
