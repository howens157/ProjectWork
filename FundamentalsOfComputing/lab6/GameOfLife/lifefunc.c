//Hayden Owens
//CSE 20311
//lifefunc.c

//defines functions for playlife.c

extern int BOARDSIZE;   //BOARDSIZE will be used from playlife.c

#include <stdbool.h>
#include <stdio.h>
#include "lifefunc.h"

//initBoard() will set every cell in the passed board to false (dead)
void initBoard(bool board[][BOARDSIZE+2])
{
    int irow, jcol;
    for(irow = 0; irow < BOARDSIZE+2; irow++)   //loop through rows
    {
        for(jcol = 0; jcol < BOARDSIZE+2; jcol++)   //loop through cols
        {
            board[irow][jcol] = false;  //set every cell to be dead
        }   
    }
}

//display() will print the passed board to the terminal
void display(bool board[][BOARDSIZE+2])
{
    int irow, jcol;
    for(irow = 0; irow < BOARDSIZE+2; irow++)   //loop through rows
    {
        for(jcol = 0; jcol < BOARDSIZE+2; jcol++)   //loop through cols
        {
            if((irow == 0) || (irow == BOARDSIZE+1) || (jcol == 0) || (jcol == BOARDSIZE+1))    //print the border of the
            {                                                                                   //board by printng a # if
                printf("#");                                                                    //if the current loop
                if(jcol == BOARDSIZE+1) //if the current loop is the end of a row               //is an edge
                   printf("\n");    //go to a new line (row)
            }
            else    //otherwise, if the current loop is not an edge,
            {
                if(board[irow][jcol])   //if the current loop corresponds with a true (live) cell
                    printf("X");    //print an X
                else    //if it is dead
                    printf(" ");    //print a space
            }
        }   
    }
}

//addlive() will set the cell at the passed coordinates to be true (alive)
void addlive(bool board[][BOARDSIZE+2], int row, int col)
{
    board[row+1][col+1] = true;
}

//kill() will set the cell at the passed coordinates to be false (dead)
void kill(bool board[][BOARDSIZE+2], int row, int col)
{
    board[row+1][col+1] = false;
}

//step() will evaluate each cell in the board to determine if it should be alive or dead in the next generation
//according to the rules of Conway's Game of Life. tempboard will be used to store the state of the next generation
//until the entire board has been looped through
void step(bool board[][BOARDSIZE+2], bool tempboard[][BOARDSIZE+2])
{
    int irow, jcol;
    int countlive = 0;  //countlive will be used to store the number of live neighbors a cell has
    int k, l;
    //primary nested loop, loops through whole board aside from edges
    for(irow = 1; irow < BOARDSIZE+1; irow++)
    {
        for(jcol = 1; jcol < BOARDSIZE+1; jcol++)
        {
            if(board[irow][jcol])   //if the current cell of interest is true (alive)
            {
                countlive = 0;  //reset countlive
                //secondary nested loop, loops through immediate neighbors of current cell of interest
                for(k = irow-1; k <= irow+1; k++)
                {
                    for(l = jcol-1; l <= jcol +1; l++)
                    {
                        if(board[k][l]) //if the current neighbor is alive
                            countlive++;    //increment countlive
                    }
                }
                countlive--;    //decrement countlive as the current cell of interest would have been counted
                                //as alive in the secondary loop
                if((countlive < 2) || (countlive > 3))  //if the live cell as less than 2 or more than 3 neighbors
                    tempboard[irow][jcol] = false;  //it dies in the next generation
                else    //otherwise, if it has 1 or 2 life neighbors
                    tempboard[irow][jcol] = true;   //it stays alive in the next generation
            }
            else if(!board[irow][jcol]) //else if the current cell of interest is false (dead)
            {
                countlive = 0;  //rest countlive
                //secondary nested loop, loops through immediate neighbors of current cell of interest
                for(k = irow-1; k <= irow+1; k++)
                {
                    for(l = jcol-1; l <= jcol +1; l++)
                    {
                        if(board[k][l]) //if the current neighbor is alive
                            countlive++;    //increment countlive
                    }
                }
                if(countlive == 3)  //if the dead cell has 3 live neighbors,
                    tempboard[irow][jcol] = true;   //it comes to live in the next generation
                else    //otherwise,
                    tempboard[irow][jcol] = false;  //the dead cell stays dead in the next generation
            }
        }   
    }
    
    //nested loop will loop through all of board
    for(irow = 0; irow < BOARDSIZE+2; irow++)
    {
        for(jcol = 0; jcol < BOARDSIZE+2; jcol++)
        {
            board[irow][jcol] = tempboard[irow][jcol];  //and copy the values from tempboard to board
        }   
    }

    initBoard(tempboard);   //reinitialize tempboard to be all false for the next time step() is called
}
