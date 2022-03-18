//crossmain.c
//Hayden Owens
//CSE 20311
//crossmain.c will read in a list of words and generate a basic crossword puzzle from
//them and ouput both a solution and a puzzle as well as a list of clues and any words
//that could not be placed
#include "crossfunc.h"  //includes functions and Word struct

int main(int argc, char *argv[])
{
    Word words[MAXWORDS];   //create an array of Word structs
    int numWords = 0; 
    char board[BOARDSIZE+2][BOARDSIZE+2];   //create a board with extra space on edges
    initboard(board);   //initialize the board with null characters
    if(argc == 1)  
    {
        numWords = readUser(words); //read the words from the user
    }
    else if(argc > 1)  
    {
        numWords = readFile(argv[1], words);  //read the words from a file
    }
    else if(argc > 3)   //too many arguments
    {
        puts("Too many arguments");
        return 1;
    }
    if(numWords == -1) //readFile returns -1 if it could not connect
    {
        puts("Input file not found"); //display error and quit
        return 1;
    }
    wordstoupper(words, numWords);  //convert all words to uppercase
    sort(words, numWords);  //sort the words by descending length
    //place the first word in the middle of the board
    place(board, words, (BOARDSIZE-strlen(words[0].str))/2, BOARDSIZE/2, true, 0);
    bool placed2nd = false; //represents whether the 2nd word has been placed in the puzzle
    int i;
    for(i = 1; i < numWords; i++)   //loops in order to try the next word if the 2nd word does not 
                                    //intersect with the first word
    {
        if(place2nd(board, words, i))   //if the word is placed, break
            break;
    }
    i++;
    placerest(board, words, i, numWords);   //place the rest of the words starting from whatever word was placed by place2nd()

    //keep trying to place words until no more can be placed, if any words were placed
    //on one loop, it will loop again. Will not stop until tryagain is called again,
    //but no more words can be placed
    while(tryagain(board, words, numWords)) {}

    if(argc < 3)    //if the user did not enter an output file
    {
        //print Boards and clues to the user
        printBoards(stdout, board);
        printClues(stdout, words, numWords);
    }
    else if(argc == 3)  //if the user did enter an output file
    {
        FILE *ofp = fopen(argv[2], "w");    //connect to the file in write mode
        //and print Boards and clues to the file
        printBoards(ofp, board);
        printClues(ofp, words, numWords);
    }
    return 0;
}
