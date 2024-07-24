/*
 * File: Boggle.cpp
 * ----------------
 * Name: [TODO: enter name here]
 * Section: [TODO: enter section leader here]
 * This file is the main starter file for Assignment #4, Boggle.
 * [TODO: extend the documentation]
 */

#include <iostream>
#include <cstring>
#include "gboggle.h"
#include "grid.h"
#include "gwindow.h"
#include "lexicon.h"
#include "random.h"
#include "simpio.h"
using namespace std;

/* Constants */

const int BOGGLE_WINDOW_WIDTH = 650;
const int BOGGLE_WINDOW_HEIGHT = 350;
const int bigBoggleSize = 5;
const int standardBoggleSize = 4;

const string STANDARD_CUBES[16]  = {
    "AAEEGN", "ABBJOO", "ACHOPS", "AFFKPS",
    "AOOTTW", "CIMOTU", "DEILRX", "DELRVY",
    "DISTTY", "EEGHNW", "EEINSU", "EHRTVW",
    "EIOSST", "ELRTTY", "HIMNQU", "HLNNRZ"
};
 
const string BIG_BOGGLE_CUBES[25]  = {
    "AAAFRS", "AAEEEE", "AAFIRS", "ADENNN", "AEEEEM",
    "AEEGMU", "AEGMNN", "AFIRSY", "BJKQXZ", "CCNSTW",
    "CEIILT", "CEILPT", "CEIPST", "DDLNOR", "DDHNOT",
    "DHHLOR", "DHLNOR", "EIIITT", "EMOTTT", "ENSSSU",
    "FIPRSY", "GORRVW", "HIPRRY", "NOOTUW", "OOOTTU"
};

const int diri[8] = { -1, 0, 0, 1, -1, -1, 1, 1 }; // Directions
const int dirj[8] = { 0, 1, -1, 0, -1, 1, -1, 1 };

/* Grid of chars ans booleans for store used cells */

Grid<char> board;
Grid<bool> used;

/* Lexicon of english words */

Lexicon englishWords = "EnglishWords.dat";

/* Sets of collected words, by human and computer */

Set<string> humansWords;
Set<string> computersWords;

int humanScore = 0;
int computerScore = 0;

/* Function prototypes */

void welcome();
void giveInstructions();
void drawMain();
void drawRelevantBoard();
void setChars();
void setBoardByComputer();
Vector<string> randomizeCopy(Vector<string>& copy);
string upper(string answer);
void setBoardByUser();
bool validString(string s);
bool ifOnTheBoard(string word);
void play();
void human();
bool validWord(string s);
void computer();
void usedRestart();
bool mainCheck(string word, int i, int j);
void wordsByComputer(string sofar, int row, int col);
void unhighlightCubes();
void restart();
void showScores();

/* Main program */

int main() {
	GWindow gw(BOGGLE_WINDOW_WIDTH, BOGGLE_WINDOW_HEIGHT);
    initGBoggle(gw);
    welcome();
    giveInstructions();
	bool endGame = false;
	while(true) {
    drawMain();
	play();
	showScores();
	while(true) {
		string s = getLine("Would you like to play again?: ");
		s = upper(s);
		if(s == "NO") {endGame = true; break;}
		if(s == "YES") {restart(); break;}
		cout << "Please enter yes or no. " << endl;
		}
		if(endGame){
			cout << "Good Luck!" << endl;
			break;
		}
	}
    return 0;
}

/*
 * Function: welcome
 * Usage: welcome();
 * -----------------
 * Print out a cheery welcome message.
 */

void welcome() {
    cout << "Welcome!  You're about to play an intense game ";
    cout << "of mind-numbing Boggle.  The good news is that ";
    cout << "you might improve your vocabulary a bit.  The ";
    cout << "bad news is that you're probably going to lose ";
    cout << "miserably to this little dictionary-toting hunk ";
    cout << "of silicon.  If only YOU had a gig of RAM..." << endl << endl;
}

/*
 * Function: giveInstructions
 * Usage: giveInstructions();
 * --------------------------
 * Print out the instructions for the user.
 */

void giveInstructions() {
    cout << endl;
    cout << "The boggle board is a grid onto which I ";
    cout << "I will randomly distribute cubes. These ";
    cout << "6-sided cubes have letters rather than ";
    cout << "numbers on the faces, creating a grid of ";
    cout << "letters on which you try to form words. ";
    cout << "You go first, entering all the words you can ";
    cout << "find that are formed by tracing adjoining ";
    cout << "letters. Two letters adjoin if they are next ";
    cout << "to each other horizontally, vertically, or ";
    cout << "diagonally. A letter can only be used once ";
    cout << "in each word. Words must be at least four ";
    cout << "letters long and can be counted only once. ";
    cout << "You score points based on word length: a ";
    cout << "4-letter word is worth 1 point, 5-letters ";
    cout << "earn 2 points, and so on. After your puny ";
    cout << "brain is exhausted, I, the supercomputer, ";
    cout << "will find all the remaining words and double ";
    cout << "or triple your paltry score." << endl << endl;
    cout << "Hit return when you're ready...";
    getLine();
}

/*
 Usage: drawMain()
 Main function for visualize the game
*/

void drawMain() {
	drawRelevantBoard();
	setChars();
}

/*
 Usage: drawRelevantBoard()
 Player decides whether to play standard Boggle or Big Boggle and resizes grids
*/

void drawRelevantBoard() {
	cout << "You can play Big Boggle(5x5) or standard Boggle(4x4). " << endl;
	int k = 0;
	while(true) {
		string answer = getLine("Would you like Big Boggle? ");
		answer = upper(answer);
		if(answer == "YES") {
			k = bigBoggleSize;
			break;
		}
		else if(answer == "NO") {
			k = standardBoggleSize;
			break;
		}
		cout << "Please input the valid answer(yes or no)." << endl;
	}
	board.resize(k, k);
	used.resize(k, k);
}

/*
 Usage: setChars()
 Make choice about how to set up the board
*/

string upper(string answer) {
	for(int i = 0; i < answer.size(); i++) {
		answer[i] = toupper(answer[i]);
	}
	return answer;
}

void setChars() {

	cout << "You can choose whether to set up the board yourself or let the computer do it. " << endl;
	bool setByUser;

	while(true) {
		string answer = getLine("Do you want to set up board by yourself?: ");
		answer = upper(answer);
		if(answer == "YES") {
			setByUser = true;
			break;
		}
		if(answer == "NO") {
			setByUser = false;
			break;
		}
		cout << "Please input the valid answer(yes or no)." << endl;
	}

	if(setByUser) setBoardByUser();
	else setBoardByComputer();

	cout << "Well, here we go. ";
}

/*
 Usage: setBoardByComputer()
 Setting the board randomly
*/

void setBoardByComputer() {
	Vector<string> copy;
	int n = board.numCols();

	if(n == bigBoggleSize) {
		for(int i = 0; i < 25; i++) {
			copy.push_back(BIG_BOGGLE_CUBES[i]);
		}
	}

	if(n == standardBoggleSize) {
		for(int i = 0; i < 16; i++) {
			copy.push_back(STANDARD_CUBES[i]);
		}
	}

	copy = randomizeCopy(copy);

	drawBoard(n, n);
	for(int i = 0; i < n; i++) {
		for(int j = 0; j < n; j++) {
			int x = randomInteger(0, 5);
			board[i][j] = copy[i][x];
			labelCube(i, j, copy[i][x]);
		}
	}
}

/*
 Usage: validString(string s)
 Randomizes the vector
*/


Vector<string> randomizeCopy(Vector<string>& copy) {
	for(int i = 0; i < copy.size(); i++) {
		int x = randomInteger(i, copy.size() - 1);
		swap(copy[x], copy[i]);
		
	}
	return copy;
}

/*
 Usage: setBoardByUser()
 Setting the board according to the player configuration
*/

void setBoardByUser() {
	int n = board.numCols();
	Vector<string> cubes;
	int k = 1;

	for(int i = 0; i < n; i++) {
		while(true) {
			cout << "Enter the 6-character symbo for the " << k << "-th row: ";
			string s = getLine();
			if(validString(s)) {
				cubes.push_back(s);
				k++;
				break;
			}
			cout << "The string must contain alphabet letters and be " << n <<" characters long" << endl;
		}
	}

	drawBoard(n, n);
	for(int i = 0; i < n; i++) {
		for(int j = 0; j < n; j++) {
			char ch = toupper(cubes[i][j]);
			board[i][j] = ch;
			labelCube(i, j, ch);
		}
	}
}

/*
 Usage: validString(string s)
 Checks if the entered string is valid for the board
*/

bool validString(string s) {
	int n = board.numCols();
	if(s.size() != n) return false;
	for(int i = 0; i < s.size(); i++) {
		char ch = tolower(s[i]);
		if(ch < 'a' || ch > 'z') return false;
	}
	return true;
}

/*
 Main functions of strategy
*/

void play() {
	human();
	computer();
}

/*
 Human turn
*/

void human() {
	cout << "It's your turn" << endl;
	cout << "If you don't want to continue anymore, press ENTER. " << endl;
	while(true) {
		string word = getLine("Enter the word: ");
		unhighlightCubes();
		if(word.size() == 0){
			cout << "Well done! now it's computer's turn" << endl << endl;
			break;
		}
		word = upper(word);
		if(validWord(word)) {
			if(!humansWords.contains(word)) {
				humansWords.add(word);
				recordWordForPlayer(word, HUMAN);
				humanScore += word.size() - 3;
				cout << "Congratulations! You found new word" << endl;
			}
			else {
				cout << "This word -> " << word << " is already guessed!" << endl;
			}
		}
	}
}

/*
 Usage: validWord(string word)
 Checks if the entered word is at least 4 letters long, if it is on the board, and if it is an English word.
*/

bool validWord(string word) {
	usedRestart();
	if(word.size() < 4){
		cout << "This word is less than 4 letters long" << endl;
		return false;
	}
	if(!englishWords.contains(word)) {
		cout << "This is not an english word" << endl;
		return false;
	}
	if(!ifOnTheBoard(word)) {
		cout << "It's impossible to get this word from the board" << endl;
		return false;
	}

	return true;
}

/*
 Usage: validWord(string word)
 Checks if it is possible to form the word from the given board
*/

bool ifOnTheBoard(string word) {
	int n = board.numCols();
	for(int i = 0; i < n; i++) {
		for(int j = 0; j < n; j++) {
			if(word[0] == board[i][j]) {
				used[i][j] = true;
				highlightCube(i, j, true);
				if(mainCheck(word, i, j)) {
					return true;
				}
				usedRestart();
			}
		}
	}

	return false;
}

/*
 Usage: mainCheck(string word, int i, int j)
 Checks if neighbours satisfies given condition
*/

bool mainCheck(string word, int i, int j) {
	if(word[0] != board[i][j]) return false;
	if(word.size() == 1 && word[0] == board[i][j]) return true;

	int row = 0;
	int col = 0;

	for(int k = 0; k < 8; k++) {
		row = i + diri[k];
		col = j + dirj[k];

		if((row >= 0 && row < board.numCols()) && (col >= 0 && col < board.numCols()) && !used[row][col]) {
			used[row][col] = true;
			if(mainCheck(word.substr(1), row, col)) {
				highlightCube(row, col, true);
				return true;
			}

			used[row][col] = false; // backtrack
		}
	}

	return false;
}

/*
 Usage: usedRestart()
 Fill used grid with falses (restart grid)
*/

void usedRestart() {
	for(int i = 0; i < board.numRows(); i++) {
		for(int j = 0; j < board.numRows(); j++) {
			used[i][j] = false;
		}
	}
}

/*
 Computer turn
*/

void computer() {
	int n = board.numCols();
	for(int i = 0; i < n; i++) {
		for(int j = 0; j < n; j++) {
			string word;
			word += board[i][j];
			usedRestart();
			used[i][j] = true;
			wordsByComputer(word, i, j);
		}
	}
}

/*
 Usage: wordsByComputer(string sofar, int row, int col)
 Finds all rest of words
*/

void wordsByComputer(string sofar, int row, int col) {
	
	if(englishWords.contains(sofar) && sofar.size() >= 4) {
		if(!humansWords.contains(sofar) && !computersWords.contains(sofar)) {
			computersWords.add(sofar);
			computerScore += sofar.size() - 3;
			recordWordForPlayer(sofar, COMPUTER);
		}
	}
	if(!englishWords.containsPrefix(sofar)) return;

	for(int i = 0; i < 8; i++) {
		row += diri[i];
		col += dirj[i];

		if((row >= 0 && row < board.numCols()) && (col >= 0 && col < board.numCols()) && !used[row][col]) {
			used[row][col] = true;
			sofar.push_back(board[row][col]);
			wordsByComputer(sofar, row, col);

			sofar.erase(sofar.size()-1); // backtrack
			used[row][col] = false;
		}
		row -= diri[i]; 
		col -= dirj[i];
	}
}

/*
 Usage: showScores();
 Shows scores in console
*/

void showScores() {
	cout << "GAME OVER ! " << endl << endl;
	cout << "Your score is: " << humanScore << endl;
	cout << "Your words are: ";
	foreach(string str in humansWords){
		cout << str << " ";
	}
	cout << endl << endl;
	cout << "Computer's score is: " << computerScore << endl;
	cout << "Computer's words are: ";
	foreach(string str in computersWords){
		cout << str << " ";
	}
	cout << endl << endl;
}

/*
 Usage: wordsByComputer(string sofar, int row, int col)
 Unhighlight last chosen characters
*/

void unhighlightCubes() {
	for(int i = 0; i < board.numCols(); i++) {
		for(int j = 0; j < board.numCols(); j++) {
			highlightCube(i, j, false);
		}
	}
}

/*
 Usage: restart();
 Resets all data
*/

void restart() {
	usedRestart();
	humanScore = 0;
	computerScore = 0;
	computersWords.clear();
	humansWords.clear();
}