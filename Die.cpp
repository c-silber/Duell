#include "Die.h"
#include <iostream>
using namespace std;

Die::Die(int topNum, int rightNum)
{
	top = topNum;
	bottom = 7 - top;
	right = rightNum;
	left = 7 - right;
}


// movement - is the die going up or down?
// path should the die be moved laterally before frontally?
void Die::rollDie(int frontal, int lateral, char movement, char path) {
	frontal = abs(frontal);
	if (top == 1 && right == 1) { return; }

	while (frontal > 3) {
		frontal = frontal - 4;
	}

	char direction;
	if (lateral > 0) {
		direction = 'r';
	}
	else {
		direction = 'l';
	}

	if (path == 'l') {
		lateralMoves(lateral, direction);
	}
		int oneRight[4] = { 5, 4, 2, 3 };
		int twoRight[4] = { 6, 3, 1, 4 };
		int threeRight[4] = { 6, 5, 1, 2 };
		int fourRight[4] = { 6, 2, 1, 5 };
		int fiveRight[4] = { 6, 4, 1, 3 };
		int sixRight[4] = { 5 , 3, 2, 4 };

		if (right == 1) {
			top = getValue(oneRight, frontal, movement);
		}
		else if (right == 2) {
			top = getValue(twoRight, frontal, movement);
		}
		else if (right == 3) {
			top = getValue(threeRight, frontal, movement);
		}
		else if (right == 4) {
			top = getValue(fourRight, frontal, movement);
		}
		else if (right == 5) {
			top = getValue(fiveRight, frontal, movement);
		}
		else if (right == 6) {
			top = getValue(sixRight, frontal, movement);
		}
	
	if (path != 'l'){
		lateralMoves(lateral, direction);
	}
	
}

void Die::lateralMoves(int lateral, char direction) {
	if (direction == 'r') {
		while (lateral > 0) {
			int temp = left;
			right = top;
			left = 7 - right;
			top = temp;
			lateral -= 1;
		}
	}
	else if (direction == 'l') {
		while (lateral < 0) {
			int temp = right;
			left = top;
			right = 7 - left;
			top = temp;
			lateral += 1;
		}
	}
}


int Die::getValue(int values[], int frontal, char movement) {
	
	if (movement == 'd') {
		int temp[4];
		temp[0] = values[3];
		temp[1] = values[2];
		temp[2] = values[1];
		temp[3] = values[0];
		values = temp;
	}

	int topDie = frontal;
	for (int i = 0; i < sizeof(values); i++) {
		if (values[i] == top) {
			topDie += i;
		}
	}

	if (topDie > 3) {
		topDie = topDie - 4;
	}

	topDie = values[topDie];
	return topDie;
}

int Die::getTop() {
	return top;
}

int Die::getRight() {
	return right;
}

Die::~Die()
{
}
