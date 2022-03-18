//crossfunc.c
//Hayden Owens
//CSE 20311
//crossfunc.c contains functions related to crossmain.c
#include "crossfunc.h"   //includes function prototypes and defintion for Word struct

//initboard will fill the whole board with null characters
void initboard(char board[][BOARDSIZE+2])
{
    int i, j;
    for(i = 0; i < BOARDSIZE+2; i++)    //nested for loop to loop through full board
    {
        for(j = 0; j < BOARDSIZE+2; j++)
        {
            board[i][j] = '\0'; //set every character in the board to a null character
        }
    }
}

//isalphastr returns true if every char in a string is alphabetic, false otherwise
bool isalphastr(char str[], int len)
{
    int i;
    bool alphabetic = true;
    for(i = 0; i < len; i++)    
    {
        if(!isalpha(str[i]))    //if any char in the string is not alphabetic
            alphabetic = false; //set the bool to false
    }
    return alphabetic;
}

//readUser will read a list of words in from the user and return the number of words read in
int readUser(Word words[])
{
    //puts("readUser");
    int numWords = 0;
    char input[WORDLENGTH];
    while(1)
    {
        PROMPT:
        printf("Please enter a word or enter a period to end: ");   //prompt user
        fgets(input, WORDLENGTH, stdin);    //get input
        char *pch = strchr(input, '\n');    //check if a \n was read in
        if(pch != NULL) //if so, replace it will a \0
            *pch = '\0';
        else    //otherwise, the word was too long
        {
            while(fgetc(stdin) != '\n') {}  //so clear out stdin
            puts("Entered word is too long, please try again.");    //display error message
            goto PROMPT;    //and prompt again
        }
        if(strcmp(input, ".") == 0) //if the input is a '.', the user is done, so break
            break;
        if(!isalphastr(input, strlen(input)))   //if the input contains non-alphabetic characters,
        {
            puts("Entered word contains non-alphabetic characters, please try again."); //display error message
            goto PROMPT;    //and prompt again
        }
        if(strlen(input) < 2)   //if the input is less than 2 characters
        {
            puts("Entered word is too short, please try again.");   //display error message
            goto PROMPT;    //and prompt again
        }
        //define all values in the struct for the current word
        strcpy(words[numWords].str, input);
        words[numWords].placed = false;
        words[numWords].x = -1;
        words[numWords].y = -1;
        words[numWords].horiz = true;
        numWords++; //increment numWords
        if(numWords > MAXWORDS - 1) //if the user has entered the max number of words
        {
            puts("Max number of words entered.");   //inform the user and break
            break;
        }
    }
    return numWords;
}

//readFile will connect to filename and then read the data in the file into words[]
int readFile(char filename[], Word words[])
{
    //puts("readFile");
    FILE *fp = fopen(filename, "r");    //create a file pointer
    if(!fp) //if the file did not connect, 
    {
        return -1;  //return -1
    }

    int numWords = 0;
    char input[WORDLENGTH];
    while(1)
    {
        fgets(input, WORDLENGTH, fp);   //get the next line of the file
        char *pch = strchr(input, '\n');    //replace the \n with a \0
        if(pch != NULL)
            *pch = '\0'; 
        if((strcmp(input, ".") == 0) || (feof(fp))) //keep looping until a '.' is read in or feof is reached
            break;
        //define initial values for each value in the struct
        strcpy(words[numWords].str, input);
        words[numWords].placed = false;
        words[numWords].x = -1;
        words[numWords].y = -1;
        words[numWords].horiz = true;
        numWords++; //increment numWords
    }
    return numWords;
}

//strtoupper converts every character in a str to the uppercase version
void strtoupper(char str[])
{
    //puts("strtoupper");
    int i;
    for(i = 0; i < strlen(str); i++)
    {
        str[i] = toupper(str[i]);
    }
}

//wordstoupper calls strtoupper on every Word in the array of Words
void wordstoupper(Word words[], int numWords)
{
    //puts("wordstoupper");
    int i;
    for(i = 0; i < numWords; i++)
        strtoupper(words[i].str);
}

//sort will sort the words[] by  length from longest to shortest
void sort(Word words[], int numWords)
{
    //puts("sort");
    bool sorted = true;
    char temp[WORDLENGTH];  //temp for storage when swapping
    int i;
    while(1)
    {
        sorted = true;
        for(i = 0; i < numWords-1; i++) //loop through every Word in words[] except the last
        {
            if(strlen(words[i].str) < strlen(words[i+1].str))   //if the current word is shorter than the next,
            {
                strcpy(temp, words[i+1].str);           //swap the two words
                strcpy(words[i+1].str, words[i].str);
                strcpy(words[i].str, temp);
                sorted = false;                         //and set sorted to false so that the loop will run again
            }
        }
        if(sorted)  //once the loop completes without setting sorted back to false, break
            break;
    }
}

/*void printWords(FILE *ofp, Word words[], int numWords)
{
    //puts("printWords");
    int i;
    fprintf(ofp, "--Word List--\n");
    for(i = 0; i < numWords; i++)
    {
        fprintf(ofp, "%s\n", words[i].str);
    }   
}*/

//place will inset a word into the puzzle starting at a given coordinate and with a given orientation. The function takes the array of words
//and the index of the word to be placed
void place(char board[][BOARDSIZE+2], Word words[], int x, int y, bool horiz, int curr)
{
    //puts("place");
    int i;
    if(!horiz)  //if the word should be placed vertically (the y value should be incremented)
    {
        for(i = 0; i < strlen(words[curr].str); i++)    //loop through each character in the word
        {
            board[i+y+1][x+1] = words[curr].str[i]; //and insert it in the proper location
        }
    }
    else    //if the word should be placed horizontally (the x value should be incremented)
    {
        for(i = 0; i < strlen(words[curr].str); i++)    //loop through each character in the word
        {
            board[y+1][i+x+1] = words[curr].str[i]; //and insert it in the proper location
        }
    }
    //update the other values of the struct to reflect the word's placement
    words[curr].placed = true;
    words[curr].x = x;
    words[curr].y = y;
    words[curr].horiz = horiz;
}

//place2nd places the 2nd word in the puzzle. It has its own function as it uses a simpler method than subsequent placements
bool place2nd(char board[][BOARDSIZE+2], Word words[], int curr)
{
    //puts("place2nd");
    int i, j;
    for(i = 0; i < BOARDSIZE; i++)  //loop through the full middle row
    {      
        if(board[BOARDSIZE/2+1][i+1] != '\0')   //if the current character is not null
        {
            for(j = 0; j < strlen(words[curr].str); j++)    //loop through each character in the word
            {
                if(board[BOARDSIZE/2+1][i+1] == words[curr].str[j]) //if the characters are a match
                {
                    if((j <= BOARDSIZE/2-1) && (strlen(words[curr].str)-(j+1) <= BOARDSIZE - BOARDSIZE/2-1))    //check that the word will fit
                    {
                        place(board, words, i, BOARDSIZE/2-j, false, curr); //and place it in the proper location
                        return true;    //return true if the word was able to be placed
                    }
                }
            }
        }
    }
    return false;   //return false otherwise
}

//checkplace checks if a given placement is valid and will not overwrite any already placed words
bool checkplace(char board[][BOARDSIZE+2], Word word, int x, int y, bool horiz, int intersect)
{
    //puts("checkplace");
    int i;
    bool safe = true;
    if(!horiz)  //if the word is to be placed horizontally
    {
        for(i = 0; i < strlen(word.str); i++)   //loop through the word
        {
            //checks that it does not overwrite any characters unless it is a proper interection, and that there are no letters surrounding the word
            //as one word should not be placed directly adjacent to any characters of another word
            if(((board[i+y+1][x+1] != '\0') && (board[i+y+1][x+1] != word.str[i])) || ((board[i+y+1][x] != '\0') && (i != intersect)) || ((board[i+y+1][x+2] != '\0') && (i != intersect)) || ((i == 0) && (board[i+y][x+1] != '\0')) || ((i == strlen(word.str)-1) && (board[i+y+2][x+1])))
                safe = false;
        }
    }
    else    //if the word is to be place vertically, do the same as above but in the other orientation
    {
        for(i = 0; i < strlen(word.str); i++)
        {
            if(((board[y+1][i+x+1] != '\0') && (board[y+1][i+x+1] != word.str[i])) || ((board[y][i+x+1] != '\0') && (i != intersect)) || ((board[y+2][i+x+1] != '\0') && (i != intersect)) || ((i == 0) && (board[y+1][i+x] != '\0')) || ((i == strlen(word.str)-1) && (board[y+1][i+x+2])))
                safe = false;
        }
    }
    return safe;    //return whether or not it is a safe placement
}

//placerest will loop through the rest of the Words in words[] and attempt to place them all
void placerest(char board[][BOARDSIZE+2], Word words[], int start, int numWords)
{
    //puts("placerest");
    int w, i, j, c;
    bool horiz = false;
    for(w = start; w < numWords; w++)   //loop through every remaining word
    {        
        for(i = 0; i < BOARDSIZE; i++)  //loop through the rows of board
        {            
            for(j = 0; j < BOARDSIZE; j++)  //loop through the cols of board
            {                
                if(board[i+1][j+1] != '\0') //if the current location in board is not a null character
                {
                    if((board[i][j+1] == '\0') && (board[i+2][j+1] == '\0'))    //and the chars above and below are null 
                    {                                                           //meaning the char is part of a horizontally placed word
                        horiz = false;  //the word should be placed vertically
                        for(c = 0; c < strlen(words[w].str); c++)   //loop through the chars in the current word
                        {                            
                            if(board[i+1][j+1] == words[w].str[c])  //if a character in the current word matches the current character on the board
                            {
                                if((c <= i) && (strlen(words[w].str)-(c+1) <= BOARDSIZE - (i+1)))   //check that there is room for the word
                                {
                                    if(checkplace(board, words[w], j, i-c, horiz, c))   //checkplace() to check other conditions
                                    {
                                        place(board, words, j, i-c, horiz, w);  //if conditions are met, place the word
                                        goto NEXTWORD;  //and jump to NEXTWORD in order to break  out of all the loops
                                    }
                                }
                            }
                        }
                    }
                    if((board[i+1][j] == '\0') && (board[i+1][j+2] == '\0'))    //if the chars to the left and the right are null
                    {                                                           //meaning the char is part of a vertically placed word
                        horiz = true;   //the word should be place horizontally
                        for(c = 0; c < strlen(words[w].str); c++)   //same as in vertical case but in opposite orientation
                        {                            
                            if(board[i+1][j+1] == words[w].str[c])
                            {
                                if((c <= j) && (strlen(words[w].str)-(c+1) <= BOARDSIZE - (j+1)))
                                {
                                    if(checkplace(board, words[w], j-c, i, horiz, c))
                                    {
                                        place(board, words, j-c, i, horiz, w);
                                        goto NEXTWORD;
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }
        printf("Could not place %s on first pass\n", words[w].str); //if a word could not be placed on the first pass, print so
        NEXTWORD:;
    }
}

//tryagain will do the same thing as placerest(), but it loops through all of words[] and only checks for words that have not already been placed
//it returns whether or not any additional words were placed on that pass through the array
bool tryagain(char board[][BOARDSIZE+2], Word words[], int numWords)
{
    bool wordsplaced = false;
    int w, i, j, c;
    bool horiz = false;
    for(w = 0; w < numWords; w++)   //for every Word in words[]
    {
        if(!words[w].placed)    //if the word has not been placed, do the same as in placerest()
        {        
            for(i = 0; i < BOARDSIZE; i++)
            {            
                for(j = 0; j < BOARDSIZE; j++)
                {                
                    if(board[i+1][j+1] != '\0')
                    {
                        if((board[i][j+1] == '\0') && (board[i+2][j+1] == '\0'))
                        {
                            horiz = false;
                            for(c = 0; c < strlen(words[w].str); c++)
                            {                            if(board[i+1][j+1] == words[w].str[c])
                                {
                                    if((c <= i) && (strlen(words[w].str)-(c+1) <= BOARDSIZE - (i+1)))
                                    {
                                        if(checkplace(board, words[w], j, i-c, horiz, c))
                                        {
                                            place(board, words, j, i-c, horiz, w);
                                            wordsplaced = true;
                                            goto NEXTWORD2;
                                        }
                                    }
                                }
                            }
                        }
                        if((board[i+1][j] == '\0') && (board[i+1][j+2] == '\0'))
                        {
                            horiz = true;
                            for(c = 0; c < strlen(words[w].str); c++)
                            {                            if(board[i+1][j+1] == words[w].str[c])
                                {
                                    if((c <= j) && (strlen(words[w].str)-(c+1) <= BOARDSIZE - (j+1)))
                                    {
                                        if(checkplace(board, words[w], j-c, i, horiz, c))
                                        {
                                            place(board, words, j-c, i, horiz, w);
                                            wordsplaced = true;
                                            goto NEXTWORD2;
                                        }
                                    }
                                }
                            }
                        }
                    }
                }
            }
            NEXTWORD2:;
        }
    }
    return wordsplaced; //return whether or not any new words were placed on this pass
}

//printBoards will print the solution and puzzle boards to the user or output file
void printBoards(FILE *ofp, char board[][BOARDSIZE+2])
{
    //puts("printBoards");
    int irow, jcol;
    //Solution Board
    fprintf(ofp, "\nSolution:\n");  
    for(irow = 0; irow < BOARDSIZE+2; irow++)   //nested loop loops through full board
    {
        for(jcol = 0; jcol < BOARDSIZE+2; jcol++)
        {
            if((irow == 0) ||  (irow == BOARDSIZE+1))   //if on the top or bottom edge of the board,
                fprintf(ofp, "- "); //print the border
            else if((jcol == 0) || (jcol == BOARDSIZE+1))   //if on the left or right edge
                fprintf(ofp, "|");  //print the border
            else if(board[irow][jcol] == '\0')  //otherwise, if the current spot does not contain a letter
                fprintf(ofp, ". "); //print a .
            else    //or if it does, 
                fprintf(ofp, "%c ", board[irow][jcol]); //print the letter
            if(jcol == BOARDSIZE+1) //if on the right edge,
                fprintf(ofp, "\n"); //print new line
        }
    }
    
    //Puzzle Board
    fprintf(ofp, "\nCrossword Puzzle:\n");
    for(irow = 0; irow < BOARDSIZE+2; irow++)
    {
        for(jcol = 0; jcol < BOARDSIZE+2; jcol++)
        {
            if((irow == 0) ||  (irow == BOARDSIZE+1))
                fprintf(ofp, "- ");
            else if((jcol == 0) || (jcol == BOARDSIZE+1))
                fprintf(ofp, "|");
            else if(board[irow][jcol] == '\0')  //if the current spot does not contain a letter
                fprintf(ofp, "# "); //print a #
            else    //or if it does
                fprintf(ofp, "  "); //print a space
            if(jcol == BOARDSIZE+1)
                fprintf(ofp, "\n");
        }
    }
}

//printClues will print the start location, direction, and shuffled version of any words that were placed and will also print 
//what words could not be placed
void printClues(FILE *ofp, Word words[], int numWords)
{
    fprintf(ofp, "\nClues:\n");
    fprintf(ofp, " Location | Direction | Anagram\n");  //headers
    fprintf(ofp, "------------------------------\n");
    int i;
    char temp[15];
    for(i = 0; i < numWords; i++)   //for all words
    {
        if(words[i].placed) //if the word was placed
        {
            strcpy(temp, words[i].str); //create shuffled version
            strfry(temp);               //as a clue
            fprintf(ofp, "%5d, %2d |", words[i].x, words[i].y); //print the start coordinates
            if(words[i].horiz)  //print whether it is placed horizontally,
                fprintf(ofp, "    Across | ");
            else    //or vertically
                fprintf(ofp, "      Down | ");
            fprintf(ofp, "%s\n", temp); //and print the clue
        }
    }

    fprintf(ofp, "\nThe following words could not be placed:\n");
    for(i = 0; i < numWords; i++)   //for all words
    {
        if(!words[i].placed)    //if it was not placed
            fprintf(ofp, "%s\n", words[i].str); //print it
    }
}
