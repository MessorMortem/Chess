#include <stdio.h>
#include <stdlib.h>

#include "ChessBoard.h"

void startBoard(PIECE *Board[8][8]) {
    PIECE *(*ptr)[8];
    ptr = Board;
    // Creates global types for pieces
    TYPE *pawntype = malloc(sizeof(TYPE));
    pawntype->t = 0;
    pawntype->updateMoves = &updatePawn;
    
    TYPE *rooktype = malloc(sizeof(TYPE));
    rooktype->t = 1;
    rooktype->updateMoves = &updateRook;
    
    TYPE *knighttype = malloc(sizeof(TYPE));
    knighttype->t = 2;
    knighttype->updateMoves = &updateKnight;

    TYPE *bishoptype = malloc(sizeof(TYPE));
    bishoptype->t = 3;
    bishoptype->updateMoves = &updateBishop;

    TYPE *queentype = malloc(sizeof(TYPE));
    queentype->t = 4;
    queentype->updateMoves = &updateQueen;

    TYPE *kingtype = malloc(sizeof(TYPE));
    kingtype->t = 5;
    kingtype->updateMoves = &updateKing;
    
    // Creates and places the initial pieces on the board
    // ------- White Pieces -------
    PIECE *rookw1 = malloc(sizeof(PIECE));
    setPiece(rookw1, ptr, 0, rooktype, 7, 0);
    Board[7][0] = rookw1;

    PIECE *knightw1 = malloc(sizeof(PIECE));
    setPiece(knightw1, ptr, 0, knighttype, 7, 1);
    Board[7][1] = knightw1;

    PIECE *bishopw1 = malloc(sizeof(PIECE));
    setPiece(bishopw1, ptr, 0, bishoptype, 7, 2);
    Board[7][2] = bishopw1;

    PIECE *queenw = malloc(sizeof(PIECE));
    setPiece(queenw, ptr, 0, queentype, 7, 3);
    Board[7][3] = queenw;

    PIECE *kingw = malloc(sizeof(PIECE));
    setPiece(kingw, ptr, 0, kingtype, 7, 4);
    Board[7][4] = kingw;

    PIECE *bishopw2 = malloc(sizeof(PIECE));
    setPiece(bishopw2, ptr, 0, bishoptype, 7, 5);
    Board[7][5] = bishopw2;

    PIECE *knightw2 = malloc(sizeof(PIECE));
    setPiece(knightw2, ptr, 0, knighttype, 7, 6);
    Board[7][6] = knightw2;

    PIECE *rookw2 = malloc(sizeof(PIECE));
    setPiece(rookw2, ptr, 0, rooktype, 7, 7);
    Board[7][7] = rookw2;

    // ------- Black Pieces -------
    PIECE *rookb1 = malloc(sizeof(PIECE));
    setPiece(rookb1, ptr, 1, rooktype, 0, 0);
    Board[0][0] = rookb1;

    PIECE *knightb1 = malloc(sizeof(PIECE));
    setPiece(knightb1, ptr, 1, knighttype, 0, 1);
    Board[0][1] = knightb1;

    PIECE *bishopb1 = malloc(sizeof(PIECE));
    setPiece(bishopb1, ptr, 1, bishoptype, 0, 2);
    Board[0][2] = bishopb1;

    PIECE *queenb = malloc(sizeof(PIECE));
    setPiece(queenb, ptr, 1, queentype, 0, 3);
    Board[0][3] = queenb;

    PIECE *kingb = malloc(sizeof(PIECE));
    setPiece(kingb, ptr, 1, kingtype, 0, 4);
    Board[0][4] = kingb;

    PIECE *bishopb2 = malloc(sizeof(PIECE));
    setPiece(bishopb2, ptr, 1, bishoptype, 0, 5);
    Board[0][5] = bishopb2;

    PIECE *knightb2 = malloc(sizeof(PIECE));
    setPiece(knightb2, ptr, 1, knighttype, 0, 6);
    Board[0][6] = knightb2;

    PIECE *rookb2 = malloc(sizeof(PIECE));
    setPiece(rookb2, ptr, 1, rooktype, 0, 7);
    Board[0][7] = rookb2;

    // ------- PAWNS -------
    // White
    PIECE *pawnw1 = malloc(sizeof(PIECE));
    setPiece(pawnw1, ptr, 0, pawntype, 6, 0);
    Board[6][0] = pawnw1;

    PIECE *pawnw2 = malloc(sizeof(PIECE));
    setPiece(pawnw2, ptr, 0, pawntype, 6, 1);
    Board[6][1] = pawnw2;

    PIECE *pawnw3 = malloc(sizeof(PIECE));
    setPiece(pawnw3, ptr, 0, pawntype, 6, 2);
    Board[6][2] = pawnw3;

    PIECE *pawnw4 = malloc(sizeof(PIECE));
    setPiece(pawnw4, ptr, 0, pawntype, 6, 3);
    Board[6][3] = pawnw4;

    PIECE *pawnw5 = malloc(sizeof(PIECE));
    setPiece(pawnw5, ptr, 0, pawntype, 6, 4);
    Board[6][4] = pawnw5;

    PIECE *pawnw6 = malloc(sizeof(PIECE));
    setPiece(pawnw6, ptr, 0, pawntype, 6, 5);
    Board[6][5] = pawnw6;

    PIECE *pawnw7 = malloc(sizeof(PIECE));
    setPiece(pawnw7, ptr, 0, pawntype, 6, 6);
    Board[6][6] = pawnw7;

    PIECE *pawnw8 = malloc(sizeof(PIECE));
    setPiece(pawnw8, ptr, 0, pawntype, 6, 7);
    Board[6][7] = pawnw8;

    // Black
    PIECE *pawnb1 = malloc(sizeof(PIECE));
    setPiece(pawnb1, ptr, 1, pawntype, 1, 0);
    Board[1][0] = pawnb1;

    PIECE *pawnb2 = malloc(sizeof(PIECE));
    setPiece(pawnb2, ptr, 1, pawntype, 1, 1);
    Board[1][1] = pawnb2;

    PIECE *pawnb3 = malloc(sizeof(PIECE));
    setPiece(pawnb3, ptr, 1, pawntype, 1, 2);
    Board[1][2] = pawnb3;

    PIECE *pawnb4 = malloc(sizeof(PIECE));
    setPiece(pawnb4, ptr, 1, pawntype, 1, 3);
    Board[1][3] = pawnb4;

    PIECE *pawnb5 = malloc(sizeof(PIECE));
    setPiece(pawnb5, ptr, 1, pawntype, 1, 4);
    Board[1][4] = pawnb5;

    PIECE *pawnb6 = malloc(sizeof(PIECE));
    setPiece(pawnb6, ptr, 1, pawntype, 1, 5);
    Board[1][5] = pawnb6;

    PIECE *pawnb7 = malloc(sizeof(PIECE));
    setPiece(pawnb7, ptr, 1, pawntype, 1, 6);
    Board[1][6] = pawnb7;

    PIECE *pawnb8 = malloc(sizeof(PIECE));
    setPiece(pawnb8, ptr, 1, pawntype, 1, 7);
    Board[1][7] = pawnb8;

    // The rest of the board points to NULL

    for (int i = 2; i <= 5; i++) {
        for (int j = 0; j <= 7; j++) {
            Board[i][j] = NULL;
        }
    }
}

void copyBoard(PIECE *Board1[8][8], PIECE *Board2[8][8]) {
    for (int i = 0; i <= 7; i++) {
        for (int j = 0; j <= 7; j++) {
            Board2[i][j] = Board1[i][j];
        }
    }
}

void setPiece(PIECE *piece, PIECE *(*boardptr)[8], int color, TYPE *piecetype, int x, int y) {
    piece->board = boardptr;
    piece->color = color;
    piece->t = piecetype;
    piece->x = x;
    piece->y = y;
    piece->counter = 0;
    piece->mark = 0;
}

void updateMoves(PIECE *Board[8][8]) {
    for (int i = 0; i <= 7; i++) {
        for (int j = 0; j <= 7; j++) {
            if (Board[i][j]) {
                Board[i][j]->t->updateMoves(Board[i][j]);
            }
        }
    }
}