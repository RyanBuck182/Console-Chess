#include <iostream>
#include <cctype>

#include "ConsoleChess.h"

using namespace std;

int main() {
	Board::initialize();

	while (Board::state != Board::Win) {
		cout << Board::formatAsString();
		
		Move* move = nullptr;
		while (move == nullptr) {
			cout << '\n' << ((Board::state == Board::WhiteToPlay) ? "White" : "Black") << " To Play\n";

			try {
				cin >> move;
			} catch (const char* error) {
				move = nullptr;
				cout << "Invalid move! Please input a legal move.\n";
			}
		}

		Board::makeMove(move);

		cout << "\n\n";
	}
}