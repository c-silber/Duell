#pragma once
#include "Player.h"

class Computer:
	public Player
{
public:
	Computer();
	int playerStrategy(BoardView &bv);
	string getMoves(int row, int column, string value);
	~Computer();
};

