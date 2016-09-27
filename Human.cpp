#include "Human.h"
#include <iostream>
using namespace std;

Human::Human()
{
}

int Human::playerStrategy(BoardView &bv) {
	char suggestion;
	cout << "WOULD YOU LIKE A SUGGESTION? (y/n) ";
	cin >> suggestion;
	if (suggestion == 'Y' || suggestion == 'y') {
		computerStrategy(bv, 'H');
		cout << computerMessage << endl;
	}

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
			bool validFrontal = bv.frontalMove(getRow(cRow), cColumn, getRow(cRow2), cColumn2);
			bool validLateral = bv.lateralMove(getRow(cRow), cColumn, getRow(cRow2), cColumn2);

			if (!validFrontal && !validLateral) {
				cout << "THERE ARE NO POSSIBLE MOVES FOR THIS DESTINATION. PLEASE TRY AGAIN." << endl;
				validRolls = "NO MOVES";
			}
			else if (!validFrontal && validLateral) {
				direction = 'l';
			}
			else if (validFrontal && !validLateral) {
				direction = 'f';
			}
			else if (validFrontal && validLateral) {
				do {
					cout << "WHICH DIRECTION DO YOU WANT TO MOVE FIRST (F/L): ";
					cin >> direction;
				} while (direction != 'l' && direction != 'L' && direction != 'f' && direction != 'F');
			}
		}
	} while (validRolls != "SUCCESS");

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

	if (cRow2 == 8 && cColumn2 == 5) {
		return 1;
	}
	return 0;
}

Human::~Human()
{
}
