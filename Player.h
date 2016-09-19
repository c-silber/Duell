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
	//returns true if the move is legal (frontal then lateral)
	bool frontalMove(BoardView &bv, bool up, bool right, int sourceRow, int sourceColumn, int destRow, int destColumn);

	//returns true if the move is legal (lateral then frontal)
	bool lateralMove(BoardView &bv, bool up, bool right, int sourceRow, int sourceColumn, int destRow, int destColumn);

	bool frontOnly(BoardView &bv, bool up, int sourceColumn, int destColumn, int sourceRow, int destRow);
	bool lateralOnly(BoardView &bv, bool right, int sourceColumn, int destColumn, int sourceRow, int destRow);

	~Player();
protected:
	Board bv;
};

