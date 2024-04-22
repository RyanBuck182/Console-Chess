#include <iostream>
#include <cctype>

#include "ConsoleChess.h"

using namespace std;

int main() {
	Board board;

	while (board.state != Board::Win) {
		cout << board;
		
		Move* move = nullptr; //set move by overloading extraction operator
		while (move == nullptr) {
			Square* startSquare = nullptr;
			Square* endSquare = nullptr;
			
			cout << '\n' << ((board.state == Board::WhiteToPlay) ? "White" : "Black") << " To Play\n";

			while (startSquare == nullptr) {
				char column;
				int row;

				cout << "  Start Square: ";
				
				cin >> column;
				cin >> row;
				cin.clear();
				cin.ignore(INT_MAX, '\n');

				int id = (row - 1) * Board::BOARD_LENGTH + (static_cast<int>(tolower(column) - static_cast<int>('a')));

				try {
					startSquare = board.getSquareFromId(id);
				} catch (const char* error) {
					cout << "Invalid input! Please input a valid square (e.g. a1).\n\n";
				}
			}

			while (endSquare == nullptr) {
				char column;
				int row;

				cout << "    End Square: ";

				cin >> column;
				cin >> row;
				cin.clear();
				cin.ignore(INT_MAX, '\n');

				int id = (row - 1) * Board::BOARD_LENGTH + (static_cast<int>(tolower(column) - static_cast<int>('a')));

				try {
					endSquare = board.getSquareFromId(id);
				} catch (const char* error) {
					cout << "Invalid input! Please input a valid square (e.g. a1).\n\n";
				}
			}

			move = new Move(startSquare, endSquare);

			try {
				board.makeMove(move);
			} catch (const char* error) {
				move = nullptr;
				cout << "Invalid move! Please input a legal move.\n";
			}
		}

		cout << "\n\n";
	}
}