//statesfunc.h
//Hayden Owens
//CSE 20311
//crossfunc.h contains function prototypes and the defintion for the struct Word
#include <stdio.h>
#include <string.h>
#include <stdbool.h>

//define sizes
#define WORDLENGTH 15
#define BOARDSIZE 15
#define MAXWORDS 20

typedef struct {    //define a struct Word that holds one string, two bools, and two ints
    char str[WORDLENGTH];
    bool placed;    //whether or not the word has been placed in the puzzle
    bool horiz; //true represents the word being placed horizontally, false if it was placed vertically
    int x;  //two ints will hold the coordinate where the word starts in the puzzle
    int y;
} Word;

//function prototypes
void initboard(char board[][BOARDSIZE+2]);
int readUser(Word words[]);
int readFile(char filename[], Word words[]);
void strtoupper(char str[]);
void wordstoupper(Word words[], int numWords);
void sort(Word words[], int numWords);
//void printWords(FILE *ofp, Word words[], int numWords);
void place(char board[][BOARDSIZE+2], Word words[], int x, int y, bool horiz, int curr);
bool place2nd(char board[][BOARDSIZE+2], Word words[], int curr);
bool checkplace(char board[][BOARDSIZE+2], Word word, int x, int y, bool horiz, int intersect);
void placerest(char board[][BOARDSIZE+2], Word words[], int start, int numWords);
void printBoards(FILE *ofp, char board[][BOARDSIZE+2]);
void printClues(FILE *ofp, Word words[], int numWords);
