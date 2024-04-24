#ifndef BOARD_H
#define BOARD_H

#include <iostream>
#include <vector>
#include <string>

class Square;
class Move;

class Board {
public:
	enum BoardState { WhiteToPlay, BlackToPlay, Win, Stalemate, Draw };
	
	static const int BOARD_LENGTH = 8;
	static const int BOARD_SIZE = BOARD_LENGTH * BOARD_LENGTH;

	static void initialize();
	static void clear();

	static bool idInRange(int);

	static BoardState getState();
	static Square* getSquareFromId(int);
	static bool isSquareAttacked(int);
	static bool isSquareAttacked(Square*);

	static Square* getNorthSquare(Square*);
	static Square* getSouthSquare(Square*);
	static Square* getEastSquare(Square*);
	static Square* getWestSquare(Square*);
	static Square* getForwardSquare(Square*);
	static Square* getBackwardSquare(Square*);
	static Square* getRightSquare(Square*);
	static Square* getLeftSquare(Square*);

	static Move* getLastMove();
	static bool moveIsValid(Move*);
	static void correctMoveType(Move*);
	static void makeMove(Move*);

	static std::string formatAsString();
private:
	enum PieceType { NoPiece,
		PawnPieceWhite, KnightPieceWhite, BishopPieceWhite, RookPieceWhite, QueenPieceWhite, KingPieceWhite,
		PawnPieceBlack, KnightPieceBlack, BishopPieceBlack, RookPieceBlack, QueenPieceBlack, KingPieceBlack,
	};
	static const PieceType DEFAULT_BOARD[BOARD_SIZE];

	static BoardState state;
	static Square* board[BOARD_SIZE];
	static bool boardWhiteAttack[BOARD_SIZE];
	static bool boardBlackAttack[BOARD_SIZE];
	static std::vector<Move*> moveList;
};

#endif