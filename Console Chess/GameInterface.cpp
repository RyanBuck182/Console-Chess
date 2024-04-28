/*
Modified By:    Ryan Buck & Connor English
Class:          CSI-240-02
Assignment:     Final Project
Date Assigned:  4/11/24
Due Date:       4/27/24 11:59PM
*/

#include <iostream>
#include <fstream>
#include <vector>
#include "GameInterface.h"
#include "Board.h"
#include "Move.h"
#include "Square.h"

using namespace std;

Board* GameInterface::board = nullptr;

bool GameInterface::currentPlayerIsWhite() {
	return board->getState() == board->WhiteToPlay;
}

int GameInterface::useGameMenu() {
	cout << "Welcome to Console Chess by Ryan Buck and Connor English.\n";
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

bool GameInterface::hasGameEnded() {
	return board->getState() == board->WhiteWin
		|| board->getState() == board->BlackWin
		|| board->getState() == board->Draw;
}

void GameInterface::outputBoard() {
	cout << board->formatAsString();
}

string GameInterface::getSideString(bool current) {
	if (current)
		return (currentPlayerIsWhite()) ? "White" : "Black";
	else
		return (!currentPlayerIsWhite()) ? "White" : "Black";
}

void GameInterface::playGame() {
	bool returnToMainMenu = false;
	while (!returnToMainMenu && !GameInterface::hasGameEnded())
		returnToMainMenu = GameInterface::doTurn();

	GameInterface::displayGameEndMessage();
	delete GameInterface::board;
	GameInterface::board = nullptr;
}

bool GameInterface::doTurn() {
	cout << "\n\n";
	GameInterface::outputBoard();

	int moveChoice = GameInterface::useMoveMenu() - 1;

	cout << '\n';
	enum choices { MakeMove, OfferDraw, Resign, Save, ReturnToMainMenu };
	switch (moveChoice) {
		case MakeMove: {
			Move move = GameInterface::chooseMove();
			GameInterface::board->makeMove(move);
			break;
		} case OfferDraw:
			GameInterface::offerDraw();
			break;
		case Resign:
			GameInterface::resign();
			break;
		case Save:
			GameInterface::saveGame();
			break;
		case ReturnToMainMenu:
			return true;
		default:
			cout << "That is not a valid option.\n";
			cout << "Press enter to continue...";
			cin.clear();
			cin.ignore(INT_MAX, '\n');
			cout << '\n';
			break;
	}

	return false;
}

int GameInterface::useMoveMenu() {
	cout << '\n' << getSideString(true) << " To Play\n";
	cout << "  (1) Make move\n";
	cout << "  (2) Offer draw\n";
	cout << "  (3) Resign\n";
	cout << "  (4) Save\n";
	cout << "  (5) Return To Main Menu\n";
	cout << "Choice: ";

	int choice;
	cin >> choice;
	cin.clear();
	cin.ignore(INT_MAX, '\n');

	return choice;
}

Move GameInterface::chooseMove() {
	Move move(board);
	bool validMove = false;
	while (!validMove) {
		try {
			cin >> move;
			validMove = true;
		} catch (const char*) {
			validMove = false;
			cout << "Invalid move! Please input a legal move.\n\n";
		}
	}

	return move;
}

void GameInterface::offerDraw() {
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
		board->setState(board->Draw);
	else
		cout << "Draw declined.\n";
}

void GameInterface::resign() {
	cout << "Are you sure you want to resign?\n";
	cout << "  (1) Yes\n";
	cout << "  (2) No\n";
	cout << "Choice: ";

	int choice;
	cin >> choice;
	cin.clear();
	cin.ignore(INT_MAX, '\n');

	if (choice == 1)
		board->setState((currentPlayerIsWhite()) ? board->BlackWin : board->WhiteWin);
	else
		cout << "Canceling resignation.\n";
}

void GameInterface::displayGameEndMessage() {
	if (board->getState() == board->WhiteWin || board->getState() == board->BlackWin)
		cout << '\n' << GameInterface::getSideString(GameInterface::currentPlayerIsWhite()) << " Wins!\n\n";
	else if (board->getState() == board->Draw)
		cout << "\nThe game has ended in a draw.\n\n";
}

void GameInterface::displayQuitMessage() {
	cout << "Terminating program.\n";
	cout << "Thanks for playing!\n";
}

void GameInterface::saveGame() {
	ofstream saveFile;
	saveFile.open("Saved Game.txt");
	for (int i = 0; i < board->getMoveList().size(); i++)
		saveFile << board->getMoveList()[i] << endl;
	saveFile.close();

	cout << "Game has been saved!\n";
	cout << "Press enter to continue...";
	cin.clear();
	cin.ignore(INT_MAX, '\n');
	cout << '\n';
}

void GameInterface::loadGame() {
	board = new Board();
	
	ifstream saveFile;
	saveFile.open("Saved Game.txt");

	vector<Move> moveList;
	while (!saveFile.eof()) {
		char startColumn;
		int startRow;
		if (!(saveFile >> startColumn >> startRow)) break;
		int startId = (startRow - 1) * Board::BOARD_LENGTH + (static_cast<int>(tolower(startColumn)) - static_cast<int>('a'));
		cout << startId;

		char endColumn;
		int endRow;
		if (!(saveFile >> endColumn >> endRow)) break;
		int endId = (endRow - 1) * Board::BOARD_LENGTH + (static_cast<int>(tolower(endColumn)) - static_cast<int>('a'));
		cout << endId;

		moveList.push_back(Move(board, board->getSquareFromId(startId), board->getSquareFromId(endId)));
	}
	saveFile.close();

	for (int i = 0; i < moveList.size(); i++)
		board->makeMove(moveList[i]);
}