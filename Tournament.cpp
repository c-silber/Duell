#include "Tournament.h"
#include <iostream>
using namespace std;

Tournament::Tournament()
{
	humanWins = 0;
	computerWins = 0;
}

void Tournament::updateScore(char user) {
	if (user == 'C') {
		computerWins += 1;
	}
	else if (user == 'H') {
		humanWins += 1;
	}
}

void Tournament::setHumanScore(int score) {
	humanWins = score;
}

void Tournament::setComputerScore(int score) {
	computerWins = score;
}

void Tournament::getScore() {
	cout << "Computer Wins: " << computerWins << endl;
	cout << "Human Wins: " << humanWins << endl;
}

int Tournament::getHumanWins() {
	return humanWins;
}

int Tournament::getComputerWins() {
	return computerWins;
}

Tournament::~Tournament()
{
}
