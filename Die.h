#pragma once

class Die
{
public:
	Die(int topNum, int rightNum);
	void rollDie(int frontal, int lateral, char movement, char path);
	int getValue(int values[], int value, char movement);
	int getTop();
	int getRight();
	void lateralMoves(int lateral, char direction);

	~Die();

private:
	int top;
	int bottom;
	int right;
	int left;
	int position;
};

