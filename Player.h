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
	~Player();
protected:
	Board bv;
};

