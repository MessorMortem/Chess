#include <stdio.h>
#include <stdlib.h>

#include "Log.h"


void writefile(PIECE *p, int newx, int newy, PIECE *tempBoard[8][8])
{
	static int count = 1;

	FILE *fp;
	fp = fopen("Log.txt", "a+");
	if( fp==NULL )
	{
		printf( "Cant open input file Log.txt! \n");
		exit(1);
	}

	if (newx == 10) {
		fprintf(fp, "1-0\n");
		printf("1-0\n");
		fclose(fp);
		return;
	}
	else if (newx == 11) {
		fprintf(fp, "0-1\n");
		printf("0-1\n");
		fclose(fp);
		return;
	}
	else if (newx == 12) {
		fprintf(fp, "1/2-1/2\n");
		printf("1/2-1/2\n");
		fclose(fp);
		return;
	}
	else if (p == NULL) {
		return;
	}

	if (count == 1 && p->color == 0) {
		fprintf(fp, "Log:\n");
	}

	char type;

	if (p->color == 0) {
		if (p->t->t == 0) {
			type = 'p';
		}
		else if (p->t->t == 1) {
			type = 'r';
		}
		else if (p->t->t == 2) {
			type = 'n';
		}
		else if (p->t->t == 3) {
			type = 'b';
		}
		else if (p->t->t == 4) {
			type = 'q';
		}
		else if (p->t->t == 5) {
			type = 'k';
		}	
	}
	else if (p->color == 1) {
		if (p->t->t == 0) {
			type = 'P';
		}
		else if (p->t->t == 1) {
			type = 'R';
		}
		else if (p->t->t == 2) {
			type = 'N';
		}
		else if (p->t->t == 3) {
			type = 'B';
		}
		else if (p->t->t == 4) {
			type = 'Q';
		}
		else if (p->t->t == 5) {
			type = 'K';
		}	
	}

	char convertedoldy = convertY(p->y);

	int convertedoldx = convertX(p->x);

	char convertednewy = convertY(newy);

	int convertednewx = convertX(newx);

	char movement;

	if (tempBoard[newx][newy]) {
		movement = 'x';
	}
	else {
		movement = '-';
	}

	if (p->color == 0) {
		fprintf(fp, "%d. ", count);
		if (p->t->t == 5 && p->y - newy >=2) {
			fprintf(fp, "0-0-0 ");
			printf("Move: 0-0-0\n");
		}
		else if (p->t->t == 5 && newy - p->y >=2) {
			fprintf(fp, "0-0 ");
			printf("Move: 0-0\n");
		}
		else {
			fprintf(fp, "%c%c%d%c%c%d ", type, convertedoldy, convertedoldx, movement, convertednewy, convertednewx);
			printf("Move: %c%c%d%c%c%d \n", type, convertedoldy, convertedoldx, movement, convertednewy, convertednewx);
		}
	}
	else if (p->color == 1) {
		if (p->t->t == 5 && p->y - newy >=2) {
			fprintf(fp, "0-0-0 \n");
			printf("Move: 0-0-0 \n");
		}
		else if (p->t->t == 5 && newy - p->y >=2) {
			fprintf(fp, "0-0 \n");
			printf("Move: 0-0 \n");
		}
		else {
			fprintf(fp, "%c%c%d%c%c%d\n", type, convertedoldy, convertedoldx, movement, convertednewy, convertednewx);
			printf("Move: %c%c%d%c%c%d\n", type, convertedoldy, convertedoldx, movement, convertednewy, convertednewx);
		}
		count++;
	}

	fclose(fp);
}

int convertX(int x) {
	return 8 - x; 
}

char convertY(int y) {
	if (y == 0) {
		 return 'A';
	}
	else if (y == 1) {
		return 'B';
	}
	else if (y == 2) {
		return 'C';
	}
	else if (y == 3) {
		return 'D';
	}
	else if (y == 4) {
		return 'E';
	}
	else if (y == 5) {
		return 'F';
	}
	else if (y == 6) {
		return 'G';
	}
	else if (y == 7) {
		return 'H';
	}
	else {
		return 'I';
	}
}

void readfile(void)
{
	FILE *fp;
	char letter;

	fp=fopen("Log.txt","r");
	if( fp==NULL ) {
                printf( "Can't open input file Log.txt! \n");
    }
	rewind(fp);

	while (letter != EOF) {
		letter = getc(fp);
		if (letter != EOF) {
			printf("%c", letter);
		}
	}
	printf("\n");

	fclose(fp);
}

