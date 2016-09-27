#include "Computer.h"
#include <string>
#include <iostream>
using namespace std;

Computer::Computer()
{
}

void Computer::moveDie(BoardView &bv) {

	bv.setValue(sourceRow, sourceColumn, "0");
	bv.setValue(destRow, destColumn, newDieValue);
	cout << endl;
	cout << computerMessage << endl;
	cout << endl;
	bv.printBoard();

}

Computer::~Computer()
{
}
