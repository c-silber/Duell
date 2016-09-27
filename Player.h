#pragma once
#include "Boardview.h"
#include "Board.h"
#include "Die.h"

class Player
{
public:

	Player();
	//convert user entry for row
	int getRow(int x);
	virtual int playerStrategy(BoardView &bv) { return 0; }

	int computerStrategy(BoardView &bv, char activePlayer);
	void setMove(int sRow, int sColumn, int dRow, int dColumn, string newDieVal, int thisPriority);
	void getMove(BoardView bv, int sourceRow, int sourceColumn, string sourceVal, int top);

	~Player();
protected:
	Board bv;
	int sourceRow, sourceColumn, destRow, destColumn, priority, distance;
	string newDieValue, computerMessage;
};

