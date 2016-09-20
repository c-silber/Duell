#include "Computer.h"
#include <string>
#include <iostream>
using namespace std;

Computer::Computer()
{
}

int Computer::playerStrategy(BoardView &bv) {
	int top;

	int opRow, opColumn;
	bv.getKey("H11", opRow, opColumn);
	int myRow, myColumn;
	bv.getKey("C11", myRow, myColumn);

	for (int i = 1; i < 9; i++) {
		for (int j = 1; j < 10; j++) {
			string val = bv.getValue(i, j);
			if (val == "0") {
				continue;
			}
			else if (val.at(0) == 'C') {
				int distanceToKeyRow = i - opRow;
				int distanceToKeyColumn = j - opColumn;
				int dist = abs(distanceToKeyRow) + abs(distanceToKeyColumn);
				top = int(val.at(1) - '0');
				bool isValid;

				if (top == dist) {
					Die c(val.at(1) - '0', val.at(2) - '0');
					// Computer has a piece that can be moved to win. Check if Computer can move that piece frontally or laterally
					if (i == opRow) {
						// my piece is in the same row (need to move laterally)
						bool right = false;
						if (j > opColumn) { right = true; }
						isValid = lateralOnly(bv, right, i, opColumn, j, opRow);
						if (isValid) {
							c.rollDie(0, abs(opColumn - j), 0, 0);

							int topDie = c.getTop();
							int rightDie = c.getRight();
							string newVal = val.at(0) + to_string(topDie) + to_string(rightDie);

							//bv.setValue(i, j, "0");
							//bv.setValue(opRow, opColumn, newVal);
							//cout << endl;
							//bv.printBoard();
							//return 1;
						}
						
					}
					else if (j == opColumn) {
						// my piece is in the same column (need to move frontally)
						bool up = false;
						if (i > opRow) { up = true; }

						isValid = frontOnly(bv, up, j, opColumn, i, opRow);
						if (isValid) {
							c.rollDie(abs(opRow - i), 0, up, 0);

							int topDie = c.getTop();
							int rightDie = c.getRight();
							string newVal = val.at(0) + to_string(topDie) + to_string(rightDie);

							//bv.setValue(i, j, "0");
							//bv.setValue(opRow, opColumn, newVal);
							//cout << endl;
							//bv.printBoard();
							//return 1;
						}
					}
					
					else {
						int count = (top - 1), up = false, right = false;
						// try moving die frontally / laterally and check if able to win
							if (j < opColumn) { right = true; }
							if (i > opRow) { up = true; }
							isValid = bv.lateralMove(up, right, i, j, opRow, opColumn);
							if (isValid) {
								c.rollDie(abs(opRow - i), abs(opColumn - j), up, 'l');

								int topDie = c.getTop();
								int rightDie = c.getRight();
								string newVal = val.at(0) + to_string(topDie) + to_string(rightDie);
								bv.setValue(i, j, "0");
								bv.setValue(opRow, opColumn, newVal);
								cout << endl;
								bv.printBoard();
								return 1;
							}

							isValid = bv.frontalMove(up, right, i, j, opRow, opColumn);
							if (isValid) {
								c.rollDie(abs(opRow - i), abs(opColumn - j), up, 'f');

								int topDie = c.getTop();
								int rightDie = c.getRight();
								string newVal = val.at(0) + to_string(topDie) + to_string(rightDie);
								bv.setValue(i, j, "0");
								bv.setValue(opRow, opColumn, newVal);
								cout << endl;
								bv.printBoard();
								return 1;
							}

					}
				}
				else {
					// try all possible moves in the direction of the key piece and determine if any combination of frontal/lateral moves will
					// get us to the key piece
					// top == 5
					// if i > opRow: move right, otherwise move left, if j > opColumn: move down, otherwise move up
					// try: frontal: top - 1 lateral: 0 + 1; top > 0
					// try: frontal: top - 2 lateral: 0 + 2; top > 0
					// try: frontal: top - n lateral: 0 + n; top > 0
					// try: lateral: top - 1; frontal: 0 + 1; top > 0
				}
			}
			else if (val.at(0) == 'H') {
				int distanceToMyKeyRow = i - myRow;
				int distanceToMyKeyColumn = j - myColumn;
				int myDist = abs(distanceToMyKeyRow) + abs(distanceToMyKeyColumn);
				top = int(val.at(1) - '0');
				if (top == myDist) {
					cout << "YOU CAN WIN BY MOVING PIECE AT: " << getRow(i) << "," << j << endl;
				}
			}
		}
	}
	return 0;
}

string Computer::getMoves(int row, int column, string value) {
	cout << "COMPUTER HAS A DIE AT " << row << ", " << column << endl;
	cout << "POSSIBLE MOVES: " << endl;

	// Function that ensures the user is moving to a legitimate space on the board

	// Function to get the new value for the die once it can move
	string getNewDieVal(string sourceDie, int sourceRow, int sourceColumn, int destRow, int destColumn);
	

	// 5 = 5 + 0
	// 5 = 0 + 5
	// 5 = 4 + 1
	// 5  = 1 + 4
	// 5 =  3 + 2
	// 5 = 2 + 3
	
	return "HI";
}


Computer::~Computer()
{
}
