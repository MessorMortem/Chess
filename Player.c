#include <stdlib.h>

#include "Player.h"

PLAYER *createPlayer(int color, PIECE *Board[8][8]) {
    PLAYER *player = malloc(sizeof(PLAYER));
    player->color = color;
    player->dcount = 0;
    if (color == 0) {
        for (int i = 6; i < 8; i++) {
            for (int j = 0; j < 8; j++) {
                Board[i][j]->player = player;
            }
        }
    }
    else if (color == 1) {
        for (int i = 0; i < 2; i++) {
            for (int j = 0; j < 8; j++) {
                Board[i][j]->player = player;
            }
        }
    }
    return player;
}

void updatePlayer(PLAYER *player, PIECE *Board[8][8]) {
    
    for (int i = 0; i < 218; i++) {
        for (int j = 0; j < 2; j++) {
            player->defending[i][j] = 9;
        }
    }
    player->dcount = 0;

    
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            if (Board[i][j]) {
                if (Board[i][j]->color == player->color) {
                    if (Board[i][j]->t->t == 0) {
                        pawnAttack(player, Board[i][j]);
                    }
                    else if (Board[i][j]->t->t == 1) {
                        rookAttack(player, Board[i][j]);
                    }
                    else if (Board[i][j]->t->t == 2) {
                        knightAttack(player, Board[i][j]);
                    }
                    else if (Board[i][j]->t->t == 3) {
                        bishopAttack(player, Board[i][j]);
                    }
                    else if (Board[i][j]->t->t == 4) {
                        queenAttack(player, Board[i][j]);
                    }
                    else if (Board[i][j]->t->t == 5) {
                        kingAttack(player, Board[i][j]);
                    }
                }
            }
        }
    }
}

void pawnAttack(PLAYER *player, PIECE *piece) {
    // Attack left
    if (piece->y > 0) {
        if (piece->color == 0) {
            player->defending[player->dcount][0] = piece->x - 1;
            player->defending[player->dcount][1] = piece->y - 1;
            player->dcount++;
        }
        else {
            player->defending[player->dcount][0] = piece->x + 1;
            player->defending[player->dcount][1] = piece->y - 1;
            player->dcount++;
        }
    }

    // Attack right
    if (piece->y < 7) {
        if (piece->color == 0) {
            player->defending[player->dcount][0] = piece->x - 1;
            player->defending[player->dcount][1] = piece->y + 1;
            player->dcount++;
        }
        else {
            player->defending[player->dcount][0] = piece->x + 1;
            player->defending[player->dcount][1] = piece->y + 1;
            player->dcount++;
        }
    }
}

void rookAttack(PLAYER *player, PIECE *piece){
    int x, y;
    // Attack Up
    x = piece->x - 1;
    y = piece->y;
    while (x >= 0) {
        player->defending[player->dcount][0] = x;
        player->defending[player->dcount][1] = y;
        player->dcount++;
        if (piece->board[x][y]) {
            break;
        }
        x--;
    }

    // Attack Down
    x = piece->x + 1;
    y = piece->y;
    while (x <= 7) {
        player->defending[player->dcount][0] = x;
        player->defending[player->dcount][1] = y;
        player->dcount++;
        if (piece->board[x][y]) {
            break;
        }
        x++;
    }

    // Attack Left
    x = piece->x;
    y = piece->y - 1;
    while (y >= 0) {
        player->defending[player->dcount][0] = x;
        player->defending[player->dcount][1] = y;
        player->dcount++;
        if (piece->board[x][y]) {
            break;
        }
        y--;
    }

    // Attack Right
    x = piece->x;
    y = piece->y + 1;
    while (y <= 7) {
        player->defending[player->dcount][0] = x;
        player->defending[player->dcount][1] = y;
        player->dcount++;
        if (piece->board[x][y]) {
            break;
        }
        y++;
    }
}

void knightAttack(PLAYER *player, PIECE *piece){
    int x = piece->x;
    int y = piece->y;

    // up 2, right 1
    if(x - 2 >= 0 && y + 1 < 8) {
        player->defending[player->dcount][0] = x - 2;
        player->defending[player->dcount][1] = y + 1;
        player->dcount++;
    }

    // up 2, left 1
    if(x - 2 >= 0 && y - 1 >= 0) {
        player->defending[player->dcount][0] = x - 2;
        player->defending[player->dcount][1] = y - 1;
        player->dcount++;
    }

    // left 2, up 1
    if(x - 1 >= 0 && y - 2 >= 0) {
        player->defending[player->dcount][0] = x - 1;
        player->defending[player->dcount][1] = y - 2;
        player->dcount++;
    }

    // left 2, down 1
    if(x + 1 < 8 && y - 2 >= 0) {
        player->defending[player->dcount][0] = x + 1;
        player->defending[player->dcount][1] = y - 2;
        player->dcount++;
    }

    // down 2, left 1
    if(x + 2 < 8 && y - 1 >= 0) {
        player->defending[player->dcount][0] = x + 2;
        player->defending[player->dcount][1] = y - 1;
        player->dcount++;
    }

    // down 2, right 1
    if(x + 2 < 8 && y + 1 < 8) {
        player->defending[player->dcount][0] = x + 2;
        player->defending[player->dcount][1] = y + 1;
        player->dcount++;
    }

    // right 2, down 1
    if(x + 1 < 8 && y + 2 < 8) {
        player->defending[player->dcount][0] = x + 1;
        player->defending[player->dcount][1] = y + 2;
        player->dcount++;
    }

    // right 2, up 1
    if(x - 1 >= 0 && y + 2 < 8) {
        player->defending[player->dcount][0] = x - 1;
        player->defending[player->dcount][1] = y + 2;
        player->dcount++;
    }
}

void bishopAttack(PLAYER *player, PIECE *piece) {
    int x, y;
    
    // Attack Up Right
    x = piece->x - 1;
    y = piece->y + 1;
    while (x >= 0 && y < 8) {
        player->defending[player->dcount][0] = x;
        player->defending[player->dcount][1] = y;
        player->dcount++;
        if (piece->board[x][y]) {
            break;
        }
        x--;
        y++;
    }

    // Attack Up Left
    x = piece->x - 1;
    y = piece->y - 1;
    while (x >= 0 && y >= 0) {
        player->defending[player->dcount][0] = x;
        player->defending[player->dcount][1] = y;
        player->dcount++;
        if (piece->board[x][y]) {
            break;
        }
        x--;
        y--;
    }

    // Attack Down Right
    x = piece->x + 1;
    y = piece->y + 1;
    while (x < 8 && y < 8) {
        player->defending[player->dcount][0] = x;
        player->defending[player->dcount][1] = y;
        player->dcount++;
        if (piece->board[x][y]) {
            break;
        }
        x++;
        y++;
    }

    // Attack Down Left
    x = piece->x + 1;
    y = piece->y - 1;
    while (x < 8 && y >= 0) {
        player->defending[player->dcount][0] = x;
        player->defending[player->dcount][1] = y;
        player->dcount++;
        if (piece->board[x][y]) {
            break;
        }
        x++;
        y--;
    }

}

void queenAttack(PLAYER *player, PIECE *piece) {
    int x,y;

    // Attack Up
    x = piece->x - 1;
    y = piece->y;
    while (x >= 0) {
        player->defending[player->dcount][0] = x;
        player->defending[player->dcount][1] = y;
        player->dcount++;
        if (piece->board[x][y]) {
            break;
        }
        x--;
    }

    // Attack Down
    x = piece->x + 1;
    y = piece->y;
    while (x <= 7) {
        player->defending[player->dcount][0] = x;
        player->defending[player->dcount][1] = y;
        player->dcount++;
        if (piece->board[x][y]) {
            break;
        }
        x++;
    }

    // Attack Left
    x = piece->x;
    y = piece->y - 1;
    while (y >= 0) {
        player->defending[player->dcount][0] = x;
        player->defending[player->dcount][1] = y;
        player->dcount++;
        if (piece->board[x][y]) {
            break;
        }
        y--;
    }

    // Attack Right
    x = piece->x;
    y = piece->y + 1;
    while (y <= 7) {
        player->defending[player->dcount][0] = x;
        player->defending[player->dcount][1] = y;
        player->dcount++;
        if (piece->board[x][y]) {
            break;
        }
        y++;
    }

    // Attack Up Right
    x = piece->x - 1;
    y = piece->y + 1;
    while (x >= 0 && y < 8) {
        player->defending[player->dcount][0] = x;
        player->defending[player->dcount][1] = y;
        player->dcount++;
        if (piece->board[x][y]) {
            break;
        }
        x--;
        y++;
    }

    // Attack Up Left
    x = piece->x - 1;
    y = piece->y - 1;
    while (x >= 0 && y >= 0) {
        player->defending[player->dcount][0] = x;
        player->defending[player->dcount][1] = y;
        player->dcount++;
        if (piece->board[x][y]) {
            break;
        }
        x--;
        y--;
    }

    // Attack Down Right
    x = piece->x + 1;
    y = piece->y + 1;
    while (x < 8 && y < 8) {
        player->defending[player->dcount][0] = x;
        player->defending[player->dcount][1] = y;
        player->dcount++;
        if (piece->board[x][y]) {
            break;
        }
        x++;
        y++;
    }

    // Attack Down Left
    x = piece->x + 1;
    y = piece->y - 1;
    while (x < 8 && y >= 0) {
        player->defending[player->dcount][0] = x;
        player->defending[player->dcount][1] = y;
        player->dcount++;
        if (piece->board[x][y]) {
            break;
        }
        x++;
        y--;
    }
}

void kingAttack(PLAYER *player, PIECE *piece) {
    int x, y;
    x = piece->x;
    y = piece->y;

    // Attack Up
    x = piece->x - 1;
    y = piece->y;
    if (x >= 0) {
        player->defending[player->dcount][0] = x;
        player->defending[player->dcount][1] = y;
        player->dcount++;
    }

    // Attack Down
    x = piece->x + 1;
    y = piece->y;
    if (x <= 7) {
        player->defending[player->dcount][0] = x;
        player->defending[player->dcount][1] = y;
        player->dcount++;
    }

    // Attack Left
    x = piece->x;
    y = piece->y - 1;
    if (y >= 0) {
        player->defending[player->dcount][0] = x;
        player->defending[player->dcount][1] = y;
        player->dcount++;
    }

    // Attack Right
    x = piece->x;
    y = piece->y + 1;
    if (y <= 7) {
        player->defending[player->dcount][0] = x;
        player->defending[player->dcount][1] = y;
        player->dcount++;
    }

    // Attack Up Right
    x = piece->x - 1;
    y = piece->y + 1;
    if (x >= 0 && y < 8) {
        player->defending[player->dcount][0] = x;
        player->defending[player->dcount][1] = y;
        player->dcount++;
    }

    // Attack Up Left
    x = piece->x - 1;
    y = piece->y - 1;
    if (x >= 0 && y >= 0) {
        player->defending[player->dcount][0] = x;
        player->defending[player->dcount][1] = y;
        player->dcount++;
    }

    // Attack Down Right
    x = piece->x + 1;
    y = piece->y + 1;
    if (x < 8 && y < 8) {
        player->defending[player->dcount][0] = x;
        player->defending[player->dcount][1] = y;
        player->dcount++;
    }

    // Attack Down Left
    x = piece->x + 1;
    y = piece->y - 1;
    if (x < 8 && y >= 0) {
        player->defending[player->dcount][0] = x;
        player->defending[player->dcount][1] = y;
        player->dcount++;
    }
}
