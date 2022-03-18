//Hayden Owens
//CSE 20311
//playlife.c
//This program will simulate Conway's Game of Life. This is the main driver program.

const int BOARDSIZE = 40;   //global var for board size that will also be used in func.c

#include <stdio.h>
#include <stdbool.h>
#include <unistd.h>
#include <stdlib.h>
#include "lifefunc.h"

int main(int argc, char *argv[])
{
    //Create two boards, one as the main board, and one for temp storage when steping forward.
    //Each board is a 42x42 2D array of booleans in which a cell that contains false is dead and
    //a cell that contains true is alive. The boards are wider than BOARDSIZE in order to simplify
    //the treatment of the edges when looping through the board. The edges will always contain
    //false (the edges will always be dead)
    bool board[BOARDSIZE+2][BOARDSIZE+2];
    bool tempboard[BOARDSIZE+2][BOARDSIZE+2];
    //initialize both boards. initBoard() fills the board with false
    initBoard(board);
    initBoard(tempboard);

    //declare variables to store inputs from user/file
    int row, col;
    char str[2];
    char command;
    
    int aniTime = 100000;   //this number will be called with usleep() to slow down the printing of the cells

    if(argc == 1)   //if no file is passed as an arguement
    {
        while(1)    //loop until the user quits
        {
            usleep(aniTime);    //wait 100,000 microseconds (0.1 seconds)
            system("clear");    //clear the terminal
            display(board); //call display on board to print the current board state
            PROMPT: //label for goto statement after invalid inputs
            printf("Command: ");    //prompt user to enteer a command
            scanf("%s", str);   //read in the first part of the command as a string

            if(strlen(str) >= 2)    //if the length of the user's command string is > 1,
            {
                while(fgetc(stdin) != '\n') {}  //clear out the rest of stdin as there might be extra inputs left
                system("clear");    //clear the terminal
                display(board); //print the board
                printf("Invalid Command: %s\n", str);   //display error message
                goto PROMPT;    //and jump back to PROMPT to allow the user to try again
            }

            command = str[0];   //once the user has entered a single char command, assign it to command

            switch(command) //switch statement based on the users command char
            {
                case 'a':   //if the user enters a
                    scanf("%d %d", &row, &col); //read in the two integers into row and col
                    if((row < 0) || (row > BOARDSIZE-1) || (col < 0) || (col > BOARDSIZE-1))    //if either row or col
                    {                                                                           //are out of bounds
                        system("clear");    //clear terminal
                        display(board); //print board
                        printf("Invalid Coordinates\n");    //display error message
                        goto PROMPT;    //and jump back to PROMPT to allow user to try again
                    }
                    addlive(board, row, col);   //if inputs are valid, add a live cell to board[row][col]
                    break;
                case 'r':   //if the user enters r
                    scanf("%d %d", &row, &col); //read in the two integers into row and col
                    if((row < 0) || (row > BOARDSIZE-1) || (col < 0) || (col > BOARDSIZE-1))    //if either row or col
                    {                                                                           //are out of bounds
                        system("clear");    //clear terminal
                        display(board); //print board
                        printf("Invalid Coordinates\n");    //display error message
                        goto PROMPT;    //and jump back to PROMPT to allow user to try again
                    }
                    kill(board, row, col);  //if inputs are valid, set board[row][col] to be dead
                    break;
                case 'n':   //if the user enters n
                    step(board, tempboard); //mutate the board by one generation
                    break;
                case 'p':   //if the user enters p
                    while(1)    //loop continuously
                    {
                        usleep(aniTime);    //wait 0.1 seconds
                        system("clear");    //clear the terminal
                        step(board, tempboard); //mutate the board
                        display(board); //print the board, and repeat until user decides to quit
                    }
                case 'q':   //if the user enters q
                    puts("Goodbye!\n"); //print Goodbye!
                    return 0;   //and exit the program
                default:    //if the user enters anything else
                    while(fgetc(stdin) != '\n') {}  //clear out stdin as there may be stray inputs
                    system("clear");    //clear terminal
                    display(board); //print the board
                    printf("Invalid Command\n");    //display error message
                    goto PROMPT;    //and jump back to PROMPT to allow user to try again
            }
        }
    }
    else if(argc == 2)  //if the user passed another argument with the executable
    {
        FILE *fp = fopen(argv[1], "r"); //attempt to connect to a file with the name the user input
        if(!fp) //if the file coult not be connected to
        {
            printf("File %s not found.\n", argv[1]);    //display error message
            return 1;   //and return
        }
        
        while(1)    //otherwise, loop continuously
        {
            fscanf(fp, "%c %d %d", &command, &row, &col);   //read in the next line of the file
                                                            //*inputs are not checked, files are assumed to be valid*
            switch(command) 
            {
                case 'a':   //if the line is an a command
                    addlive(board, row, col);   //addlive() at corresponding row and col
                    break;
                case 'r':   //if the line is an r command
                    kill(board, row, col);  //kill() at corresponding row and col
                    break;
                case 'p':   //if the line is a p command (at the end of the file)
                    while(1)    //as above, continuously mutate and print until the user quits
                    {
                        usleep(aniTime);            //NOTE: EOF is never checked for as
                        system("clear");            //it is assumed p will be at the end of any 
                        step(board, tempboard);     //input file
                        display(board);             
                    }
            }
        }
        return 0;
    }
    else    //if any other amount of arguments are passed
    {
        puts("Too many arguments"); //display error message
        return 1;   //and quit the program
    }
}
