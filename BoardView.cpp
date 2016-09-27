#include "BoardView.h"
#include "Die.h"
#include "Tournament.h"
#include <string>
#include <iomanip>
#include <sstream>
#include <iostream>
using namespace std;

BoardView::BoardView()
{
	humanKeyRow = 0, humanKeyColumn = 0, computerKeyRow = 0, computerKeyColumn = 0;
}

// Function that sets the value of each position on the Duell board
void BoardView::setValue(int i, int j, string bVal) {
	boardArray[i][j] = bVal;
}

void BoardView::getKey() {
	for (int i = 1; i < 9; i++) {
		for (int j = 1; j < 10; j++) {
			string val = getValue(i, j);
			if (val == "H11") {
				setHumanKeyRow(i);
				setHumanKeyColumn(j);
			}
			if (val == "C11") {
				setComputerKeyRow(i);
				setComputerKeyColumn(j);
			}
		}
	}
}

void BoardView::setHumanKeyRow(int i) {
	humanKeyRow = i;
}

void BoardView::setHumanKeyColumn(int j) {
	humanKeyColumn = j;
}

void BoardView::setComputerKeyRow(int i) {
	computerKeyRow = i;
}

void BoardView::setComputerKeyColumn(int j) {
	computerKeyColumn = j;
}


int BoardView::getHumanKeyRow() {
	return humanKeyRow;
}

int BoardView::getHumanKeyColumn() {
	return humanKeyColumn;
}

int BoardView::getComputerKeyRow() {
	return computerKeyRow;
}

int BoardView::getComputerKeyColumn() {
	return computerKeyColumn;
}

// Function that returns a specific position
string BoardView::getValue(int i, int j) {
	return boardArray[i][j];
}

// Function that prints the current Duell board
void BoardView::printBoard() {
	for (int i = 0; i < 9; i++) {
		for (int j = 0; j < 10; j++) {
			cout << left << setw(5) << boardArray[i][j] << " ";
		}
		cout << endl;
	}
}

string BoardView::validateSource(int row, int column) {
	if (row > MAX_ROW || row < MIN_ROW || column > MAX_COLUMN || column < MIN_COLUMN) {
		return "INVALID ROW OR COLUMN. TRY AGAIN";
	}
	string sourceDie = getValue(row, column);
	sourceDie = sourceDie.at(0);
	if (sourceDie != "H") {
		return "YOU HAVE NOT SELECTED A VALID DIE. TRY AGAIN";
	}
	return "SUCCESS";
}


string BoardView::validateDiceRoll(string sourceDie, int sourceRow, int sourceColumn, int destRow, int destColumn) {
	if (destRow > MAX_ROW || destRow < MIN_ROW || destColumn > MAX_COLUMN || destColumn < MIN_COLUMN) {
		return "INVALID ROW OR COLUMN. TRY AGAIN";
	}

	// Make sure that the die is not being moved to an occupied spot
	string destDie = getValue(destRow, destColumn);
	if (destDie.at(0) == sourceDie.at(0)) {
		return "YOU CANNOT MOVE YOUR DIE TO AN OCCUPIED SPACE. TRY AGAIN";
	}

	int sourceNum = int(sourceDie.at(1) - '0');
	int distRow, distColumn;

	if (destColumn > sourceColumn) {
		distColumn = destColumn - sourceColumn;
	}
	else {
		distColumn = sourceColumn - destColumn;
	}

	if (destRow > sourceRow) {
		distRow = destRow - sourceRow;
	}
	else {
		distRow = sourceRow - destRow;
	}

	int dist = distRow + distColumn;
	char direction;

	if (dist != sourceNum) {
		return "INCORRECT NUMBER OF SPACES MOVED. TRY AGAIN.";
	}

	return "SUCCESS";
}

bool BoardView::frontalMove(int sourceRow, int sourceColumn, int destRow, int destColumn) {

	// frontal - move up or down first and then left or right
	// Move: 1,4 -> 4,7
	// Converted Move: 8,4 -> 5,7
	// first: check all spaces between 7,4 and 5,4
	// second: check all the spaces from 5,4 and 5,6

	// If this is the case, only moving frontally
	if (sourceColumn == destColumn && sourceRow > destRow) {
		destRow += 1;
	}
	else if (sourceColumn == destColumn && sourceRow < destRow) {
		destRow -= 1;
	}

	int sRow = sourceRow - 1;
	if (sourceRow > destRow && sRow != destRow) { // if this is true, we are moving up
		while (sRow + 1 > destRow) {	// while source Row - 1 (7) is greater than dest Row (5)
			string val = getValue(sRow, sourceColumn);
			if (val != "0") {
				return false;
			}
			sRow--;
		}
	}

	// Move: 4,7 -> 1,4
	// Converted Move: 5,7 -> 8,4
	// first: check all spaces between 6,7 and 8,7
	// second: check all the spaces from 8,7 and 8,5
	sRow = sourceRow + 1;
	if (sourceRow < destRow) {		// if this is true, we are moving down
		while ((sRow - 1) < destRow) {
			string val = getValue(sRow, sourceColumn);
			if (val != "0") {
				return false;
			}
			sRow++;
		}
	}

	// 4,5 -> 4,9
	int dColumn = destColumn - 1;
	if (sourceColumn < destColumn) {	// if this is true, moving right
		while (sourceColumn < dColumn) {
			string val = getValue(destRow, dColumn);
			if (val != "0") {
				return false;
			}
			dColumn--;
		}
	}

	dColumn = destColumn + 1;
	if (sourceColumn > destColumn) {
		while (sourceColumn > dColumn) {
			string val = getValue(destRow, dColumn);
			if (val != "0") {
				return false;
			}
			dColumn++;
		}
	}

	return true;
}

bool BoardView::lateralMove(int sourceRow, int sourceColumn, int destRow, int destColumn) {

	int sColumn = sourceColumn + 1;
	if (sourceColumn < destColumn) {	// if this is true, moving right
		while (sColumn < destColumn) {
			string val = getValue(sourceRow, sColumn);
			if (val != "0") {
				return false;
			}
			sColumn++;
		}
	}

	sColumn = sourceColumn - 1;
	if (sourceColumn > destColumn) {
		while (sColumn > destColumn) {
			string val = getValue(sourceRow, sColumn);
			if (val != "0") {
				return false;
			}
			sColumn--;
		}
	}

	int sRow = sourceRow;
	if (sourceRow > destRow) { // if this is true, we are moving up
		while (sRow > destRow) {	// while source Row - 1 (7) is greater than dest Row (5)
			string val = getValue(sRow, destColumn);
			if (val != "0") {
				return false;
			}
			sRow--;
		}
	}

	// Move: 4,7 -> 1,4
	// Converted Move: 5,7 -> 8,4
	// first: check all spaces between 6,7 and 8,7
	// second: check all the spaces from 8,7 and 8,5
	sRow = sourceRow;
	if (sourceRow < destRow) {		// if this is true, we are moving down
		while (sRow < destRow) {
			string val = getValue(sRow, destColumn);
			if (val != "0") {
				return false;
			}
			sRow++;
		}
	}

	return true;
}

void BoardView::initiateSerialization(int humanWins, int computerWins, char nextPlayer) {
	string next;
	if (nextPlayer == 'H') {
		next = "Human";
	}
	else {
		next = "Computer";
	}

	time_t now = time(0);
	tm *ltm = localtime(&now);

	string fileName = "Duell" + to_string(1 + ltm->tm_mon) + "/" + to_string(ltm->tm_mday);
	cout << fileName << endl;
	ofstream myfile;
	myfile.open("Duell.txt");
	myfile << "Board:" << endl;
	for (int i = 1; i < 9; i++) {
		for (int j = 1; j < 10; j++) {
			myfile << getValue(i, j);
			if (j != 9) { myfile << "	"; }
		}
		myfile << endl;
	}
	myfile << endl;
	myfile << "Computer Wins: " << computerWins << endl;
	myfile << endl;
	myfile << "Human Wins: " << humanWins << endl;
	myfile << endl;
	myfile << "Next Player: " << next << endl;
	myfile.close();
}

bool BoardView::resumeSerialization(string textFile, Tournament &t) {

	Board b;

	for (int i = 0; i < 9; i++) {
		for (int j = 0; j < 10; j++) {
			setValue(i, j, b.getBoard(i, j));
		}
	}

	ifstream file(textFile);
	stringstream buffer;

	buffer << file.rdbuf();

	file.close();

	char delim = ':';
	string token = buffer.str().substr(0, buffer.str().find(delim));
	int count = token.length() + 1;

	int row = 1, column = 1, loc;
	for (loc = count; loc < buffer.str().size(); loc++) {
		if (row == 9 && column == 1) {
			break;
		}

		char term = buffer.str()[loc];
		if (term == '\t' || isspace(term) || term == '\n') {
			continue;
		}
		else {
			if (term == '0') {
				setValue(row, column, "0");
				column++;
				if (column == 10) {
					column = 1;
					row++;
				}
			}
			else {
				string thisTerm = to_string(term);
				if (thisTerm == "67") {
					thisTerm = "C";
					thisTerm += buffer.str()[loc + 1];
					thisTerm += buffer.str()[loc + 2];
				}
				else {
					thisTerm = "H";
					thisTerm += buffer.str()[loc + 1];
					thisTerm += buffer.str()[loc +2];
				}
				setValue(row, column, thisTerm);
				column++;
				if (column == 10) {
					column = 1;
					row++;
				}
				loc += 2;
			}
		}
	}

	printBoard();

	count = buffer.str().find(':', loc);
	count += 1;
	
	for (loc = count; loc < buffer.str().size(); loc++) {
		char term = buffer.str()[loc];
		if (term == '\t' || isspace(term) || term == '\n') {
			continue;
		}
		else {
			t.setComputerScore(term - '0');
			break;
		}
	}

	count = buffer.str().find(':', loc);
	count += 1;

	for (loc = count; loc < buffer.str().size(); loc++) {
		char term = buffer.str()[loc];
		if (term == '\t' || isspace(term) || term == '\n') {
			continue;
		}
		else {
			t.setHumanScore(term - '0');
			break;
		}
	}

	count = buffer.str().find(':', loc);
	count += 1;

	for (loc = count; loc < buffer.str().size(); loc++) {
		char term = buffer.str()[loc];
		if (term == 'C') {
			return 1;
		}
		if (term == 'H') {
			return 0;
		}
	}
}


BoardView::~BoardView()
{
}