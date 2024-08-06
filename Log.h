/* Log.h */
#ifndef LOG_H
#define LOG_H

#include "Piece.h"

void writefile(PIECE *p, int newx, int newy, PIECE *tempBoard[8][8]);

int convertX(int x);

char convertY(int y);

void readfile(void);

#endif
/* EOF */

