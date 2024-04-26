#include <iostream>
#include <cctype>
#include <string>

#include "ConsoleChess.h"

using namespace std;

int main() {
	bool quitGame = false;
	while (!quitGame) {
		int gameChoice = GameHandler::useGameMenu();
		
		switch (gameChoice) {
			case 1: { // New Game
				GameHandler::board = new Board();

				bool returnToMainMenu = false;
				while (!returnToMainMenu && !GameHandler::hasGameEnded()) {
					cout << "\n\n";
					GameHandler::outputBoard();

					int moveChoice = GameHandler::useMoveMenu();

					cout << '\n';
					switch (moveChoice) {
						case 1: { // Make move
							Move* move = GameHandler::chooseMove();
							GameHandler::board->makeMove(move);
							break;
						} case 2: // Offer draw
							GameHandler::offerDraw();
							break;
						case 3: // Resign
							GameHandler::resign();
							break;
						case 4: // Save
							break;
						case 5: // Return to main menu
							returnToMainMenu = true;
							break;
						default:
							cout << "That is not a valid option.\n";
							cout << "Press enter to continue...";
							cin.clear();
							cin.ignore(INT_MAX, '\n');
							cout << '\n';
							break;
					}
				}

				GameHandler::displayGameEndMessage();
				delete GameHandler::board;
				GameHandler::board = nullptr;
				break;
			}
			case 2: // Load Game
				break;
			case 3: // Quit
				cout << '\n';
				quitGame = true;
				break;
			default:
				cout << "Invalid input!\n";
				break;
		}
	}

	GameHandler::displayQuitMessage();
}