#include <iostream>
#include <cctype>

#include "ConsoleChess.h"

using namespace std;

int main() {
	Board::initialize();

	while (Board::state != Board::Win) {
		cout << Board::formatAsString();
		
		Move* move = nullptr; //set move by overloading extraction operator
		while (move == nullptr) {
			Square* startSquare = nullptr;
			Square* endSquare = nullptr;
			
			cout << '\n' << ((Board::state == Board::WhiteToPlay) ? "White" : "Black") << " To Play\n";

			while (startSquare == nullptr) {
				cout << "  Start Square: ";

				try {
					cin >> startSquare;
				} catch (const char* error) {
					cout << "Invalid input! Please input a valid square (e.g. a1).\n\n";
				}
			}

			while (endSquare == nullptr) {
				cout << "    End Square: ";

				try {
					cin >> endSquare;
				} catch (const char* error) {
					cout << "Invalid input! Please input a valid square (e.g. a1).\n\n";
				}
			}

			move = new Move(startSquare, endSquare);

			try {
				Board::makeMove(move);
			} catch (const char* error) {
				move = nullptr;
				cout << "Invalid move! Please input a legal move.\n";
			}
		}

		cout << "\n\n";
	}
}