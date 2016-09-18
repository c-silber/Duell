#pragma once
#include <string>
using namespace std;

// implements the model of the board
class Board
{
public:
	// Board constructor takes no arguments and creates an 8x9 Duell board
	Board();

	// method that the returns the Duell board
	string getBoard(int i, int j);

	~Board();
private:
	string boardArray[9][10];
};

