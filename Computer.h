#pragma once
#include "Player.h"

class Computer:
	public Player
{
public:
	Computer();
	void moveDie(BoardView &bv);
	~Computer();
};

