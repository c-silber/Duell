#pragma once
#include <string>
#include <fstream>
#include "Board.h"
#include "Tournament.h"
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
	void getKey();
	int getHumanKeyRow();
	int getHumanKeyColumn();
	int getComputerKeyRow();
	int getComputerKeyColumn();

	// Function that ensures the user is moving to a legitimate space on the board
	string validateDiceRoll(string sourceDie, int sourceRow, int sourceColumn, int destRow, int destColumn);

	bool frontalMove(int sourceRow, int sourceColumn, int destRow, int destColumn);
	bool lateralMove(int sourceRow, int sourceColumn, int destRow, int destColumn);
	void setHumanKeyRow(int i);
	void setHumanKeyColumn(int j);
	void setComputerKeyRow(int i);
	void setComputerKeyColumn(int j);
	void initiateSerialization(int humanWins, int computerWins, char nextPlayer);
	bool resumeSerialization(string textFile, Tournament &t);

	const int MIN_ROW = 1;
	const int MIN_COLUMN = 1;
	const int MAX_ROW = 8;
	const int MAX_COLUMN = 9;

	~BoardView();
private:
	string boardArray[9][10];
	int humanKeyRow, humanKeyColumn, computerKeyRow, computerKeyColumn;
};

