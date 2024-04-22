#include <iostream>
#include "ConsoleChess.h"

using namespace std;

int main() {
	Board board;

	cout << board;
	cout << "\nPress enter to continue...";
	cin.get();

	board.getSquareFromId(0)->piece->computeValidMoves(board);
}