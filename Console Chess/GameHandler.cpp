#include <iostream>

#include "GameHandler.h"
#include "Board.h"
#include "Move.h"

using namespace std;

bool GameHandler::currentPlayerIsWhite() {
	return Board::getState() == Board::WhiteToPlay;
}

int GameHandler::useGameMenu() {
	cout << "Welcome to Console Chess by Ryan Buck and Connor English.\n\n";
	cout << "Please make a selection:\n";
	cout << "  (1) New Game\n";
	cout << "  (2) Load Game\n";
	cout << "  (3) Quit\n";
	cout << "Choice: ";

	int choice;
	cin >> choice;
	cin.clear();
	cin.ignore(INT_MAX, '\n');

	return choice;
}

bool GameHandler::hasGameEnded() {
	return Board::getState() == Board::WhiteWin
		|| Board::getState() == Board::BlackWin
		|| Board::getState() == Board::Draw
		|| Board::getState() == Board::Stalemate;
}

void GameHandler::outputBoard() {
	cout << Board::formatAsString();
}

string GameHandler::getSideString(bool current) {
	if (current)
		return (currentPlayerIsWhite()) ? "White" : "Black";
	else
		return (!currentPlayerIsWhite()) ? "White" : "Black";
}

int GameHandler::useMoveMenu() {
	cout << '\n' << getSideString(true) << " To Play\n";
	cout << "  (1) Make move\n";
	cout << "  (2) Offer draw\n";
	cout << "  (3) Resign\n";
	cout << "  (4) Save\n";
	cout << "  (5) Quit\n";
	cout << "Choice: ";

	int choice;
	cin >> choice;
	cin.clear();
	cin.ignore(INT_MAX, '\n');

	return choice;
}

Move* GameHandler::chooseMove() {
	Move* move = nullptr;
	while (move == nullptr) {
		try {
			cin >> move;
		} catch (const char*) {
			move = nullptr;
			cout << "Invalid move! Please input a legal move.\n";
		}
	}

	return move;
}

void GameHandler::offerDraw() {
	cout << getSideString(true) << " offers a draw.\n";
	cout << "Does " << getSideString(false) << " accept?\n";
	cout << "  (1) Yes\n";
	cout << "  (2) No\n";
	cout << "Choice: ";

	int choice;
	cin >> choice;
	cin.clear();
	cin.ignore(INT_MAX, '\n');

	if (choice == 1)
		Board::setState(Board::Draw);
	else
		cout << "Draw declined.\n";
}

void GameHandler::resign() {
	cout << "Are you sure you want to resign?\n";
	cout << "  (1) Yes\n";
	cout << "  (2) No\n";
	cout << "Choice: ";

	int choice;
	cin >> choice;
	cin.clear();
	cin.ignore(INT_MAX, '\n');

	if (choice == 1)
		Board::setState((currentPlayerIsWhite()) ? Board::BlackWin : Board::WhiteWin);
	else
		cout << "Canceling resignation.\n";
}

void GameHandler::displayGameEndMessage() {
	if (Board::getState() == Board::WhiteWin || Board::getState() == Board::BlackWin)
		cout << '\n' << GameHandler::getSideString(GameHandler::currentPlayerIsWhite()) << " Wins!\n\n";
	else if (Board::getState() == Board::Stalemate)
		cout << "\nThe game has ended in stalemate.\n\n";
	else if (Board::getState() == Board::Draw)
		cout << "\nThe game has ended in a draw.\n\n";
}

void GameHandler::displayQuitMessage() {
	cout << "Terminating program.\n";
	cout << "Thanks for playing!\n";
}