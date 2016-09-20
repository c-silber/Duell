#include "BoardView.h"
#include "Die.h"
#include <string>
#include <iomanip>
#include <iostream>
using namespace std;

BoardView::BoardView()
{

}

// Function that sets the value of each position on the Duell board
void BoardView::setValue(int i, int j, string bVal) {
	boardArray[i][j] = bVal;
}

void BoardView::getKey(string opponent, int &row, int &column) {
	for (int i = 1; i < 9; i++) {
		for (int j = 1; j < 10; j++) {
			string val = getValue(i, j);
			if (val == opponent) {
				row = i;
				column = j;
			}
		}
	}
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

bool BoardView::frontalMove(bool up, bool right, int sourceRow, int sourceColumn, int destRow, int destColumn) {
	string val;
	// if we are moving up
	if (up == true) {
		while (sourceRow > destRow) {
			val = getValue((sourceRow + 1), sourceColumn);
			if (val != "0") {
				return false;
			}
			sourceRow++;
		}
	}
	// if not, we are moving down
	else {
		while (sourceRow < destColumn) {
			val = getValue((sourceRow - 1), sourceColumn);
			if (val != "0") {
				return false;
			}
			sourceRow--;
		}
	}
	// if we are moving right
	if (right == true) {
		while (sourceColumn < destColumn) {
			val = getValue(destRow, sourceColumn);
			if (val != "0") {
				return false;
			}
			sourceColumn++;
		}
	}
	// if not, we are moving left
	else {
		while (sourceColumn > destColumn) {
			val = getValue(destRow, sourceColumn);
			if (val != "0") {
				return false;
			}
			sourceColumn--;
		}
	}
	return true;
}

bool BoardView::lateralMove(bool up, bool right, int sourceRow, int sourceColumn, int destRow, int destColumn) {
	string val;
	if (right == true) {
		while (sourceColumn < destColumn) {
			val = getValue(sourceRow, (sourceColumn + 1));
			if (val != "0") {
				return false;
			}
			sourceColumn++;
		}
	}
	// if not, we are moving left
	else {
		while (sourceColumn > destColumn) {
			val = getValue(sourceRow, (sourceColumn - 1));
			if (val != "0") {
				return false;
			}
			sourceColumn--;
		}
	}
	if (up == true) {
		while ((sourceRow + 1) > (destRow)) {
			val = getValue(sourceRow, sourceColumn);
			if (val != "0") {
				return false;
			}
			sourceRow++;
		}
	}
	// if not, we are moving down
	else {
		while (sourceRow < destColumn) {
			val = getValue((sourceRow - 1), sourceColumn);
			if (val != "0") {
				return false;
			}
			sourceRow--;
		}
	}
	return true;
}
























BoardView::~BoardView()
{
}