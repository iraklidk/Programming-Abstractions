/*
 * File: WordLadder.cpp
 * --------------------------
 * Name: [TODO: enter name here]
 * Section: [TODO: enter section leader here]
 * This file is the starter project for the Word Ladder problem.
 * [TODO: rewrite the documentation]
 */

#include <iostream>
#include <string>
#include "console.h"
#include "simpio.h"
#include "queue.h"
#include "vector.h"
#include "lexicon.h"
#include "map.h"
using namespace std;

bool diffByOneLetter(string a, string b) {
	int count = 0;
	for(int i = 0; i < a.size(); i++) {
		if(a[i] != b[i]) count++;
		if(count > 1) return false;
	}

	return (count == 1);
}

void printVector(Vector<string>& vec) {
	if(vec.size() == 0) {
		cout << "No ladder found." << endl; 
	}else {
		cout << "Found Ladder: ";
	foreach(string s in vec) {
		cout << s << " ";
		}
	cout << endl;
	}
}

Vector<string> foundSmallestVector(Vector<Vector<string>>& vec) {
	Vector<string> ans;
	for(int i = 0; i < vec.size()-2; i++) {
		if(vec[i].size() > vec[i+1].size()) 
			ans = vec[i];
		else
			ans = vec[i+1];
	}

	return ans;
}

Vector<string> validWords(Lexicon& lex, string startWord) {
	Vector<string> vec;
	for(int i = 0; i < startWord.size(); i++) {
		for(int ch = 'a'; ch <= 'z'; ch++) {
			string tmp = startWord;
			if(startWord[i] != ch) {
				tmp[i] = ch;
				if(lex.contains(tmp))
					vec.push_back(tmp);
			}
		}
	}
	return vec;
}

void foundShortest(string startWord, string destinationWord) {
	Lexicon englishWords("EnglishWords.dat");
	Vector<string> solution;
	Vector<string> vec(1, startWord);
	Queue<Vector<string>> q;
	Lexicon usedWords;
	q.enqueue(vec);
	englishWords.add(startWord);
	bool f = false;
	while(!q.isEmpty() && !f) {
		Vector<string> first = q.dequeue();
		Vector<string> validArr = validWords(englishWords, first[first.size()-1]);
		foreach(string word in validArr) {

			if(!usedWords.contains(word)) {
				usedWords.add(word);
				Vector<string> tmp = first;
				tmp.push_back(word);
				q.enqueue(tmp);
				if(word == destinationWord) {
					first.push_back(word);
					solution = first;
					f = true;
					break;
				}

			}
		}
	}
	
	printVector(solution);
}

void foundLadder(string startWord, string destinationWord) {
	if(startWord.length() != destinationWord.length())
		cout << "No ladder found." << endl;
	else{
		foundShortest(startWord, destinationWord);
	}
}

int main() {

	while(true) {
		string startWord = getLine("Enter start word (RETURN to quit): ");
		if(startWord == "") break;
		string destinationWord = getLine("Enter destination word: ");
		foundLadder(startWord, destinationWord);
	}

    return 0;
}