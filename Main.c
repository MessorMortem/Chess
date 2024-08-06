#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

#include "Piece.h"
#include "ChessBoard.h"
#include "Display.h"
#include "Player.h"
#include "Conversion.h"
#include "Log.h"
#include "Bluetooth_scan.h"
#include "Server.h"
#include "Client.h"

int main(void) {

	// Initializes board
	srand(time(NULL));
	remove("Log.txt");

    //Initializes bluetooth
    int client, server, s;

	int gamemode;

	printf("\n*********************************\n");
	printf("*********************************\n");
	printf("**************WELCOME************\n");
	printf("*********************************\n");
	printf("**************LETS***************\n");
	printf("**************PLAY***************\n");
	printf("**************CHESS**************\n");
	printf("*********************************\n");
	printf("*********************************\n");
	printf("*********************************\n\n");

	while (1) {
		printf("Select Gamemode\n0-Local, 1-Bluetooth server, 2-Bluetooth client\n");
		printf("Which Game Type?: ");
		scanf("%d", &gamemode);
		if (gamemode >= 0 && gamemode <= 2) {
			break;
		}
		else {
			printf("Invalid input\n");
		}
	}
	printf("\n\n");

    if (gamemode == 1)
    {
        server = server_setup(&s);
    }
    if (gamemode == 2)
    {
        client = client_setup();
    }

	PIECE *Board[8][8];
	PIECE *tempBoard[8][8];

	PIECE *capturedPieces[30];
	for (int n = 0; n < 30; n++) {
		capturedPieces[n] = NULL;
	}
	int capturecount = 0;

	startBoard(Board);
	copyBoard(Board, tempBoard);


	TYPE *typelist[6];
	// Pawn type
	typelist[0] = Board[1][0]->t;
	// Other types
	for (int i = 0; i < 5; i++) {
		typelist[i+1] = Board[0][i]->t;
	}

	PLAYER *playerW = createPlayer(0, Board);
	PLAYER *playerB = createPlayer(1, Board);
	PLAYER* tempptr = playerW;
	playerW->other = playerB;
	playerB->other = tempptr;

	updatePlayer(playerW, Board);
	updatePlayer(playerB, Board);
	updateMoves(Board);
	printBoard(Board);

	char oldletter, newletter;
	int oldnumber, newnumber;
	int oldx, oldy, newx, newy;
	int counter = 1;
	int whitecheck = 0;
	int blackcheck = 0;
	int movecheck;
	int mate;
	int choice = 0;
	int capturetimer = 0;
	int drawcheck = 0;

	PIECE *tempPiece;

	while(1) {
		printf("Turn %d\n", counter);
		counter++;
		while(1) {
			printf("Red's turn\n");
			printf("Make a move-0 OR Print log-1 OR Exit-2\n");
			printf("Choice: ");
            if (gamemode == 0)
                scanf("%d", &choice);
            if (gamemode == 1)
            {
                scanf("%d", &choice);
                server_write(server, choice);
            }
            if (gamemode == 2)
            {
                choice = client_read(client);
                printf("%d\n", choice);
            }

			if (choice == 0) {
				break;
			}
			else if (choice == 1) {
				readfile();
			}
			else if (choice == 2) {
				break;
			}
			else {
				printf("Invalid input\n");
			}
		}
		if (choice == 2) {
			printf("\nBye!\n\n");
			break;
		}
		while(1) {
				// Ask player for movement
				printf("Enter piece you want to move\n");
				printf("Enter Coordinate: ");

                if (gamemode == 0)
                {
                    scanf(" %c", &oldletter);
                    scanf("%d", &oldnumber);
                }
                if (gamemode == 1)
                {
                    scanf(" %c", &oldletter);
                    scanf("%d", &oldnumber);
                    server_write(server, oldletter);
                    server_write(server, oldnumber);
                }
                if (gamemode == 2)
                {
                    oldletter = client_read(client);
                    oldnumber = client_read(client);
                    printf("%c", oldletter);
                    printf("%d\n", oldnumber);
                }

				printf("Enter where you want to move\n");
				printf("Enter Coordinate: ");

                if (gamemode == 0)
                {
                    scanf(" %c", &newletter);
                    scanf("%d", &newnumber);
                }
                if (gamemode == 1)
                {
                    scanf(" %c", &newletter);
                    scanf("%d", &newnumber);
                    server_write(server, newletter);
                    server_write(server, newnumber);
                }
                if (gamemode == 2)
                {
                    newletter = client_read(client);
                    newnumber = client_read(client);
                    printf("%c", newletter);
                    printf("%d\n", newnumber);
                }

				oldx = convertNumber(oldnumber);
				oldy = convertLetter(oldletter);
				newx = convertNumber(newnumber);
				newy = convertLetter(newletter);
			
			// Checks if new coordinates are in the movelist of the piece
			if (Board[oldx][oldy] != NULL) {
				movecheck = checkPiece(Board[oldx][oldy], newx, newy);
			}
			// Check for no piece at spot
			if (oldx > 7 || oldx < 0 || oldy > 7 || oldy < 0 || Board[oldx][oldy] == NULL) {
					printf("Invalid Move: There is no piece there!\n");
			}
			// Checks for correct piece color
			else if (Board[oldx][oldy]->color == 1) {
					printf("Invalid Move: That piece is not yours!\n");
			}
			// If checks pass then the piece is moved and movelists are updated
			else if (movecheck) {
				// Points to new position in case there is a capture
				tempPiece = Board[newx][newy];
				movePiece(Board, Board[oldx][oldy], newx, newy);
				// Updates player defend list after move to see if white is in check
				updatePlayer(playerW, Board);
				updatePlayer(playerB, Board);
				// Checks if white is in check
				whitecheck = Check(Board, 0);
				if (whitecheck) {
					// If white is in check after the move then reset to previous board state
					copyBoard(tempBoard, Board);
					Board[oldx][oldy]->x = oldx;
					Board[oldx][oldy]->y = oldy;
					// Resets defend lists
					updatePlayer(playerW, Board);
					updatePlayer(playerB, Board);

                    printf("Invalid Move: That piece can't move there!\n");
				}
				// White is not in Check after move
				else { 
					unmarkPawn(Board);
					// If there is a piece at new position add to captured pieces array to be freed later
					if (tempPiece) { 
						capturedPieces[capturecount] = tempPiece;
						capturecount++;
						// If there was a capture reset capture timer
						capturetimer = 0;
					}
					// If the moved piece is a pawn reset capture timer
					if (Board[newx][newy]->t->t == 0) {
						capturetimer = 0;
					}
					// Writefile needs information on previous position so the position is temporarily reset
					Board[newx][newy]->x = oldx;
					Board[newx][newy]->y = oldy;
					writefile(tempBoard[oldx][oldy], newx, newy, tempBoard);
					Board[newx][newy]->x = newx;
					Board[newx][newy]->y = newy;
					copyBoard(Board, tempBoard);
					updatePlayer(playerW, Board);
					updatePlayer(playerB, Board);
					updateMoves(Board);
					// Checks if there is a pawn that needs to be promoted
					if (gamemode == 0) {
						PawnPromotion(Board[newx][newy], typelist);
					}
					updatePlayer(playerW, Board);
					updatePlayer(playerB, Board);
					updateMoves(Board);
					blackcheck = Check(Board, 1);
					mate = Mate(Board, 1);
					printBoard(Board);
					break;
				}
			}
			// Executes if the new coordinate is not in the movelist
			else {
					printf("Invalid Move: That piece can't move there!\n");
			}
		}
		
		// If mate is detected then the game ends
		if (mate == 1) {
			// If black is in check and mated, then white wins
			if (blackcheck) {
				writefile(NULL, 10, 10, tempBoard);
				printf("Checkmate! Red Wins\n");
				break;
			}
			// If black is not in check and mated, then stalemate
			else {
				writefile(NULL, 12, 12, tempBoard);
				printf("Stalemate!\n");
				break;
			}
		}

		while(1) {
			printf("Green's turn\n");
			printf("Make a move-0 OR Print log-1 OR Exit-2\n");
			printf("Choice: ");

            if (gamemode == 0)
                scanf("%d", &choice);
            if (gamemode == 1)
            {
                choice = server_read(server);
                printf("%d\n", choice);
            }
            if (gamemode == 2)
            {
                scanf("%d", &choice);
                client_write(client, choice);
            }

			if (choice == 0) {
				break;
			}
			else if (choice == 1) {
				readfile();
			}
			else if (choice == 2){
				break;
			}
			else {
				printf("Invalid input\n");
			}
		}
		if (choice == 2) {
			printf("\nBye !\n\n");
			break;
		}
		while(1) {
				// Ask player for movement
				printf("Enter piece you want to move\n");
				printf("Enter Coordinate: ");

                if (gamemode == 0)
                {
                    scanf(" %c", &oldletter);
                    scanf("%d", &oldnumber);
                }
                if (gamemode == 1)
                {
                   oldletter = server_read(server);
                   oldnumber = server_read(server);
                   printf("%c", oldletter);
                   printf("%d\n", oldnumber);
                }
                if (gamemode == 2)
                {
                    scanf(" %c", &oldletter);
                    scanf("%d", &oldnumber);
                    client_write(client, oldletter);
                    client_write(client, oldnumber);
                }

				printf("Enter where you want to move\n");
				printf("Enter Coordinate: ");

                if (gamemode == 0)
                {
                    scanf(" %c", &newletter);
                    scanf("%d", &newnumber);
                }
                if (gamemode == 1)
                {
                    oldletter = server_read(server);
                    oldnumber = server_read(server);
                    printf("%c", newletter);
                    printf("%d\n", newnumber);
                }
                if (gamemode == 2)
                {
                    scanf(" %c", &newletter);
                    scanf("%d", &newnumber);
                    client_write(client, newletter);
                    client_write(client, newnumber);
                }


				oldx = convertNumber(oldnumber);
				oldy = convertLetter(oldletter);
				newx = convertNumber(newnumber);
				newy = convertLetter(newletter);
			
			// Checks if new coordinates are in the movelist of the piece
			if (Board[oldx][oldy] != NULL) {
				movecheck = checkPiece(Board[oldx][oldy], newx, newy);
			}
			// Check for no piece at spot
			if (oldx > 7 || oldx < 0 || oldy > 7 || oldy < 0 || Board[oldx][oldy] == NULL) {
					printf("Invalid Move: There is no piece there!\n");
			}
			// Checks for correct piece color
			else if (Board[oldx][oldy]->color == 0) {
					printf("Invalid Move: That piece is not yours!\n");
			}
			// If checks pass then the piece is moved and movelists are updated
			else if (movecheck) {
				unmarkPawn(Board);
				// Points to new position in case there is a capture
				tempPiece = Board[newx][newy];
				movePiece(Board, Board[oldx][oldy], newx, newy);
				// Updates player defend list after move to see if black is in check
				updatePlayer(playerW, Board);
				updatePlayer(playerB, Board);
				// Checks if black is in check
				blackcheck = Check(Board, 1);
				if (blackcheck) {
					// If black is in check after the move then reset to previous board state
					copyBoard(tempBoard, Board);
					Board[oldx][oldy]->x = oldx;
					Board[oldx][oldy]->y = oldy;
					// Resets defend lists
					updatePlayer(playerW, Board);
					updatePlayer(playerB, Board);

                    printf("Invalid Move: That piece can't move there!\n");

				}
				// Black is not in Check after move
				else {
					// If there is a piece at new position add to captured pieces array to be freed later
					if (tempPiece) {
						capturedPieces[capturecount] = tempPiece;
						capturecount++;
						// If there was a capture reset capture timer
					}
					else {
						// If there was no capture increment capture timer
						capturetimer++;
					}
					// If the moved piece is a pawn reset capture timer
					if (Board[newx][newy]->t->t == 0) {
						capturetimer = 0;
					}
					// Writefile needs information on previous position so the position is temporarily reset
					Board[newx][newy]->x = oldx;
					Board[newx][newy]->y = oldy;
					writefile(tempBoard[oldx][oldy], newx, newy, tempBoard);
					Board[newx][newy]->x = newx;
					Board[newx][newy]->y = newy;
					copyBoard(Board, tempBoard);
					updatePlayer(playerW, Board);
					updatePlayer(playerB, Board);
					updateMoves(Board);
					// Checks if there is a pawn that needs to be promoted
					if (gamemode == 0) {
						PawnPromotion(Board[newx][newy], typelist);
					}
					updatePlayer(playerW, Board);
					updatePlayer(playerB, Board);
					updateMoves(Board);
					whitecheck = Check(Board, 0);
					mate = Mate(Board, 0);
					printBoard(Board);
					break;
				}
			}
			// Executes if the new coordinate is not in the movelist
			else {
					printf("Invalid Move: That piece can't move there!\n");
			}
		}
		if (capturetimer >= 10) {
			while (1) {
				printf("10 Moves have been made without capture or pawn move.\n");
				printf("Do both players accept a draw? 0-No 1-Yes\n");
				printf("Choice: ");
				scanf("%d",&drawcheck); //<------------------------------------------------------------------------------------------------------------------------
				if (drawcheck >= 0 && drawcheck <= 1) {
					break;
				}
				else {
					printf("Invalid Input\n");
				}
			}
			if (drawcheck) {
				printf("Players agree to a draw\n");
				writefile(NULL, 12, 12, tempBoard);
				break;
			}
		}

		if (drawcheck) {
			printf("Players agree to a draw.\n");
			writefile(NULL, 12, 12, tempBoard);
			break;
		}
		if (mate == 1) {
			if (whitecheck) {
				writefile(NULL, 11, 11, tempBoard);
				printf("Checkmate! Green Wins\n");
				break;
			}
			else {
				writefile(NULL, 12, 12, tempBoard);
				printf("Stalemate!\n");
				break;
			}
		}
	}

	tempPiece = NULL;

	// Free type declarations
	for (int n = 0; n < 6; n++) {
		typelist[n]->updateMoves = NULL;
		free(typelist[n]);
		typelist[n] = NULL;
	}

	// Free Captured Pieces
	for (int n = 0; n < 30; n++) {
		if (capturedPieces[n]) {
			if (capturedPieces[n]->t) {
				capturedPieces[n]->t = NULL;
			}
			if (capturedPieces[n]->player) {
				capturedPieces[n]->player = NULL;
			}
			if (capturedPieces[n]->board) {
				capturedPieces[n]->board = NULL;
			}
			free(capturedPieces[n]);
			capturedPieces[n] = NULL;
		}
		else {
			break;
		}
	} 

	// Free Pieces on Board
	for (int n = 0; n < 8; n++) {
		for (int m = 0; m < 8; m++) {
			if (Board[n][m]) {
				if (Board[n][m]->t) {
					Board[n][m]->t = NULL;
				}
				if (Board[n][m]->player) {
					Board[n][m]->player = NULL;
				}
				if (Board[n][m]->board) {
					Board[n][m]->board = NULL;
				}
				free(Board[n][m]);
				Board[n][m] = NULL;
			}
		}
	}

	// Free Players
	playerW->other = NULL;
	free(playerW);
	playerW = NULL;
	playerB->other = NULL;
	free(playerB);
	playerB = NULL;

    server_close(server, s);
    client_close(client);
	return 0;
}
