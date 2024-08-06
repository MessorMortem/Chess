#include "Piece.h"

// Initializes the starting pieces of the board
void startBoard(PIECE *Board[8][8]);

// Copies Board1 to Board2
void copyBoard(PIECE *Board1[8][8], PIECE *Board2[8][8]);

// Sets the initial information of the starting pieces
void setPiece(PIECE *piece, PIECE *(*ptr)[8], int color, TYPE *piecetype, int x, int y);

// Updates the movelist of every piece
void updateMoves(PIECE *Board[8][8]);

