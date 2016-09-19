#include "Human.h"
#include <iostream>
using namespace std;

Human::Human()
{
}

int Human::playerStrategy(BoardView &bv) {
	
	int cRow, cColumn;
	string validSrc;
	bool up = false, right = false;
	do {

		cout << "H: CHOOSE A DIE TO MOVE (ROW AND COLUMN) - ";
		cin >> cRow >> cColumn;
		while (cin.fail())
		{
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			cout << "INVALID ENTRY. TRY AGAIN - ";
			cin >> cRow >> cColumn;
		}
		validSrc = bv.validateSource(getRow(cRow), cColumn);
		if (validSrc != "SUCCESS") {
			cout << validSrc << endl;
		};
	} while (validSrc != "SUCCESS");

	int cRow2, cColumn2; 
	string validDest, validRolls;
	char direction = 'n';
	do {
		cout << "SELECT THE LOCATION TO MOVE TO (ROW AND COLUMN) - ";
		cin >> cRow2 >> cColumn2;
		while (cin.fail())
		{
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			cout << "INVALID ENTRY. TRY AGAIN - ";
			cin >> cRow2 >> cColumn2;
		}
		if (cRow2 > cRow) {
			up = true;
		}
		if (cColumn2 > cColumn) {
			right = true;
		}
		validRolls = bv.validateDiceRoll(bv.getValue(getRow(cRow), cColumn), getRow(cRow), cColumn, getRow(cRow2), cColumn2);
		if (validRolls != "SUCCESS") {
			cout << validRolls << endl;
		}
		if (validRolls == "SUCCESS") {
			if (cColumn != cColumn2 && cRow != cRow2) {
				// check if there are any possible moves for the given destination
				if (frontalMove(bv, up, right, cRow, cColumn, cRow2, cColumn2) == false &&
					lateralMove(bv, up, right, cRow, cColumn, cRow2, cColumn2) == false) {
					cout << "THERE ARE NO POSSIBLE MOVES FOR THIS DESTINATION. PLEASE TRY AGAIN." << endl;
					validRolls = "TRYAGAIN";
				}
			}
			else {
				// if the piece is moving only laterally or frontally, make sure it does not roll over any other dice
				if (cColumn == cColumn2) {
					bool isValid = frontOnly(bv, up, cColumn, cColumn2, cRow, cRow2);
					if (isValid == false) {
						cout << "CANNOT MOVE OVER ANOTHER DIE" << endl;
						validRolls = "TRYAGAIN";
					}
				}
				if (cRow == cRow2) {
					bool isValid = lateralOnly(bv, right, cColumn, cColumn2, cRow, cRow2);
					if (isValid == false) {
						cout << "CANNOT MOVE OVER ANOTHER DIE" << endl;
						validRolls = "TRYAGAIN";
					}
				}
			}
		}
	} while (validRolls != "SUCCESS");
	

	if (cColumn != cColumn2 && cRow != cRow2) {
		bool isValid = true;
		do {
			do {
				cout << "WHICH DIRECTION DO YOU WANT TO MOVE FIRST (F/L): ";
				cin >> direction;
			} while (direction != 'l' && direction != 'L' && direction != 'f' && direction != 'F');

			// check if there are dice on the path
			if (direction == 'f' || direction == 'F') {
				isValid = frontalMove(bv, up, right, cRow, cColumn, cRow2, cColumn2);
				if (isValid == false) {
					cout << "CANNOT MOVE OVER ANOTHER DIE" << endl;
				}
			}
			else if (direction == 'l' || direction == 'L') {
				isValid = lateralMove(bv, up, right, cRow, cColumn, cRow2, cColumn2);
				if (isValid == false) {
					cout << "CANNOT MOVE OVER ANOTHER DIE" << endl;
				}
			}
		} while (isValid == false);
	}


	string destValue = bv.getValue(getRow(cRow2), cColumn2);

	string sourceDie = bv.getValue(getRow(cRow), cColumn);
	int topNum = int(sourceDie.at(1) - '0');
	int rightNum = int(sourceDie.at(2) - '0');

	int frontal = cRow2 - cRow;
	int lateral = cColumn2 - cColumn;

	Die d(topNum, rightNum);
	d.rollDie(frontal, lateral, up, direction);

	int topDie = d.getTop();
	int rightDie = d.getRight();
	string newVal = sourceDie.at(0) + to_string(topDie) + to_string(rightDie);

	bv.setValue(getRow(cRow), cColumn, "0");
	bv.setValue(getRow(cRow2), cColumn2, newVal);

	if (destValue == "C11") {
		return 1;
	}

	return 0;
}

Human::~Human()
{
}
