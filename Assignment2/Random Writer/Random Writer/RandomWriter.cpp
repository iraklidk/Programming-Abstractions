/*
 * File: RandomWriter.cpp
 * ----------------------
 * Name: [TODO: enter name here]
 * Section: [TODO: enter section leader here]
 * This file is the starter project for the Random Writer problem.
 * [TODO: rewrite the documentation]
 */

#include <algorithm>
#include "console.h"
#include "random.h"
#include "simpio.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <utility>
#include <string>
#include <vector>
#include <string>
#include "map.h"
using namespace std;

void probMapGen(Map<string, Vector<char> >& prob, int markovOrder, ifstream& file) {
	string str;
	char ch;

	for(int i = 0; i < markovOrder; i++) {
		file.get(ch);
		str += ch;
	}

	while(file.get(ch)) {
		prob[str].push_back(ch);
		str = str.substr(1) + ch;
	}
}

string seedFind(Map<string, Vector<char> >& prob) {
	string seed = "";

	Vector<char> vec;

	foreach(string s in prob) {
		if(prob[s].size() > vec.size()) {
			seed = s;
		}
	}
	return seed;
}

void randomTextGen(Map<string, Vector<char> >& prob, int chars) {
	string seed = seedFind(prob);
	for(int i = 0; i < chars; i++) {
		if(prob[seed].isEmpty()) break;
		char ch = prob[seed][randomInteger(0, prob[seed].size()-1)];
		cout.put(ch);
		seed = seed.substr(1) + ch;
	}
}

void mainInterface(int& markovOrder) {
	while(true) {
		string s = getLine("Enter the file: ");
		if(s == "Tom Sawyer" || s == "TomSawyer") break;
		else cout << "Please enter valid filename" << endl;
	}

	while(true) {
		markovOrder = getInteger("Enter the markov order: ");
		if(markovOrder <= 10 && markovOrder >= 1) break;
		else cout << "Enter the valid order" << endl;
	}
}

int main() {
	ifstream file("TomSawyer.txt");
	int markovOrder = 0;
	mainInterface(markovOrder);
	
	Map<string, Vector<char> > prob;
	probMapGen(prob, markovOrder, file);
	randomTextGen(prob, 2000);

    return 0;
}