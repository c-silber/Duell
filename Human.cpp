#include "Human.h"
#include <iostream>
using namespace std;

Human::Human()
{
}

int Human::playerStrategy(BoardView &bv) {
	
	int cRow, cColumn;
	string validSrc;
	do {
		cout << "H: CHOOSE A DIE TO MOVE (ROW AND COLUMN) - ";
		cin >> cRow >> cColumn;
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
		validRolls = bv.validateDiceRoll(bv.getValue(getRow(cRow), cColumn), getRow(cRow), cColumn, getRow(cRow2), cColumn2);
		if (validRolls != "SUCCESS") {
			cout << validRolls << endl;
		}
		//else {
		//	if (cColumn != cColumn2 && getRow(cRow) != getRow(cRow2)) {
		//		cout << "WHICH DIRECTION DO YOU WANT TO MOVE FIRST (F/L): ";
		//		cin >> direction;
		//	}
		//}
	} while (validRolls != "SUCCESS");
	
	string destValue = bv.getValue(getRow(cRow2), cColumn2);

	string sourceDie = bv.getValue(getRow(cRow), cColumn);
	int topNum = int(sourceDie.at(1) - '0');
	int rightNum = int(sourceDie.at(2) - '0');

	int frontal = cRow2 - cRow;
	int lateral = cColumn2 - cColumn;

	Die d(topNum, rightNum);
	d.rollDie(frontal, lateral, 'd', direction);

	int top = d.getTop();
	int right = d.getRight();
	string newVal = sourceDie.at(0) + to_string(top) + to_string(right);

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
