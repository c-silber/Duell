#include "Board.h"
#include <string>
using namespace std;

Board::Board()
{
	//initialize the board to contain all 0s
	for (int i = 1; i < 9; i++) {
		for (int j = 1; j < 10; j++) {
			boardArray[i][j] = "0";
		}
	}

	boardArray[8][0] = "(1)";
	boardArray[7][0] = "(2)";
	boardArray[6][0] = "(3)";
	boardArray[5][0] = "(4)";
	boardArray[4][0] = "(5)";
	boardArray[3][0] = "(6)";
	boardArray[2][0] = "(7)";
	boardArray[1][0] = "(8)";

	boardArray[0][1] = "(1)";
	boardArray[0][2] = "(2)";
	boardArray[0][3] = "(3)";
	boardArray[0][4] = "(4)";
	boardArray[0][5] = "(5)";
	boardArray[0][6] = "(6)";
	boardArray[0][7] = "(7)";
	boardArray[0][8] = "(8)";
	boardArray[0][9] = "(9)";

	// fill the top row with the computer player dice
	boardArray[1][1] = "C56";
	boardArray[1][2] = "C15";
	boardArray[1][3] = "C21";
	boardArray[1][4] = "C62";
	boardArray[1][5] = "C11";
	boardArray[1][6] = "C62";
	boardArray[1][7] = "C21";
	boardArray[1][8] = "C15";
	boardArray[1][9] = "C56";

	// fill the bottom row with the human player dice
	boardArray[8][1] = "H56";
	boardArray[8][2] = "H15";
	boardArray[8][3] = "H21";
	boardArray[8][4] = "H62";
	boardArray[8][5] = "H11";
	boardArray[8][6] = "H62";
	boardArray[8][7] = "H21";
	boardArray[8][8] = "H15";
	boardArray[8][9] = "H56";
}

// method that the returns the Duell board
string Board::getBoard(int i, int j) {
	return boardArray[i][j];
}


Board::~Board()
{
}


string boardArray[9][10];