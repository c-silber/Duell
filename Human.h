#pragma once
#include "Player.h"

class Human :
	public Player
{
public:
	Human();
	int playerStrategy(BoardView &bv);

	const int MIN_ROW = 1;
	const int MIN_COLUMN = 1;
	const int MAX_ROW = 8;
	const int MAX_COLUMN = 9;
	~Human();
};

