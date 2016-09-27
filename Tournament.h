#pragma once
class Tournament
{
public:
	Tournament();

	void updateScore(char user);
	void setHumanScore(int score);
	void setComputerScore(int score);

	int getHumanWins();
	int getComputerWins();

	void getScore();
	~Tournament();

private:
	int humanWins, computerWins;
};

