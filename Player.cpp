#include "Player.h"
#include <iostream>
using namespace std;

Player::Player()
{
}

Player::~Player()
{
}

int Player::getRow(int x) {
	switch (x) {
	case 8:
		return 1;
	case 7:
		return 2;
	case 6:
		return 3;
	case 5:
		return 4;
	case 4:
		return 5;
	case 3:
		return 6;
	case 2:
		return 7;
	case 1:
		return 8;
	}
}



bool Player::frontOnly(BoardView &bv, bool up, int sourceColumn, int destColumn, int sourceRow, int destRow) {
	string val;
	if (up == true) {
		while (getRow(sourceRow) > getRow(destRow)) {
			val = bv.getValue(getRow(sourceRow + 1), sourceColumn);
			if (val != "0") {
				return false;
			}
			sourceRow++;
		}
	}
	// if not, we are moving down
	else {
		while (getRow(destRow) > getRow(sourceRow)) {
			val = bv.getValue(getRow(sourceRow - 1), sourceColumn);
			if (val != "0") {
				return false;
			}
			sourceRow--;
		}
	}
	return true;
}

bool Player::lateralOnly(BoardView &bv, bool right, int sourceColumn, int destColumn, int sourceRow, int destRow) {
	string val;
	if (right == true) {
		while (sourceColumn < destColumn) {
			val = bv.getValue(getRow(sourceRow), (sourceColumn + 1));
			if (val != "0") {
				return false;
			}
			sourceColumn++;
		}
	}
	// if not, we are moving left
	else {
		while (sourceColumn > destColumn) {
			val = bv.getValue(getRow(sourceRow), (sourceColumn - 1));
			if (val != "0") {
				return false;
			}
			sourceColumn--;
		}
	}
	return true;
}