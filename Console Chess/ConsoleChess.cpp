#include <iostream>
#include <cctype>

#include "ConsoleChess.h"

using namespace std;

int main() {
	Board::initialize();

	while (Board::getState() != Board::Win) {
		cout << Board::formatAsString();
		
		cout << '\n' << ((Board::getState() == Board::WhiteToPlay) ? "White" : "Black") << " To Play\n";
		cout << "  (1) Make move\n";
		cout << "  (2) Offer draw\n";
		cout << "  (3) Resign\n";
		cout << "  (4) Save\n";
		cout << "Choice: ";
		
		int choice;
		cin >> choice;
		cin.clear();
		cin.ignore(INT_MAX, '\n');

		switch (choice) {
			case 1: {
				Move* move = nullptr;
				while (move == nullptr) {
					cout << "\n";
					try {
						cin >> move;
					} catch (const char*) {
						move = nullptr;
						cout << "Invalid move! Please input a legal move.\n";
					}
				}

				Board::makeMove(move);
				break;
			}
			case 2:
				//offer draw
				break;
			case 3:
				//resign
				break;
			case 4:
				//save
				break;
			default:
				//"please enter a valid option"
				break;
		}

		cout << "\n\n";
	}
}