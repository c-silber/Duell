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

				if (top == dist) {
					cout << "I CAN WIN BY MOVING PIECE AT: " << getRow(i) << "," << j << endl;
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
