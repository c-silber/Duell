#include "Game.h"
#include <iostream>
#include <ctime>
#include "Board.h"
#include "BoardView.h"
#include "Human.h"
#include "Computer.h"
#include "Tournament.h"
using namespace std;

Game::Game()
{
}

// function that implements the game
void Game::Run() {
	cout << "-- DUELL --" << endl;

	Tournament t;

	bool playing = true, firstRun = true;
	while (playing) {
		char winner = Play(t, firstRun);
		firstRun = false;
		if (winner == 'C') {
			t.updateScore('C');
		}
		else {
			t.updateScore('H');
		}
		char newGame;
		cout << "START A NEW GAME (y/n)? " << endl;
		cin >> newGame;
		if (newGame == 'N' || newGame == 'n') {
			t.getScore();
			playing = false;
		}
	}

}

char Game::Play(Tournament &t, bool firstRun) {
	// new board and boardview are created
	Board b;
	BoardView bv;

	char reSerialize;
	string fileName;
	bool serialize = false, first = 0;

	if (firstRun) {
		cout << "WOULD YOU LIKE TO RESUME A PREVIOUS GAME (y/n)? ";
		cin >> reSerialize;
		if (reSerialize == 'Y' || reSerialize == 'y') {
			serialize = true;
			ifstream file;
			do {
				cout << "Please enter the file name: ";
				cin >> fileName;
			
				file.open(fileName);
				if (file.fail()) {
					cout << "ERROR OPENING FILE" << endl;
				}

			} while (file.fail());

			first = bv.resumeSerialization(fileName, t);
		}
	}
	if (serialize == false) {
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
			first = 1;
			cout << "COMPUTER GOES FIRST" << endl;
		}

		for (int i = 0; i < 9; i++) {
			for (int j = 0; j < 10; j++) {
				bv.setValue(i, j, b.getBoard(i, j));
			}
		}
		bv.printBoard();
	}

	bool playing = true;
	char nextPlayer, suspend;
	while (playing) {
		Human h;
		Computer c;
		Player *human = &h;
		if (first == 1) {
			Player *computer = &c;
			computer->playerStrategy(bv);
			int cVal = c.computerStrategy(bv, 'C');
			c.moveDie(bv);
			nextPlayer = 'H';
			if (cVal == 1) {
				return 'C';
			}
			cout << "WOULD YOU LIKE TO SUSPEND THE GAME (y/n)? ";
			cin >> suspend;

			if (suspend == 'Y' || suspend == 'y') {
				bv.initiateSerialization(t.getHumanWins(), t.getComputerWins(), nextPlayer);
				cout << "THANK YOU FOR PLAYING" << endl;
				system("pause");
				exit(0);
			}
		}
		first = 1;
		int val = human->playerStrategy(bv);
		bv.printBoard();
		nextPlayer = 'C';
		if (val == 1) {
			return 'H';
		}

		cout << "WOULD YOU LIKE TO SUSPEND THE GAME (y/n)? ";
		cin >> suspend;

		if (suspend == 'Y' || suspend == 'y') {
			bv.initiateSerialization(t.getHumanWins(), t.getComputerWins(), nextPlayer);
			cout << "THANK YOU FOR PLAYING" << endl;
			system("pause");
			exit(0);
		}
	}
}

Game::~Game()
{
}
