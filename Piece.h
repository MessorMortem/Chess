#ifndef PIECE_H
#define PIECE_H

typedef struct TYPE TYPE;

typedef struct PIECE PIECE;

#include "Player.h"
#include "ChessBoard.h"

struct PIECE {
	PIECE *(*board)[8];
	PLAYER *player;
	TYPE *t;
	int color; // 0 = white; 1 = black
	int x;
	int y;
    int movelist[27][2];
    int counter;
    int mark;
};

struct TYPE {
	int t; // type of piece 0 = pawn 1 = rook 2 = knight 3 = bishop 4 = queen 5 = king
	void (*updateMoves)(PIECE *p);
};

//updates the piece movelist based on the movement of a pawn
void updatePawn(PIECE *p);

//updates the piece movelist based on the movement of a rook
void updateRook(PIECE *p);

//updates the piece movelist based on the movement of a knight
void updateKnight(PIECE *p);

//updates the piece movelist based on the movement of a bishop
void updateBishop(PIECE *p);

//updates the piece movelist based on the movement of a queen
void updateQueen(PIECE *p);

//updates the piece movelist based on the movement of a king
void updateKing(PIECE *p);

// Checks if the piece can move to x and y
int checkPiece(PIECE *p, int newx, int newy); 

// Checks if square is attacked by a player
int checkSquare(PLAYER *player, int x, int y);

// Moves the piece to x and y
// Includes special cases for enpassant and castle
void movePiece(PIECE *Board[8][8], PIECE *p, int newx, int newy);

// Resets pawn marks
void unmarkPawn(PIECE *Board[8][8]);

// Checks if an EnPassant move is possible
int EnPassant(PIECE *p, int newx, int newy);

// Checks if the king is in Check
int Check(PIECE *Board[8][8], int color);

// Checks if there are any legal moves that the player can make
int Mate(PIECE *Board[8][8], int color);

// Promotes the pawn
void PawnPromotion(PIECE *p, TYPE *typelist[6]);


#endif
