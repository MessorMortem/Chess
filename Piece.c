#include <stdio.h>

#include "Piece.h"


int enpassant;


void updatePawn(PIECE *p) {
    int i,r,c,x,y, curr_pos_x, curr_pos_y;
    int counter;
    i = 1;
    counter = 0;
    r = 0;
    c = 0;

    curr_pos_x = p->x;
    curr_pos_y = p->y;

    for (x=0; x<27; x++)
    {
        for (y=0; y<2; y++)
        {
            p->movelist[x][y] = 9;
        }
    }

    if (p->color == 1) //top player - black
    {
        if (p->x == 1)
        {
            while (p->board[curr_pos_x + i][curr_pos_y] == NULL)
            {
                if (curr_pos_x + i > 3)
                {
                    break;
                }
                
                else
                {
                    p->movelist[r][c] = curr_pos_x + i;
                    p->movelist[r][c+1] = curr_pos_y;

                    i++;
                    r++;
                    counter++;
                }
            }
            i=1;
        }
        else
        {
            if(p->board[curr_pos_x + i][curr_pos_y] == NULL && curr_pos_x + i < 8)
            {
                p->movelist[r][c] = curr_pos_x + i;
                p->movelist[r][c+1] = curr_pos_y;
                r++;
                counter++;
            }
        }

        //Capture diagonal right down 
        if (p->board[curr_pos_x + 1][curr_pos_y + 1] != NULL && curr_pos_x + 1 < 8 && curr_pos_y + 1 < 8)
        {
            if (p->board[curr_pos_x + 1][curr_pos_y + 1]->color != p->color)
            {
                p->movelist[r][c] = curr_pos_x + 1;
                p->movelist[r][c+1] = curr_pos_y + 1;
                r++;
                counter++;
            }
        }
        //Capture diagonal left down 
        if (p->board[curr_pos_x + 1][curr_pos_y - 1] != NULL && curr_pos_x + 1 < 8 && curr_pos_y - 1 >= 0)
        {
            if (p->board[curr_pos_x + 1][curr_pos_y - 1]->color != p->color)
            {
                p->movelist[r][c] = curr_pos_x + 1;
                p->movelist[r][c+1] = curr_pos_y - 1;
                r++;
                counter++;
            }
        }
        
        //En Passant
        if (enpassant == 1)
        {   //check bounds
            if (curr_pos_x + 1 < 8 && curr_pos_y - 1 >= 0 && p->board[curr_pos_x][curr_pos_y - 1] != NULL)
            {
                //check if piece on left is a white pawn and if it's the correct white pawn to use En Passant on
                if ((p->board[curr_pos_x][curr_pos_y - 1]->t->t == 0) && (p->board[curr_pos_x][curr_pos_y - 1]->color == 0) && (p->board[curr_pos_x][curr_pos_y - 1]->mark == 1))
                {
                    p->movelist[r][c] = curr_pos_x + 1;
                    p->movelist[r][c+1] = curr_pos_y - 1;
                    r++;
                    counter++;
                }
            }
            //check bounds
            if (curr_pos_x + 1 < 8 && curr_pos_y + 1 < 8 && p->board[curr_pos_x][curr_pos_y + 1] != NULL)
            {
                //check if piece on right is a white pawn and if it's the correct white pawn to use En Passant on
                if ((p->board[curr_pos_x][curr_pos_y + 1]->t->t == 0) && (p->board[curr_pos_x][curr_pos_y + 1]->color == 0) && (p->board[curr_pos_x][curr_pos_y + 1]->mark == 1))
                {
                    p->movelist[r][c] = curr_pos_x + 1;
                    p->movelist[r][c+1] = curr_pos_y + 1;
                    r++;
                    counter++;
                }
            }
        }
    }
   
    else if (p->color == 0 ) //bottom player - white
    {
        if (p->x == 6)
        { 
            while (p->board[curr_pos_x - i][curr_pos_y] == NULL)
            {
                if (curr_pos_x - i < 4)
                {
                    break;
                }
                
                else
                {
                    p->movelist[r][c] = curr_pos_x - i;
                    p->movelist[r][c+1] = curr_pos_y;

                    i++;
                    r++;
                    counter++;
                }
            }
            i=1;
        }   
        else
        {
            if(p->board[curr_pos_x - i][curr_pos_y] == NULL && curr_pos_x - i >= 0)
            {
                p->movelist[r][c] = curr_pos_x - i;
                p->movelist[r][c+1] = curr_pos_y;
                r++;
                counter++;
            }
        }

        //Capture diagonal right up
        if (p->board[curr_pos_x - 1][curr_pos_y + 1] != NULL && curr_pos_x - 1 >= 0 && curr_pos_y + 1 < 8)
        {
            if (p->board[curr_pos_x - 1][curr_pos_y + 1]->color != p->color)
            {
                p->movelist[r][c] = curr_pos_x - 1;
                p->movelist[r][c+1] = curr_pos_y + 1;
                r++;
                counter++;
            }
        }
        //Capture diagonal left up
        if (p->board[curr_pos_x - 1][curr_pos_y - 1] != NULL && curr_pos_x - 1 >= 0 && curr_pos_y - 1 >= 0)
        {
            if (p->board[curr_pos_x - 1][curr_pos_y - 1]->color != p->color)
            {
                p->movelist[r][c] = curr_pos_x - 1;
                p->movelist[r][c+1] = curr_pos_y - 1;
                r++;
                counter++;
            }
        }

        //En Passant
        if (enpassant == 1)
        {   //check bounds
            if (curr_pos_x - 1 >= 0 && curr_pos_y - 1 >= 0 && p->board[curr_pos_x][curr_pos_y - 1] != NULL)
            {
                //check if piece on left is a black pawn and if it's the correct black pawn to use En Passant on
                if ((p->board[curr_pos_x][curr_pos_y - 1]->t->t == 0) && (p->board[curr_pos_x][curr_pos_y - 1]->color == 1) && (p->board[curr_pos_x][curr_pos_y - 1]->mark == 1))
                {
                    p->movelist[r][c] = curr_pos_x - 1;
                    p->movelist[r][c+1] = curr_pos_y - 1;
                    r++;
                    counter++;
                }
            }
            //check bounds
            if (curr_pos_x - 1 >= 0 && curr_pos_y + 1 < 8 && p->board[curr_pos_x][curr_pos_y + 1] != NULL)
            {
                //check if piece on right is a black pawn and if it's the correct black pawn to use En Passant on
                if ((p->board[curr_pos_x][curr_pos_y + 1]->t->t == 0) && (p->board[curr_pos_x][curr_pos_y + 1]->color == 1) && (p->board[curr_pos_x][curr_pos_y + 1]->mark == 1))
                {
                    p->movelist[r][c] = curr_pos_x - 1;
                    p->movelist[r][c+1] = curr_pos_y + 1;
                    r++;
                    counter++;
                }
            }
        }
    }
    
    p->counter = counter;  
}


void updateRook(PIECE *p){
    int i,r,c,x,y, curr_pos_x, curr_pos_y = 0;
    int counter;
    i = 1;
    counter = 0;
    r = 0;
    c = 0;

    curr_pos_x = p->x;
    curr_pos_y = p->y;

    for (x=0; x<27; x++)
    {
        for (y=0; y<2; y++)
        {
            p->movelist[x][y] = 9;
        }
    }

    //check horizontal left
    while (p->board[curr_pos_x][curr_pos_y - i] == NULL)
    {
        if (curr_pos_y - i < 0)
        {
            break;
        }
        
        //add to list
        p->movelist[r][c] = curr_pos_x;
        p->movelist[r][c+1] = curr_pos_y - i;

        i++;
        r++;
        counter++;
    }
    if (p->board[curr_pos_x][curr_pos_y - i] != NULL && curr_pos_y - i >= 0)
    {
        if (p->board[curr_pos_x][curr_pos_y - i]->color != p->color)
        {
            p->movelist[r][c] = curr_pos_x;
            p->movelist[r][c+1] = curr_pos_y - i;

            r++;
            counter++;
        } 
    }
    i=1;

    //check horizontal right 
    while (p->board[curr_pos_x][curr_pos_y + i] == NULL)
    {
        if (curr_pos_y + i >= 8)
        {
            break;
        }
        
        //add to list
        p->movelist[r][c] = curr_pos_x;
        p->movelist[r][c+1] = curr_pos_y + i;

        i++;
        r++;
        counter++;
    }
    if (p->board[curr_pos_x][curr_pos_y + i] != NULL && curr_pos_y + i < 8)
    {
        if (p->board[curr_pos_x][curr_pos_y + i]->color != p->color)
        {
            p->movelist[r][c] = curr_pos_x;
            p->movelist[r][c+1] = curr_pos_y + i;

            r++;
            counter++;
        } 
    }
    i=1;

    //check vertical up
    while (p->board[curr_pos_x - i][curr_pos_y] == NULL)
    {
        if (curr_pos_x - i < 0)
        {
            break;
        }

        //add to list
        p->movelist[r][c] = curr_pos_x - i;
        p->movelist[r][c+1] = curr_pos_y;

        i++;
        r++;
        counter++;

    }
    if (p->board[curr_pos_x - i][curr_pos_y] != NULL && curr_pos_x - i >= 0)
    {
        if (p->board[curr_pos_x - i][curr_pos_y]->color != p->color)
        {
            p->movelist[r][c] = curr_pos_x - i;
            p->movelist[r][c+1] = curr_pos_y;

            r++;
            counter++;
        } 
    }
    i=1;

    //check vertical down
    while (p->board[curr_pos_x + i][curr_pos_y] == NULL)
    {
        if (curr_pos_x + i >= 8)
        {
            break;
        }
        
        //add to list
        p->movelist[r][c] = curr_pos_x + i;
        p->movelist[r][c+1] = curr_pos_y;
  
        i++;
        r++;
        counter++;
    }
    if (p->board[curr_pos_x + i][curr_pos_y] != NULL && curr_pos_x + i < 8)
    {
        if (p->board[curr_pos_x + i][curr_pos_y]->color != p->color)
        {
            p->movelist[r][c] = curr_pos_x + i;
            p->movelist[r][c+1] = curr_pos_y;

            r++;
            counter++;
        } 
    }
    i=1;

    p->counter = counter;

}


void updateKnight(PIECE *p){
    int r,c,x,y, curr_pos_x, curr_pos_y;
    int counter;
    counter = 0;
    r = 0;
    c = 0;

    curr_pos_x = p->x;
    curr_pos_y = p->y;

    for (x=0; x<27; x++)
    {
        for (y=0; y<2; y++)
        {
            p->movelist[x][y] = 9;
        }
    }

    //check up 2, right 1
    if(curr_pos_x - 2 >= 0 && curr_pos_y + 1 < 8)
    {
        if (p->board[curr_pos_x - 2][curr_pos_y + 1] == NULL)
        {
            p->movelist[r][c] = curr_pos_x - 2;
            p->movelist[r][c+1] = curr_pos_y + 1;
            r++;
            counter++;
        }
        else if(p->board[curr_pos_x - 2][curr_pos_y + 1] != NULL && p->board[curr_pos_x - 2][curr_pos_y + 1]->color != p->color)
        {
            p->movelist[r][c] = curr_pos_x - 2;
            p->movelist[r][c+1] = curr_pos_y + 1;
            r++;
            counter++;
        }
    }

    //check right 2, up 1
    if (curr_pos_x - 1 >= 0 && curr_pos_y + 2 < 8)
    {
        if (p->board[curr_pos_x - 1][curr_pos_y + 2] == NULL)
        {
            p->movelist[r][c] = curr_pos_x - 1;
            p->movelist[r][c+1] = curr_pos_y + 2;
            r++;
            counter++;
        }
        else if (p->board[curr_pos_x - 1][curr_pos_y + 2] != NULL && p->board[curr_pos_x - 1][curr_pos_y + 2]->color != p->color)
        {
            p->movelist[r][c] = curr_pos_x - 1;
            p->movelist[r][c+1] = curr_pos_y + 2;
            r++;
            counter++;
        }
    }

    //check right 2, down 1
    if (curr_pos_x + 1 < 8 && curr_pos_y + 2 < 8)
    {
        if (p->board[curr_pos_x + 1][curr_pos_y + 2] == NULL)
        {
            p->movelist[r][c] = curr_pos_x + 1;
            p->movelist[r][c+1] = curr_pos_y + 2;
            r++;
            counter++;
        }
        else if (p->board[curr_pos_x + 1][curr_pos_y + 2] != NULL && p->board[curr_pos_x + 1][curr_pos_y + 2]->color != p->color)
        {
            p->movelist[r][c] = curr_pos_x + 1;
            p->movelist[r][c+1] = curr_pos_y + 2;
            r++;
            counter++;
        }
    }

    //check right 1, down 2
    if (curr_pos_x + 2 < 8 && curr_pos_y + 1 < 8)
    {
        if (p->board[curr_pos_x + 2][curr_pos_y + 1] == NULL)
        {
            p->movelist[r][c] = curr_pos_x + 2;
            p->movelist[r][c+1] = curr_pos_y + 1;
            r++;
            counter++;
        }
        else if (p->board[curr_pos_x + 2][curr_pos_y + 1] != NULL && p->board[curr_pos_x + 2][curr_pos_y + 1]->color != p->color)
        {
            p->movelist[r][c] = curr_pos_x + 2;
            p->movelist[r][c+1] = curr_pos_y + 1;
            r++;
            counter++;
        }
    }

    //check left 1, up 2
    if (curr_pos_x - 2 >= 0 && curr_pos_y - 1 >= 0)
    {
        if (p->board[curr_pos_x - 2][curr_pos_y - 1] == NULL)
        {
            p->movelist[r][c] = curr_pos_x - 2;
            p->movelist[r][c+1] = curr_pos_y - 1;
            r++;
            counter++;
        }
        else if (p->board[curr_pos_x - 2][curr_pos_y - 1] != NULL && p->board[curr_pos_x - 2][curr_pos_y - 1]->color != p->color)
        {
            p->movelist[r][c] = curr_pos_x - 2;
            p->movelist[r][c+1] = curr_pos_y - 1;
            r++;
            counter++;
        }
    }

    //check left 2, up 1
    if (curr_pos_x - 1 >= 0 && curr_pos_y - 2 >= 0)
    {
        if (p->board[curr_pos_x - 1][curr_pos_y - 2] == NULL)
        {
            p->movelist[r][c] = curr_pos_x - 1;
            p->movelist[r][c+1] = curr_pos_y - 2;
            r++;
            counter++;
        }
        else if (p->board[curr_pos_x - 1][curr_pos_y - 2] != NULL && p->board[curr_pos_x - 1][curr_pos_y - 2]->color != p->color)
        {
            p->movelist[r][c] = curr_pos_x - 1;
            p->movelist[r][c+1] = curr_pos_y - 2;
            r++;
            counter++;
        }
    }

    //check left 1, down 2
    if (curr_pos_x + 2 < 8 && curr_pos_y - 1 >= 0)
    {
        if (p->board[curr_pos_x + 2][curr_pos_y - 1] == NULL)
        {
            p->movelist[r][c] = curr_pos_x + 2;
            p->movelist[r][c+1] = curr_pos_y - 1;
            r++;
            counter++;
        }
        else if (p->board[curr_pos_x + 2][curr_pos_y - 1] != NULL && p->board[curr_pos_x + 2][curr_pos_y - 1]->color != p->color)
        {
            p->movelist[r][c] = curr_pos_x + 2;
            p->movelist[r][c+1] = curr_pos_y - 1;
            r++;
            counter++;
        }
    }
  
    //check left 2, down 1
    if (curr_pos_x + 1 < 8 && curr_pos_y - 2 >= 0)
    {
        if (p->board[curr_pos_x + 1][curr_pos_y - 2] == NULL)
        {
            p->movelist[r][c] = curr_pos_x + 1;
            p->movelist[r][c+1] = curr_pos_y - 2;
            r++;
            counter++;
        }
        else if (p->board[curr_pos_x + 1][curr_pos_y - 2] != NULL && p->board[curr_pos_x + 1][curr_pos_y - 2]->color != p->color)
        {
            p->movelist[r][c] = curr_pos_x + 1;
            p->movelist[r][c+1] = curr_pos_y - 2;
            r++;
            counter++;
        }
    }
    p->counter = counter;

}


void updateBishop(PIECE *p){
    int i,r,c,x,y, curr_pos_x, curr_pos_y;
    int counter;
    i = 1;
    counter = 0;
    r = 0;
    c = 0;

    curr_pos_x = p->x;
    curr_pos_y = p->y;

    for (x=0; x<27; x++)
    {
        for (y=0; y<2; y++)
        {
            p->movelist[x][y] = 9;
        }
    }

    //check diagonal right up
    while (p->board[curr_pos_x - i][curr_pos_y + i] == NULL)
    {
        if (curr_pos_x - i < 0 || curr_pos_y + i >= 8)
        {
            break;
        }
        
        //add to list
        p->movelist[r][c] = curr_pos_x - i;
        p->movelist[r][c+1] = curr_pos_y + i;
  
        i++;
        r++;
        counter++;
    }
    if (p->board[curr_pos_x - i][curr_pos_y + i] != NULL && curr_pos_x - i >= 0 && curr_pos_y + i < 8)
    {
        if (p->board[curr_pos_x - i][curr_pos_y + i]->color != p->color)
        {
            p->movelist[r][c] = curr_pos_x - i;
            p->movelist[r][c+1] = curr_pos_y + i;

            r++;
            counter++;
        } 
    }
    i=1;
    
    //check diagonal right down
    while (p->board[curr_pos_x + i][curr_pos_y + i] == NULL)
    {
        if (curr_pos_x + i >= 8 || curr_pos_y + i >= 8)
        {
            break;
        }
        
        //add to list
        p->movelist[r][c] = curr_pos_x + i;
        p->movelist[r][c+1] = curr_pos_y + i;
  
        i++;
        r++;
        counter++;
    }
    if (p->board[curr_pos_x + i][curr_pos_y + i] != NULL && curr_pos_x + i < 8 && curr_pos_y + i < 8)
    {
        if (p->board[curr_pos_x + i][curr_pos_y + i]->color != p->color)
        {
            p->movelist[r][c] = curr_pos_x + i;
            p->movelist[r][c+1] = curr_pos_y + i;

            r++;
            counter++;
        } 
    }
    i=1;

    //check diagonal left up
    while (p->board[curr_pos_x - i][curr_pos_y - i] == NULL)
    {
        if (curr_pos_x - i < 0 || curr_pos_y - i < 0)
        {
            break;
        }
        
        //add to list
        p->movelist[r][c] = curr_pos_x - i;
        p->movelist[r][c+1] = curr_pos_y - i;
  
        i++;
        r++;
        counter++;
    }
    if (p->board[curr_pos_x - i][curr_pos_y - i] != NULL && curr_pos_x - i >= 0 && curr_pos_y - i >= 0)
    {
        if (p->board[curr_pos_x - i][curr_pos_y - i]->color != p->color)
        {
            p->movelist[r][c] = curr_pos_x - i;
            p->movelist[r][c+1] = curr_pos_y - i;

            r++;
            counter++;
        } 
    }
    i=1;

    //check diagonal left down
    while (p->board[curr_pos_x + i][curr_pos_y - i] == NULL)
    {
        if (curr_pos_x + i >= 8 || curr_pos_y - i < 0)
        {
            break;
        }
        
        //add to list
        p->movelist[r][c] = curr_pos_x + i;
        p->movelist[r][c+1] = curr_pos_y - i;
  
        i++;
        r++;
        counter++;
    }
    if (p->board[curr_pos_x + i][curr_pos_y - i] != NULL && curr_pos_x + i < 8 && curr_pos_y - i >= 0)
    {
        if (p->board[curr_pos_x + i][curr_pos_y - i]->color != p->color)
        {
            p->movelist[r][c] = curr_pos_x + i;
            p->movelist[r][c+1] = curr_pos_y - i;

            r++;
            counter++;
        } 
    }
    i=1;

    p->counter = counter;
}

void updateQueen(PIECE *p){
    int i,r,c,x,y, curr_pos_x, curr_pos_y;
    int counter;
    i = 1;
    counter = 0;
    r = 0;
    c = 0;

    curr_pos_x = p->x;
    curr_pos_y = p->y;

    for (x=0; x<27; x++)
    {
        for (y=0; y<2; y++)
        {
            p->movelist[x][y] = 9;
        }
    }

    //check horizontal left
    while (p->board[curr_pos_x][curr_pos_y - i] == NULL)
    {
        if (curr_pos_y - i < 0)
        {
            break;
        }
        
        //add to list
        p->movelist[r][c] = curr_pos_x;
        p->movelist[r][c+1] = curr_pos_y - i;

        i++;
        r++;
        counter++;
    }
    if (p->board[curr_pos_x][curr_pos_y - i] != NULL && curr_pos_y - i >= 0)
    {
        if (p->board[curr_pos_x][curr_pos_y - i]->color != p->color)
        {
            p->movelist[r][c] = curr_pos_x;
            p->movelist[r][c+1] = curr_pos_y - i;

            r++;
            counter++;
        } 
    }
    i=1;

    //check horizontal right 
    while (p->board[curr_pos_x][curr_pos_y + i] == NULL)
    {
        if (curr_pos_y + i >= 8)
        {
            break;
        }
        
        //add to list
        p->movelist[r][c] = curr_pos_x;
        p->movelist[r][c+1] = curr_pos_y + i;

        i++;
        r++;
        counter++;
    }
    if (p->board[curr_pos_x][curr_pos_y + i] != NULL && curr_pos_y + i < 8)
    {
        if (p->board[curr_pos_x][curr_pos_y + i]->color != p->color)
        {
            p->movelist[r][c] = curr_pos_x;
            p->movelist[r][c+1] = curr_pos_y + i;

            r++;
            counter++;
        } 
    }
    i=1;

    //check vertical up
    while (p->board[curr_pos_x - i][curr_pos_y] == NULL)
    {
        if (curr_pos_x - i < 0)
        {
            break;
        }
        
        //add to list
        p->movelist[r][c] = curr_pos_x - i;
        p->movelist[r][c+1] = curr_pos_y;

        i++;
        r++;
        counter++;
    }
    if (p->board[curr_pos_x - i][curr_pos_y] != NULL && curr_pos_x - i >= 0)
    {
        if (p->board[curr_pos_x - i][curr_pos_y]->color != p->color)
        {
            p->movelist[r][c] = curr_pos_x - i;
            p->movelist[r][c+1] = curr_pos_y;

            r++;
            counter++;
        } 
    }
    i=1;

    //check vertical down
    while (p->board[curr_pos_x + i][curr_pos_y] == NULL)
    {
        if (curr_pos_x + i >= 8)
        {
            break;
        }
        
        //add to list
        p->movelist[r][c] = curr_pos_x + i;
        p->movelist[r][c+1] = curr_pos_y;
  
        i++;
        r++;
        counter++;
    }
    if (p->board[curr_pos_x + i][curr_pos_y] != NULL && curr_pos_x + i < 8)
    {
        if (p->board[curr_pos_x + i][curr_pos_y]->color != p->color)
        {
            p->movelist[r][c] = curr_pos_x + i;
            p->movelist[r][c+1] = curr_pos_y;

            r++;
            counter++;
        } 
    }
    i=1;

    //check diagonal right up
    while (p->board[curr_pos_x - i][curr_pos_y + i] == NULL)
    {
        if (curr_pos_x - i < 0 || curr_pos_y + i >= 8)
        {
            break;
        }
        
        //add to list
        p->movelist[r][c] = curr_pos_x - i;
        p->movelist[r][c+1] = curr_pos_y + i;
  
        i++;
        r++;
        counter++;
    }
    if (p->board[curr_pos_x - i][curr_pos_y + i] != NULL && curr_pos_x - i >= 0 && curr_pos_y + i < 8)
    {
        if (p->board[curr_pos_x - i][curr_pos_y + i]->color != p->color)
        {
            p->movelist[r][c] = curr_pos_x - i;
            p->movelist[r][c+1] = curr_pos_y + i;

            r++;
            counter++;
        } 
    }
    i=1;
    
    //check diagonal right down
    while (p->board[curr_pos_x + i][curr_pos_y + i] == NULL)
    {
        if (curr_pos_x + i >= 8 || curr_pos_y + i >= 8)
        {
            break;
        }
        
        //add to list
        p->movelist[r][c] = curr_pos_x + i;
        p->movelist[r][c+1] = curr_pos_y + i;
  
        i++;
        r++;
        counter++;
    }
    if (p->board[curr_pos_x + i][curr_pos_y + i] != NULL && curr_pos_x + i < 8 && curr_pos_y + i < 8)
    {
        if (p->board[curr_pos_x + i][curr_pos_y + i]->color != p->color)
        {
            p->movelist[r][c] = curr_pos_x + i;
            p->movelist[r][c+1] = curr_pos_y + i;

            r++;
            counter++;
        } 
    }
    i=1;

    //check diagonal left up
    while (p->board[curr_pos_x - i][curr_pos_y - i] == NULL)
    {
        if (curr_pos_x - i < 0 || curr_pos_y - i < 0)
        {
            break;
        }
        
        //add to list
        p->movelist[r][c] = curr_pos_x - i;
        p->movelist[r][c+1] = curr_pos_y - i;
  
        i++;
        r++;
        counter++;
    }
    if (p->board[curr_pos_x - i][curr_pos_y - i] != NULL && curr_pos_x - i >= 0 && curr_pos_y - i >= 0)
    {
        if (p->board[curr_pos_x - i][curr_pos_y - i]->color != p->color)
        {
            p->movelist[r][c] = curr_pos_x - i;
            p->movelist[r][c+1] = curr_pos_y - i;

            r++;
            counter++;
        } 
    }
    i=1;

    //check diagonal left down
    while (p->board[curr_pos_x + i][curr_pos_y - i] == NULL)
    {
        if (curr_pos_x + i >= 8 || curr_pos_y - i < 0)
        {
            break;
        }
        
        //add to list
        p->movelist[r][c] = curr_pos_x + i;
        p->movelist[r][c+1] = curr_pos_y - i;
  
        i++;
        r++;
        counter++;
    }
    if (p->board[curr_pos_x + i][curr_pos_y - i] != NULL && curr_pos_x + i < 8 && curr_pos_y - i >= 0)
    {
        if (p->board[curr_pos_x + i][curr_pos_y - i]->color != p->color)
        {
            p->movelist[r][c] = curr_pos_x + i;
            p->movelist[r][c+1] = curr_pos_y - i;

            r++;
            counter++;
        } 
    }
    i=1;

    p->counter = counter;
}


void updateKing(PIECE *p){
    int r,c,x,y, curr_pos_x, curr_pos_y;
    int counter;
    counter = 0;
    r = 0;
    c = 0;

    curr_pos_x = p->x;
    curr_pos_y = p->y;

    for (x=0; x<27; x++)
    {
        for (y=0; y<2; y++)
        {
            p->movelist[x][y] = 9;
        }
    }

    //check 1 square right
    if (curr_pos_y + 1 < 8)
    {
        if (p->board[curr_pos_x][curr_pos_y + 1] == NULL && checkSquare(p->player->other, curr_pos_x, curr_pos_y + 1) != 1)
        {
            p->movelist[r][c] = curr_pos_x;
            p->movelist[r][c+1] = curr_pos_y + 1;
            r++;
            counter++;
        }
        else if (p->board[curr_pos_x][curr_pos_y + 1] != NULL && p->board[curr_pos_x][curr_pos_y + 1]->color != p->color && checkSquare(p->player->other, curr_pos_x, curr_pos_y + 1) != 1)
        {
            p->movelist[r][c] = curr_pos_x;
            p->movelist[r][c+1] = curr_pos_y + 1;
            r++;
            counter++;
        }
    }

    //check 1 square left
    if (curr_pos_y - 1 >= 0)
    {
        if (p->board[curr_pos_x][curr_pos_y - 1] == NULL && checkSquare(p->player->other, curr_pos_x, curr_pos_y - 1) != 1)
        {
            p->movelist[r][c] = curr_pos_x;
            p->movelist[r][c+1] = curr_pos_y - 1;
            r++;
            counter++;
        }
        else if (p->board[curr_pos_x][curr_pos_y - 1] != NULL && p->board[curr_pos_x][curr_pos_y - 1]->color != p->color && checkSquare(p->player->other, curr_pos_x, curr_pos_y - 1) != 1)
        {
            p->movelist[r][c] = curr_pos_x;
            p->movelist[r][c+1] = curr_pos_y - 1;
            r++;
            counter++;
        }
    }

    //check 1 square up
    if (curr_pos_x - 1 >= 0)
    {
        if (p->board[curr_pos_x - 1][curr_pos_y] == NULL && checkSquare(p->player->other, curr_pos_x - 1, curr_pos_y) != 1)
        {
            p->movelist[r][c] = curr_pos_x - 1;
            p->movelist[r][c+1] = curr_pos_y;
            r++;
            counter++;
        }
        else if (p->board[curr_pos_x - 1][curr_pos_y] != NULL && p->board[curr_pos_x - 1][curr_pos_y]->color != p->color && checkSquare(p->player->other, curr_pos_x - 1, curr_pos_y) != 1)
        {
            p->movelist[r][c] = curr_pos_x - 1;
            p->movelist[r][c+1] = curr_pos_y;
            r++;
            counter++;
        }
    }

    //check 1 square down
    if (curr_pos_x + 1 < 8)
    {
        if (p->board[curr_pos_x + 1][curr_pos_y] == NULL && checkSquare(p->player->other, curr_pos_x + 1, curr_pos_y) != 1)
        {
            p->movelist[r][c] = curr_pos_x + 1;
            p->movelist[r][c+1] = curr_pos_y;
            r++;
            counter++;
        }
        else if (p->board[curr_pos_x + 1][curr_pos_y] != NULL && p->board[curr_pos_x + 1][curr_pos_y]->color != p->color && checkSquare(p->player->other, curr_pos_x + 1, curr_pos_y) != 1)
        {
            p->movelist[r][c] = curr_pos_x + 1;
            p->movelist[r][c+1] = curr_pos_y;
            r++;
            counter++;
        }
    }

    //check 1 square right diagonal up
    if (curr_pos_x - 1 >= 0 && curr_pos_y + 1 < 8)
    {
        if (p->board[curr_pos_x - 1][curr_pos_y + 1] == NULL && checkSquare(p->player->other, curr_pos_x - 1, curr_pos_y + 1) != 1)
        {
            p->movelist[r][c] = curr_pos_x - 1;
            p->movelist[r][c+1] = curr_pos_y + 1;
            r++;
            counter++;
        }
        else if (p->board[curr_pos_x - 1][curr_pos_y + 1] != NULL && p->board[curr_pos_x - 1][curr_pos_y + 1]->color != p->color && checkSquare(p->player->other, curr_pos_x - 1, curr_pos_y + 1) != 1)
        {
            p->movelist[r][c] = curr_pos_x - 1;
            p->movelist[r][c+1] = curr_pos_y + 1;
            r++;
            counter++;
        }
    }

    //check 1 square right diagonal down
    if (curr_pos_x + 1 < 8 && curr_pos_y + 1 < 8)
    {
        if (p->board[curr_pos_x + 1][curr_pos_y + 1] == NULL && checkSquare(p->player->other, curr_pos_x + 1, curr_pos_y + 1) != 1)
        {
            p->movelist[r][c] = curr_pos_x + 1;
            p->movelist[r][c+1] = curr_pos_y + 1;
            r++;
            counter++;
        }
        else if (p->board[curr_pos_x + 1][curr_pos_y + 1] != NULL && p->board[curr_pos_x + 1][curr_pos_y + 1]->color != p->color && checkSquare(p->player->other, curr_pos_x + 1, curr_pos_y + 1) != 1)
        {
            p->movelist[r][c] = curr_pos_x + 1;
            p->movelist[r][c+1] = curr_pos_y + 1;
            r++;
            counter++;
        }
    }

    //check 1 square left diagonal up
    if(curr_pos_x - 1 >= 0 && curr_pos_y - 1 >= 0)
    {
        if (p->board[curr_pos_x - 1][curr_pos_y - 1] == NULL && checkSquare(p->player->other, curr_pos_x - 1, curr_pos_y - 1) != 1)
        {
            p->movelist[r][c] = curr_pos_x - 1;
            p->movelist[r][c+1] = curr_pos_y - 1;
            r++;
            counter++;
        }
        else if (p->board[curr_pos_x - 1][curr_pos_y - 1] != NULL && p->board[curr_pos_x - 1][curr_pos_y - 1]->color != p->color && checkSquare(p->player->other, curr_pos_x - 1, curr_pos_y - 1) != 1)
        {
            p->movelist[r][c] = curr_pos_x - 1;
            p->movelist[r][c+1] = curr_pos_y - 1;
            r++;
            counter++;
        }
    }

    //check 1 square left diagonal down
    if (curr_pos_x + 1 < 8 && curr_pos_y - 1 >= 0)
    {
        if (p->board[curr_pos_x + 1][curr_pos_y - 1] == NULL && checkSquare(p->player->other, curr_pos_x + 1, curr_pos_y - 1) != 1)
        {
            p->movelist[r][c] = curr_pos_x + 1;
            p->movelist[r][c+1] = curr_pos_y - 1;
            r++;
            counter++;
        }
        else if (p->board[curr_pos_x + 1][curr_pos_y - 1] != NULL && p->board[curr_pos_x + 1][curr_pos_y - 1]->color != p->color && checkSquare(p->player->other, curr_pos_x + 1, curr_pos_y - 1) != 1)
        {
            p->movelist[r][c] = curr_pos_x + 1;
            p->movelist[r][c+1] = curr_pos_y - 1;
            r++;
            counter++;
        }
    }

    // Castle
    // Check if king has not moved
    if (p->mark == 0) {
        // White King
        if (p->color == 0) {
            if (p->board[7][0]) {
                // Queenside Castle
                if (p->board[7][0]->t->t == 1 && p->board[7][0]->mark == 0) {
                    if (checkSquare(p->player->other, 7, 0) || checkSquare(p->player->other, 7, 1) || checkSquare(p->player->other, 7, 2) || checkSquare(p->player->other, 7, 3) || checkSquare(p->player->other, 7, 4)) {
                    }
                    else if (p->board[7][1] || p->board[7][2] || p->board[7][3]) {
                    }
                    else {
                        p->movelist[r][c] = 7;
                        p->movelist[r][c+1] = 2; 
                        counter++;
                    }
                }
            }
            if (p->board[7][7]) {
                // Kingside Castle
                if (p->board[7][7]->t->t == 1 && p->board[7][7]->mark == 0) {
                    if (checkSquare(p->player->other, 7, 4) || checkSquare(p->player->other, 7, 5) || checkSquare(p->player->other, 7, 6) || checkSquare(p->player->other, 7, 7)) {
                    }
                    else if (p->board[7][5] || p->board[7][6]) {
                    }
                    else {
                        p->movelist[r][c] = 7;
                        p->movelist[r][c+1] = 6; 
                        counter++;
                    }
                }
            }
        }
        // Black King
        else if (p->color == 1) {
            if (p->board[0][0]) {
                // Queenside Castle
                if (p->board[0][0]->t->t == 1 && p->board[0][0]->mark == 0) {
                    if (checkSquare(p->player->other, 0, 0) || checkSquare(p->player->other, 0, 1) || checkSquare(p->player->other, 0, 2) || checkSquare(p->player->other, 0, 3) || checkSquare(p->player->other, 0, 4)) {
                    }
                    else if (p->board[0][1] || p->board[0][2] || p->board[0][3]) {
                    }
                    else {
                        p->movelist[r][c] = 0;
                        p->movelist[r][c+1] = 2; 
                        counter++;
                    }
                }
            }
            if (p->board[0][7]) {
                // Kingside Castle
                if (p->board[0][7]->t->t == 1 && p->board[0][7]->mark == 0) {
                    if (checkSquare(p->player->other, 0, 4) || checkSquare(p->player->other, 0, 5) || checkSquare(p->player->other, 0, 6) || checkSquare(p->player->other, 0, 7)) {
                    }
                    else if (p->board[0][5] || p->board[0][6]) {
                    }
                    else {
                        p->movelist[r][c] = 0;
                        p->movelist[r][c+1] = 6; 
                        counter++;
                    }
                }
            }
        }
    }

    p->counter = counter;
}

int checkSquare(PLAYER *player, int x, int y) {
    for (int i = 0; i < player->dcount; i++) {
        if (player->defending[i][0] == x && player->defending[i][1] == y) {
            return 1;
        }
    }
    return 0;
}

int checkPiece(PIECE *p, int newx, int newy){
    //check if new move is a valid move

    int x;
    int counter;
    int templist[27][2];

    counter = p->counter;
    
    for (int i = 0; i < 27; i++) {
        for (int j = 0; j < 2; j++) {
            templist[i][j] = p->movelist[i][j];
        }
    }

    for (x=0; x<counter; x++)
    {
        if ((templist[x][0] == newx) && (templist[x][1] == newy))
        {
            return 1;
        }
    }
    return 0;
}

void movePiece(PIECE *Board[8][8], PIECE *p, int newx, int newy){
    
    
    // If it is a pawn that moves two space and there is an enemy pawn in the correct position, it is marked
    if (EnPassant(p, newx, newy))
    {
        p->mark = 1;
    }
    else {p->mark = 0;}

    // If pawn AND moving pawn to new column
    if (p->t->t == 0 && p->y != newy) {
        // If there is a pawn right next to the pawn you are moving AND it is marked
        if (Board[p->x][newy]) {
            if (Board[p->x][newy]->t->t == 0 && Board[p->x][newy]->mark == 1) {
                Board[p->x][newy] = NULL;
            }
        }
    }

    // Mark king or Rook if they move
    if (p->t->t == 5 || p->t->t == 1) {
        p->mark = 1;
    }

    // Move rook if castling
    if (p->t->t == 5) {
        // Queenside
        if (p->y - newy == 2) {
            Board[p->x][3] = Board[p->x][0];
            Board[p->x][3]->y = 3;
            Board[p->x][0] = NULL;
        }
        // Kingside
        else if (newy - p->y == 2) {
            Board[p->x][5] = Board[p->x][7];
            Board[p->x][5]->y = 5;
            Board[p->x][7] = NULL;
        }
    }
    
    Board[newx][newy] = p;
    Board[p->x][p->y] = NULL;
    p->x = newx;
    p->y = newy;
}

void unmarkPawn(PIECE *Board[8][8]) {
    for (int i = 3; i <=4; i++) {
        for (int j = 0; j < 8; j++) {
            if (Board[i][j]) {
                if (Board[i][j]->t->t == 0) {
                    Board[i][j]->mark = 0;
                }
            }
        }
    }
}

int EnPassant(PIECE *p, int newx, int newy){
    int curr_pos_x, curr_pos_y;
    enpassant = 0;
    curr_pos_x = p->x;
    curr_pos_y = p->y;

    //white player - bottom
    if (p->t->t == 0 && p->color == 0){
        if ((curr_pos_x - 2 == 4) && (curr_pos_x - 2 == newx)){   //Check if pawn moved 2 times
            if (p->board[curr_pos_x -2][curr_pos_y +1] != NULL){
                //check if piece on right is a black pawn
                if (p->board[curr_pos_x - 2][curr_pos_y + 1]->t->t == 0 && p->board[curr_pos_x - 2][curr_pos_y + 1]->color == 1){
                    enpassant = 1;
                    
                }
            }
            if (p->board[curr_pos_x -2][curr_pos_y - 1] != NULL){
                //check if piece on left is a black pawn
                if (p->board[curr_pos_x - 2][curr_pos_y - 1]->t->t == 0 && p->board[curr_pos_x - 2][curr_pos_y - 1]->color == 1){
                    enpassant = 1;
                }
            }
        }
    }

    //black player - top
    if (p->t->t == 0 && p->color == 1){
        if ((curr_pos_x + 2 == 3) && (curr_pos_x + 2 == newx)){
            if (p->board[curr_pos_x +2][curr_pos_y +1] != NULL){
                //check if piece on right is a white pawn
                if (p->board[curr_pos_x + 2][curr_pos_y + 1]->t->t == 0 && p->board[curr_pos_x + 2][curr_pos_y + 1]->color == 0){
                    enpassant = 1;
                    
                }
            }
            if (p->board[curr_pos_x +2][curr_pos_y - 1] != NULL){
                //check if piece on left is a white pawn
                if (p->board[curr_pos_x + 2][curr_pos_y - 1]->t->t == 0 && p->board[curr_pos_x + 2][curr_pos_y - 1]->color == 0){
                   enpassant = 1;
                }
            }
        }
    }

    return enpassant;
}


int Check(PIECE *Board[8][8], int color){
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            if (Board[i][j]) {
                if (Board[i][j]->t->t == 5 && Board[i][j]->color == color){
                    return checkSquare(Board[i][j]->player->other, i, j); 
                }
            }
        }
    }
    return 2;
}

int Mate(PIECE *Board[8][8], int color) {
    PIECE *tempBoard[8][8];
    copyBoard(Board, tempBoard);

    int check;
    int newx, newy;
    int movecount;

    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            if (Board[i][j]) {
                if (Board[i][j]->color == color) {
                    movecount = Board[i][j]->counter;
                    for (int k = 0; k < movecount; k++) {
                        newx = Board[i][j]->movelist[k][0];
                        newy = Board[i][j]->movelist[k][1];
                        movePiece(Board, Board[i][j], newx, newy);
                        updatePlayer(Board[newx][newy]->player, Board);
					    updatePlayer(Board[newx][newy]->player->other, Board);
					    check = Check(Board, color);
                        copyBoard(tempBoard, Board);
                        Board[i][j]->x = i;
						Board[i][j]->y = j;
                        updatePlayer(Board[i][j]->player, Board);
					    updatePlayer(Board[i][j]->player->other, Board);
                        if (check) {
                            continue;
                        }
                        else {
                            return 0;
                        }
                    }
                }
            }
        }
    }
    return 1;

}

void PawnPromotion(PIECE *p, TYPE *typelist[6]){
    int piece_type;
    int piece_type2;
    if (!p) {
        return;
    }

    if (p->t->t == 0 && p->color == 0){
        if (p->x == 0){
            while(1){
                printf("1-Rook, 2-Knight, 3-Bishop, 4-Queen\n");
                printf("Pawn promoted to (input type number): ");
                scanf("%d", &piece_type);
                if (piece_type > 0 && piece_type < 5){
                    setPiece(p, p->board, 0, typelist[piece_type], p->x, p->y);
                    break;
                }
                else {
                    printf("Not a valid type number\n");
                }
            }
        }
    }
    if (p->t->t == 0 && p->color == 1){
        if (p->x == 7){
            while(1){
                printf("1-Rook, 2-Knight, 3-Bishop, 4-Queen\n");
                printf("Pawn promoted to (input type number): ");
                scanf("%d", &piece_type2);
                if (piece_type2 > 0 && piece_type2 < 5){
                    setPiece(p, p->board, 1, typelist[piece_type2], p->x, p->y);
                    break;
                }
                else{
                    printf("Not a valid type number\n");
                }
            }
        }
    }
}
