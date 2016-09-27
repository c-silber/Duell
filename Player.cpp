#include "Player.h"
#include <iostream>
using namespace std;

Player::Player()
{
	newDieValue = "empty";
	sourceRow = 0;
	sourceColumn = 0;
	destRow = 0;
	destColumn = 0;
	computerMessage = "";
	priority = 0;
	distance = 99;
}

int Player::computerStrategy(BoardView &bv, char activePlayer) {
	string active = string(1, activePlayer) + "11";
	string opponent;
	char opponentPlayer;
	if (activePlayer == 'H') { opponent = "C11"; opponentPlayer = 'C'; }
	else { opponent = "H11"; opponentPlayer = 'H'; }

	int top, opRow, opColumn, myRow, myColumn;
	string newVal;

	bv.getKey();
	myRow = bv.getHumanKeyRow();
	myColumn = bv.getHumanKeyColumn();
	opRow = bv.getComputerKeyRow();
	opColumn = bv.getComputerKeyColumn();

	if (activePlayer == 'C') {
		myRow = bv.getComputerKeyRow();
		myColumn = bv.getComputerKeyColumn();
		opRow = bv.getHumanKeyRow();
		opColumn = bv.getHumanKeyColumn();
	}

	bool isValid;

	for (int i = 1; i < 9; i++) {
		for (int j = 1; j < 10; j++) {
			//cout << i << "," << j << endl;
			if (i == 8 && j == 6) {
				cout << "STOP HERE" << endl;
			}
			string val = bv.getValue(i, j);
			if (val == "0") {
				continue;
			}
			else if (val.at(0) == activePlayer) {
				Die c(val.at(1) - '0', val.at(2) - '0');
				int distanceToKeyRow = i - opRow;
				int distanceToKeyColumn = j - opColumn;
				int dist = abs(distanceToKeyRow) + abs(distanceToKeyColumn);
				top = int(val.at(1) - '0');

				if (top == dist) {
					// Computer has a piece that can be moved to win. Check if Computer can move that piece frontally or laterally
					if (i == opRow) {
						// my piece is in the same row (need to move laterally)
						bool right = false;
						if (j > opColumn) { right = true; }
						isValid = bv.lateralMove(getRow(i), j, getRow(opRow), opColumn);
						if (isValid) {
							c.rollDie(0, abs(opColumn - j), 0, 0);

							newVal = val.at(0) + to_string(c.getTop()) + to_string(c.getRight());

							computerMessage = val + " WAS ROLLED FROM SQUARE (" + to_string(getRow(i)) + ","
								+ to_string(j) + ") FRONTALLY BY 0 AND LATERALLY BY " + to_string(abs(opColumn - j)) + " TO SQUARE (" + to_string(getRow(opRow)) + "," + to_string(opColumn) + "). THE DIE IS NOW "
								+ val.at(0) + to_string(c.getTop()) + to_string(c.getRight());

							computerMessage += "\nThe computer picked " + val + " at (" + to_string(getRow(i)) + ","
								+ to_string(j) + ") because this enabled the player to capture the opponents key piece.";

							setMove(i, j, opRow, opColumn, newVal, 4);
							return 1;
						}
					}
					else if (j == opColumn) {
						// my piece is in the same column (need to move frontally)
						bool up = false;
						if (i > opRow) { up = true; }

						isValid = bv.frontalMove(i, j, opRow, opColumn);
						if (isValid) {

							c.rollDie(abs(opRow - i), 0, up, 0);
							
							computerMessage = val + " WAS ROLLED FROM SQUARE (" + to_string(getRow(i)) + ","
								+ to_string(j) + ") FRONTALLY BY " + to_string(abs(opRow - i)) + " AND LATERALLY BY 0 TO SQUARE (" + to_string(getRow(opRow)) + "," + to_string(opColumn) + "). THE DIE IS NOW "
								+ val.at(0) + to_string(c.getTop()) + to_string(c.getRight());

							computerMessage += "\nThe computer picked " + val + " at (" + to_string(getRow(i)) + ","
								+ to_string(j) + ") because this enabled the player to capture the opponents key piece and win the game.";

							setMove(i, j, opRow, opColumn, val.at(0) + to_string(c.getTop()) + to_string(c.getRight()), 4);

							return 1;
						}
					}
					
					else {
						int count = (top - 1), up = false, right = false;
						// try moving die frontally / laterally and check if able to win
						if (j < opColumn) { right = true; }
						if (i > opRow) { up = true; }
						isValid = bv.lateralMove(i, j, opRow, opColumn);
						if (isValid) {
							c.rollDie(abs(opRow - i), abs(opColumn - j), up, 'l');

							newVal = val.at(0) + to_string(c.getTop()) + to_string(c.getRight());

							computerMessage = val + " WAS ROLLED FROM SQUARE (" +
								to_string(getRow(i)) + "," + to_string(j) + ") FRONTALLY BY " + to_string(abs(opRow - i)) + " AND LATERALLY BY " +
								to_string(abs(opRow - i)) + " TO SQUARE (" + to_string(getRow(opRow)) + "," + to_string(opColumn)
								+ "). THE DIE IS NOW " + val.at(0) + to_string(c.getTop()) + to_string(c.getRight());

							computerMessage += "\nThe computer picked " + val + " at (" + to_string(getRow(i)) + ","
								+ to_string(j) + ") because this enabled the player to capture the opponents key piece and win the game.";

							setMove(i, j, opRow, opColumn, newVal,  4);

							return 1;
						}

						isValid = bv.frontalMove(i, j, opRow, opColumn);
						if (isValid) {
							c.rollDie(abs(opRow - i), abs(opColumn - j), up, 'f');

							computerMessage = val + " WAS ROLLED FROM SQUARE ("
								+ to_string(getRow(i)) + "," + to_string(j) + ") FRONTALLY BY " + to_string(abs(opRow - i)) + " AND LATERALLY BY " +
								to_string(abs(opRow - i)) + " TO SQUARE (" + to_string(getRow(opRow)) + "," + to_string(opColumn)
								+ "). THE DIE IS NOW " + val.at(0) + to_string(c.getTop()) + to_string(c.getRight());

							computerMessage += "\nThe computer picked " + val + " at (" + to_string(getRow(i)) + ","
								+ to_string(j) + ") because this enabled the player to capture the opponents key piece and win the game.";

							setMove(i, j, opRow, opColumn, val.at(0) + to_string(c.getTop()) + to_string(c.getRight()), 4);

							return 1;
						}

					}
				}
				else {
					bool up = false, right = false;
					// try moving die frontally / laterally and check if able to win
					for (int moves = 1; moves < (top+1); moves++) {
						int newRow = i - moves, newColumn = j + (top - moves);
						if (j < opColumn) {
							right = true;
							newRow = i + moves;
						}
						if (i > opRow) {
							up = true;
							newColumn = j - (top - moves);
						}

						string validDest = bv.validateDiceRoll(val, i, j, newRow, newColumn);
						
						if (validDest == "SUCCESS") {
							isValid = bv.lateralMove(i, j, newRow, newColumn);
							if (isValid) {
								c.rollDie(abs(newRow - i), abs(newColumn - j), up, 'l');

								int topDie = c.getTop();
								int rightDie = c.getRight();
								string newVal = val.at(0) + to_string(topDie) + to_string(rightDie);

								int distanceToKeyRow = newRow - opRow;
								int distanceToKeyColumn = newColumn - opColumn;
								int dist = abs(distanceToKeyRow) + abs(distanceToKeyColumn);
								int newTop = newVal.at(1) - '0';
							
								// COULD POSSIBLY WIN NEXT TURN
								if ((newTop == dist) && (priority < 3)) {

									computerMessage = val + " WAS ROLLED FROM SQUARE (" + to_string(getRow(i)) + "," + to_string(j) + ") FRONTALLY BY " + to_string(abs(newRow - i))
										+ " AND LATERALLY BY " + to_string(abs(newColumn - j)) + " TO SQUARE (" + to_string(getRow(newRow)) + "," +
										to_string(newColumn) + ").\nTHE DIE IS NOW " + newVal;

									setMove(i, j, newRow, newColumn, newVal, 2);

								}
								// BEST MOVE IF NO MOVE
								if (newDieValue == "empty" || dist < distance && (priority == 0)) {

									computerMessage = val + " WAS ROLLED FROM SQUARE (" + to_string(getRow(i)) + "," + to_string(j) + ") FRONTALLY BY " + to_string(abs(newRow - i))
										+ " AND LATERALLY BY " + to_string(abs(newColumn - j)) + " TO SQUARE (" + to_string(getRow(newRow)) + "," +
										to_string(newColumn) + ").\nTHE DIE IS NOW " + newVal;

									setMove(i, j, newRow, newColumn, newVal, 0);

									distance = dist;
								}
								string valHere = bv.getValue(newRow, newColumn);
								// COULD CAPTURE OPPONENT PIECE
								if ((valHere.at(0) == opponentPlayer) && (priority < 2)) {

									computerMessage = val + " WAS ROLLED FROM SQUARE (" + to_string(getRow(i)) + "," + to_string(j) + ") FRONTALLY BY " + to_string(abs(newRow - i))
										+ " AND LATERALLY BY " + to_string(abs(newColumn - j)) + " TO SQUARE (" + to_string(getRow(newRow)) + "," +
										to_string(newColumn) + ").\nTHE DIE IS NOW " + newVal;

									setMove(i, j, newRow, newColumn, newVal, 1);
								}
							}
						}
						newRow = i + (top - moves), newColumn = j - moves;
						if (j < opColumn) {
							right = true;
							newColumn = j + moves;
						}
						if (i > opRow) {
							up = true;
							newRow = i - (top - moves);
						}
						validDest = bv.validateDiceRoll(val, i, j, newRow, newColumn);

						if (validDest == "SUCCESS") {
							isValid = bv.frontalMove(i, j, newRow, newColumn);
							if (isValid) {
								c.rollDie(abs(newRow - 1), (newColumn - j), up, 'f');

								int topDie = c.getTop();
								int rightDie = c.getRight();
								string newVal = val.at(0) + to_string(topDie) + to_string(rightDie);

								int distanceToKeyRow = newRow - opRow;
								int distanceToKeyColumn = newColumn - opColumn;
								int dist = abs(distanceToKeyRow) + abs(distanceToKeyColumn);
								int newTop = newVal.at(1) - '0';

								// COULD POSSIBLY WIN NEXT TURN
								if ((newTop == dist) && (priority < 3)) {

									computerMessage = val + " WAS ROLLED FROM SQUARE (" + to_string(getRow(i)) + "," + to_string(j) + ") FRONTALLY BY " 
										+ to_string(abs(newRow - i)) + " AND LATERALLY BY " + to_string(abs(newColumn - j)) + " TO SQUARE (" + to_string(getRow(newRow))
										+ "," + to_string(newColumn) + ").\nTHE DIE IS NOW " + newVal;

									setMove(i, j, newRow, newColumn, newVal, 2);

								}
								// BEST MOVE IF NOT MOVE ... priority = 0
								if (newDieValue == "empty" || dist < distance && (priority == 0)) {
									distance = dist;

									computerMessage = val + " WAS ROLLED FROM SQUARE (" + to_string(getRow(i)) + "," + to_string(j) + ") FRONTALLY BY "
										+ to_string(abs(newRow - i)) + " AND LATERALLY BY " + to_string(abs(newColumn - j)) + " TO SQUARE (" + to_string(getRow(newRow))
										+ "," + to_string(newColumn) + ").\nTHE DIE IS NOW " + newVal;

									setMove(i, j, newRow, newColumn, newVal, 0);

								}
								else {
									string valHere = bv.getValue(newRow, newColumn);
									// CAN CAPTURE OPPONENT PIECE
									if ((valHere.at(0) == opponentPlayer) && (priority < 2)) {

										computerMessage = val + " WAS ROLLED FROM SQUARE (" + to_string(getRow(i)) + "," + to_string(j) + ") FRONTALLY BY "
											+ to_string(abs(newRow - i)) + " AND LATERALLY BY " + to_string(abs(newColumn - j)) + " TO SQUARE (" + to_string(getRow(newRow))
											+ "," + to_string(newColumn) + ").\nTHE DIE IS NOW " + newVal;

										setMove(i, j, newRow, newColumn, newVal, 1);
									}
								}
							}
						}
					}
				}
			}
			else if (val.at(0) == opponentPlayer) {
				int distanceToMyKeyRow = i - myRow;
				int distanceToMyKeyColumn = j - myColumn;
				int myDist = abs(distanceToMyKeyRow) + abs(distanceToMyKeyColumn);
				top = int(val.at(1) - '0');

				if (top == myDist) {
					// check if the opponents piece is able to get to my key piece
					bool validateFrontal = bv.frontalMove(i, j, myRow, myColumn);
					if (validateFrontal) {
						cout << "CAN BE KILLED MOVING FRONTALLY FROM " << val << endl;
					}

					bool validateLateral = bv.lateralMove(i, j, myRow, myColumn);
					if (validateLateral) {
						cout << "CAN BE KILLED MOVING LATERALLY FROM " << val << endl;
					}



					// If someone can kill my key piece, try moving it forward
					string moveKey = bv.validateDiceRoll(active, getRow(myRow), myColumn, getRow(myRow - 1), myColumn);
					bool frontal = bv.frontalMove(getRow(myRow), myColumn, getRow(myRow - 1), myColumn);
					if (moveKey == "SUCCESS" && frontal) {
						computerMessage = active + " WAS ROLLED FROM SQUARE ("
							+ to_string(getRow(myRow)) + "," + to_string(myColumn) + ") FRONTALLY BY 1 AND LATERALLY BY 0" +
							" TO SQUARE (" + to_string(getRow(myRow - 1)) + "," + to_string(myColumn)
							+ "). THE DIE IS NOW " + active;

						computerMessage += "\nThe computer picked " + active + " at ("
							+ to_string(getRow(myRow)) + "," + to_string(myColumn) + ") to save key piece from being captured by " + val;

						setMove(myRow, myColumn, (myRow + 1), myColumn, active, 3);

						if (activePlayer == 'C') {
							if (destRow == 8 && destColumn == 5)
								return 1;
						}
					}
					else {
						// if I can't move it forward, try capturing the opponents piece

						cout << val << endl;
						getMove(bv, i, j, val, top);

					}
				}
				
				bool up = false, right = false;
				// try moving die frontally / laterally and check if any of my pieces are able to be captured
				for (int capMoves = 0; capMoves < top; capMoves++) {
					int newRow = i - capMoves, newColumn = j + (top - capMoves);
					if (j < opColumn) {
						right = true;
						newRow = i + capMoves;
					}
					if (i > opRow) {
						up = true;
						newColumn = j - (top - capMoves);
					}
					string validDest = bv.validateDiceRoll(val, i, j, newRow, newColumn);
					if (validDest == "SUCCESS") {
						isValid = bv.lateralMove(i, j, newRow, newColumn);
						if (isValid) {
							Die e(val.at(1) - '0', val.at(2) - '0');
							e.rollDie(abs(newRow - i), abs(newColumn - j), up, 'l');

							int topDie = e.getTop();
							int rightDie = e.getRight();
							string newVal = val.at(0) + to_string(topDie) + to_string(rightDie);
							int newTop = newVal.at(1) - '0';

							string valHere = bv.getValue(newRow, newColumn);
							if (valHere.at(0) == activePlayer) {
								//cout << "at risk of capture" << endl;
							}
						}
					}
				}
			}
		}
	}
	return 0;
}

Player::~Player()
{
	int sourceRow, sourceColumn, destRow, destColumn, priority;
	string newDieValue, computerMessage;
}

int Player::getRow(int x) {
	switch (x) {
	case 8:
		return 1;
	case 7:
		return 2;
	case 6:
		return 3;
	case 5:
		return 4;
	case 4:
		return 5;
	case 3:
		return 6;
	case 2:
		return 7;
	case 1:
		return 8;
	}
}

void Player::setMove(int sRow, int sColumn, int dRow, int dColumn, string newDieVal, int thisPriority){
	sourceRow = sRow;
	sourceColumn = sColumn;
	destRow = dRow;
	destColumn = dColumn;
	newDieValue = newDieVal;
	priority = thisPriority;
}

void Player::getMove(BoardView bv, int sourceRow, int sourceColumn, string sourceVal, int top) {
	bool isValid;
	for (int moves = 0; moves < (top + 1); moves++) {
		int newRow = sourceRow - moves, newColumn = sourceColumn + (top - moves);
		string validDest;

		validDest = bv.validateDiceRoll(sourceVal, sourceRow, sourceColumn, newRow, newColumn);

		if (validDest == "SUCCESS") {
			isValid = bv.lateralMove(sourceRow, sourceColumn, newRow, newColumn);
			if (isValid) {
				if (bv.getValue(newRow, newColumn) != "0"){
					cout << "NEW ROW: " << newRow << " NEW COLUMN: " << newColumn << endl;
				}
			}
		}

		newRow = sourceRow - moves, newColumn = sourceColumn - (top - moves);

		validDest = bv.validateDiceRoll(sourceVal, sourceRow, sourceColumn, newRow, newColumn);

		if (validDest == "SUCCESS") {
			isValid = bv.lateralMove(sourceRow, sourceColumn, newRow, newColumn);
			if (isValid) {
				if (bv.getValue(newRow, newColumn) != "0") {
					cout << "NEW ROW: " << newRow << " NEW COLUMN: " << newColumn << endl;
				}
			}
		}

		newRow = sourceRow + moves, newColumn = sourceColumn + (top - moves);

		validDest = bv.validateDiceRoll(sourceVal, sourceRow, sourceColumn, newRow, newColumn);

		if (validDest == "SUCCESS") {
			isValid = bv.lateralMove(sourceRow, sourceColumn, newRow, newColumn);
			if (isValid) {
				if (bv.getValue(newRow, newColumn) != "0") {
					cout << "NEW ROW: " << newRow << " NEW COLUMN: " << newColumn << endl;
				}
			}
		}

		newRow = sourceRow + moves, newColumn = sourceColumn - (top - moves);

		validDest = bv.validateDiceRoll(sourceVal, sourceRow, sourceColumn, newRow, newColumn);

		if (validDest == "SUCCESS") {
			isValid = bv.lateralMove(sourceRow, sourceColumn, newRow, newColumn);
			if (isValid) {
				if (bv.getValue(newRow, newColumn) != "0") {
					cout << "NEW ROW: " << newRow << " NEW COLUMN: " << newColumn << endl;
				}
			}
		}

		newRow = sourceRow + (top - moves), newColumn = sourceColumn - moves;

		validDest = bv.validateDiceRoll(sourceVal, sourceRow, sourceColumn, newRow, newColumn);

		if (validDest == "SUCCESS") {
			isValid = bv.lateralMove(sourceRow, sourceColumn, newRow, newColumn);
			if (isValid) {
				if (bv.getValue(newRow, newColumn) != "0") {
					cout << "NEW ROW: " << newRow << " NEW COLUMN: " << newColumn << endl;
				}
			}
		}

		newRow = sourceRow + (top - moves), newColumn = sourceColumn + moves;

		validDest = bv.validateDiceRoll(sourceVal, sourceRow, sourceColumn, newRow, newColumn);

		if (validDest == "SUCCESS") {
			isValid = bv.lateralMove(sourceRow, sourceColumn, newRow, newColumn);
			if (isValid) {
				if (bv.getValue(newRow, newColumn) != "0") {
					cout << "NEW ROW: " << newRow << " NEW COLUMN: " << newColumn << endl;
				};
			}
		}

		newRow = sourceRow - (top - moves), newColumn = sourceColumn + moves;

		validDest = bv.validateDiceRoll(sourceVal, sourceRow, sourceColumn, newRow, newColumn);

		if (validDest == "SUCCESS") {
			isValid = bv.lateralMove(sourceRow, sourceColumn, newRow, newColumn);
			if (isValid) {
				if (bv.getValue(newRow, newColumn) != "0") {
					cout << "NEW ROW: " << newRow << " NEW COLUMN: " << newColumn << endl;
				}
			}
		}

		newRow = sourceRow - (top - moves), newColumn = sourceColumn - moves;

		validDest = bv.validateDiceRoll(sourceVal, sourceRow, sourceColumn, newRow, newColumn);

		if (validDest == "SUCCESS") {
			isValid = bv.lateralMove(sourceRow, sourceColumn, newRow, newColumn);
			if (isValid) {
				if (bv.getValue(newRow, newColumn) != "0") {
					cout << "NEW ROW: " << newRow << " NEW COLUMN: " << newColumn << endl;
				}
			}
		}
	}
}