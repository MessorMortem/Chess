#include <stdio.h>

#include "Display.h"

void printBoard(PIECE* Board[8][8])
{
	int NewBoard[8][8][2];

	// Makes a temporary array with information on the type and color of each piece
	for (int i = 0; i <= 7; i++) {
		for (int j = 0; j <= 7; j++) {
			if (Board[i][j]) {
				NewBoard[i][j][0] = Board[i][j]->t->t;
				NewBoard[i][j][1] = Board[i][j]->color;
			}
			else {
				NewBoard[i][j][0] = 6;
				NewBoard[i][j][1] = 0;
			}
		}
	}

	// Prints the board based on type and color of pieces
	// Whte piecess are red in color
	printf("    A   B   C   D   E   F   G   H\n");
	printf("  ┌───┬───┬───┬───┬───┬───┬───┬───┐\n");
	for (int n = 8; n > 0; n--)
	{
		printf("%d │", n);
		for (int j = 0; j <= 7; j++)
		{
			if (NewBoard[8 - n][j][1] == 0)
			{
				if (NewBoard[8 - n][j][0] == 0)
				{
					printf("\033[0;31m");
					printf(" ♙");
					printf("\033[0m");
					printf(" │");
				}
				else if (NewBoard[8 - n][j][0] == 1)
				{
					printf("\033[0;31m");
					printf(" ♖");
					printf("\033[0m");
					printf(" │");

				}
				else if (NewBoard[8 - n][j][0] == 2)
				{
					printf("\033[0;31m");
					printf(" ♘");
					printf("\033[0m");
					printf(" │");
				}
				else if (NewBoard[8 - n][j][0] == 3)
				{
					printf("\033[0;31m");
					printf(" ♗");
					printf("\033[0m");
					printf(" │");

				}
				else if (NewBoard[8 - n][j][0] == 4)
				{
					printf("\033[0;31m");
					printf(" ♕");
					printf("\033[0m");
					printf(" │");

				}
				else if (NewBoard[8 - n][j][0] == 5)
				{
					printf("\033[0;31m");
					printf(" ♔");
					printf("\033[0m");
					printf(" │");
				}
				else if (NewBoard[8 - n][j][0] == 6)
				{
					printf("   │");
				}
			}
			else if (NewBoard[8 - n][j][1] == 1)
			{
				if (NewBoard[8 - n][j][0] == 0)
				{
					printf("\033[0;32m");
					printf(" ♟");
					printf("\033[0m");
					printf(" │");
				}
				else if (NewBoard[8 - n][j][0] == 1)
				{
					printf("\033[0;32m");
					printf(" ♜");
					printf("\033[0m");
					printf(" │");
				}
				else if (NewBoard[8 - n][j][0] == 2)
				{
					printf("\033[0;32m");
					printf(" ♞");
					printf("\033[0m");
					printf(" │");
				}
				else if (NewBoard[8 - n][j][0] == 3)
				{
					printf("\033[0;32m");
					printf(" ♝");
					printf("\033[0m");
					printf(" │");
				}
				else if (NewBoard[8 - n][j][0] == 4)
				{
					printf("\033[0;32m");
					printf(" ♛");
					printf("\033[0m");
					printf(" │");
				}
				else if (NewBoard[8 - n][j][0] == 5)
				{
					printf("\033[0;32m");
					printf(" ♚");
					printf("\033[0m");
					printf(" │");
				}
			}
		}
		printf(" %d\n", n);
		if (n != 1) {
			printf("  ├───┼───┼───┼───┼───┼───┼───┼───┤\n");
		}
	}
	printf("  └───┴───┴───┴───┴───┴───┴───┴───┘\n");
	printf("    A   B   C   D   E   F   G   H\n");

}
