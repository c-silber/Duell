#include "Game.h"
#include <iostream>
#include <ctime>
#include "Board.h"
#include "BoardView.h"
#include "Human.h"
#include "Computer.h"
using namespace std;

Game::Game()
{
}

// function that implements the game
void Game::Run() {

	cout << "-- DUELL --" << endl;

	// random generator to simulate die rolling
	srand(time(0));
	int hDie = 0, cDie = 0;

	// computer and human roll for firsts
	do {
		hDie = rand() % 6 + 1;
		cDie = rand() % 6 + 1;
		cout << "YOU ROLL THE DIE: " << hDie << endl;
		cout << "COMPUTER ROLLS THE DIE: " << cDie << endl;
		if (hDie == cDie) {
			cout << "TIE. ROLL AGAIN" << endl;
		}
	} while (hDie == cDie);

	if (hDie > cDie) {
		cout << "YOU GO FIRST" << endl;
	}
	else {
		cout << "COMPUTER GOES FIRST" << endl;
	}

	// new board and boardview are created
	Board b;
	BoardView bv;

	for (int i = 0; i < 9; i++) {
		for (int j = 0; j < 10; j++) {
			bv.setValue(i, j, b.getBoard(i, j));
		}
	}

	bv.printBoard();
	char newGame;
	bool playing = true;
	while (playing) {
		Human h;
		Computer c;
		Player *human = &h;
		Player *computer = &c;
		computer->playerStrategy(bv);
		int val = human->playerStrategy(bv);
		bv.printBoard();
		if (val == 1) {
			cout << "YOU WIN!" << endl;
			cout << "WOULD YOU LIKE TO START A NEW GAME? (y/n)" << endl;
			cin >> newGame;
			if (newGame == 'y' || newGame == 'Y') {
				playing = true;
			}
			else {
				playing = false;
			}
		}
	}
}


Game::~Game()
{
}
