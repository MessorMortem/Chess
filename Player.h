#ifndef PLAYER_H
#define PLAYER_H

typedef struct PLAYER PLAYER;

#include "Piece.h"

struct PLAYER  {
    PLAYER *other;
    int color;
    int defending[218][2];
    int dcount;
};

// Initializes player with with certain color
PLAYER *createPlayer(int color, PIECE *Board[8][8]);

// Updates the available moves of the player
void updatePlayer(PLAYER *player, PIECE *Board[8][8]);

void pawnAttack(PLAYER *player, PIECE *piece);

void rookAttack(PLAYER *player, PIECE *piece);

void knightAttack(PLAYER *player, PIECE *piece);

void bishopAttack(PLAYER *player, PIECE *piece);

void queenAttack(PLAYER *player, PIECE *piece);

void kingAttack(PLAYER *player, PIECE *piece);

#endif