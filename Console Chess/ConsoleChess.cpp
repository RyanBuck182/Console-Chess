/*
Modified By:    Ryan Buck & Connor English
Class:          CSI-240-02
Assignment:     Final Project
Date Assigned:  4/11/24
Due Date:       4/27/24 11:59PM

Project Description:
Plays chess in a console.

Certification of Authenticity:
I certify that this is entirely my own work, except where I have given
fully-documented references to the work of others. I understand the
definition and consequences of plagiarism and acknowledge that the assessor
of this assignment may, for the purpose of assessing this assignment:
- Reproduce this assignment and provide a copy to another member of
academic staff; and/or
- Communicate a copy of this assignment to a plagiarism checking
service (which may then retain a copy of this assignment on its
database for the purpose of future plagiarism checking)
*/

#include <iostream>
#include <cctype>
#include <string>

#include "ConsoleChess.h"

using namespace std;

int main() {
	bool quitGame = false;
	while (!quitGame) {
		int gameChoice = GameInterface::useGameMenu() - 1;

		enum choices { NewGame, LoadGame, Quit };
		switch (gameChoice) {
			case NewGame:
				GameInterface::board = new Board();
				GameInterface::playGame();
				break;
			case LoadGame:
				GameInterface::loadGame();
				GameInterface::playGame();
				break;
			case Quit:
				cout << '\n';
				quitGame = true;
				break;
			default:
				cout << "Invalid input!\n";
				break;
		}
		cout << endl;
	}

	GameInterface::displayQuitMessage();
}