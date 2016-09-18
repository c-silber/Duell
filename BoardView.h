#pragma once
#include <string>
#include "Board.h"
using namespace std;

class BoardView
{
public:
	BoardView();

	// Function that sets the value of each position on the Duell board
	void setValue(int i, int j, string bVal);

	// Function that returns a specific position
	string getValue(int i, int j);

	// Function that prints the current Duell board
	void printBoard();

	string validateSource(int row, int column);

	// Get the location of the opponents key piece
	void getKey(string opponent, int &row, int &column);

	// Function that ensures the user is moving to a legitimate space on the board
	string validateDiceRoll(string sourceDie, int sourceRow, int sourceColumn, int destRow, int destColumn);

	const int MIN_ROW = 1;
	const int MIN_COLUMN = 1;
	const int MAX_ROW = 8;
	const int MAX_COLUMN = 9;

	~BoardView();
private:
	string boardArray[9][10];
};

