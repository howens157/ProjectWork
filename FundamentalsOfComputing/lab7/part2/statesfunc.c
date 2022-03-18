//statesfunc.c
//Hayden Owens
//CSE 20311
//statesfunc.c contains functions related to statesmain.c
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>
#include "statesfunc.h"   //includes function prototypes and defintion for State struct

//readUser will read in the filename from the user and then call readFile on that final. It will
//return the numbner of states read in or -1 if the file could not be found
int readUser(State states[])
{
    int maxlength = 30; 
    char filename[maxlength];   //create a string of length maxlength
    printf("Please enter the filename: ");    //prompt user
    scanf("%s", filename);  //and read in their input
    return readFile(filename, states);  //call readFile and return its value
}

//readFile will connect to filename and then read the data in the file into states[]
int readFile(char filename[], State states[])
{
    FILE *fp = fopen(filename, "r");    //create a file pointer
    if(!fp) //if the file did not connect, 
    {
        return -1;  //return -1
    }

    int count = 0;  //count will store the number of states in the array
    int max = 256;
    char currline[max];
    while(1)    //will loop continuously
    {   
        fgets(currline, max, fp);    //read in the next line of the file to the
        if(feof(fp))    //if the end of the file has been reached,
            break;  //break;
        strcpy(states[count].abbrev, strtok(currline, ","));
        strcpy(states[count].name, strtok(NULL, ","));
        strcpy(states[count].cap, strtok(NULL, ","));
        states[count].year = atoi(strtok(NULL, "\n"));
        count++;    //increment count
    }
    return count;
}

//compare() will convert two strings to lowercase forms and then compare those strings using strcmp() in order to
//have a case-insensitive string comparison
int compare(char str1[], char str2[])
{
    int maxcomplength = 30; //longest length strings that can be compared
    char lowstr1[maxcomplength];    //vars for lowercase version
    char lowstr2[maxcomplength];
    int i;
    strcpy(lowstr1, str1);  //copy str1/2 to lowstr1/2
    strcpy(lowstr2, str2);
    for(i = 0; i < strlen(lowstr1); i++)    //convert both strings to completely lowercase
        lowstr1[i] = tolower(lowstr1[i]);
    for(i = 0; i < strlen(lowstr2); i++)
        lowstr2[i] = tolower(lowstr2[i]);

    return strcmp(lowstr1, lowstr2);    //call strcmp() on the lowercase versions and return that value (0 if equal)
}

//prompt() will display all options for the user, read their choice, and return it
int prompt()
{
    puts("\n1: Display info for all states");
    puts("2: Display info for a certain state");
    puts("3: Display the capital of a certain state");
    puts("4: Display all the states that joined the union in a given year");
    puts("5: Display all states that start with a certain letter");
    puts("0: Quit the program");
    printf("Please enter a command: ");
    int command;
    scanf("%d", &command);
    while(fgetc(stdin) != '\n') {}
    printf("\n");
    return command;
}

//display() will print the info for every state in the array
void display(State states[], int numStates)
{
    int i;
    for(i = 0; i < numStates; i++)  //loop through states[]
    {   //and print all of its info
        printf("%s: %s, %s, %d\n", states[i].abbrev, states[i].name, states[i].cap, states[i].year);
    }
}

//abbrevinfo() will prompt the user for a state abbreviation and display the info for that state
void abbrevinfo(State states[], int numStates)
{
    printf("Please enter the abbreviation for the state: "); //prompt user for abbrev and store it
    char userabbrev[3];
    fgets(userabbrev, 3, stdin);
    while(fgetc(stdin) != '\n') {}  //clear out stdin in case of any stray inputs
    if(userabbrev[2] == '\n')   //replace \n with null character
        userabbrev[2] = '\0';
    int i;
    bool found = false; //bool to store whether any states were found
    for(i = 0; i < numStates; i++)  //loop through states[]
    {
        if(compare(states[i].abbrev, userabbrev) == 0)  //check if the current state's abbrev matches the input
        {
            printf("%s, %s, %d\n", states[i].name, states[i].cap, states[i].year);  //if so, display info
            found = true;   //and set found to true
        }
    }
    if(!found)  //if no states were found
        printf("There were no states with the abbreviation %s found.\n", userabbrev);
}

//putcap() will prompt the user for a state and print the capital of that state
void putcap(State states[], int numStates)
{
    printf("Please enter the abbreviation or name of the state: "); //prompt user for state/abbrev and store it
    char input[30];
    fgets(input, 30, stdin);
    char * pch = strchr(input, '\n');
    //if a \n was read in, replace it with a null character
    if(pch != NULL)
        *pch = '\0';
    else    //otherwise, clear out stdin
        while(fgetc(stdin) != '\n') {}
    int i;
    bool found = false; //bool to store whether the state was found
    for(i = 0; i < numStates; i++)  //loop through states[]
    {   
        //if the abbrev or name matches the input
        if((compare(states[i].abbrev, input) == 0) || (compare(states[i].name, input) == 0))
        {
            printf("The capital of %s is %s.\n", states[i].name, states[i].cap);    //print the capital
            found = true;   //set found to true
        }
    }
    if(!found)  //if no state was found
        printf("There were no states with the abbreviation or name %s found.\n", input);
}

//joinedyear() will prompt the user for a year and print all states that joined the union that year
void joinedyear(State states[], int numStates)
{
    printf("Please enter a year: ");    //prompt user and store input
    char input[30];
    fgets(input, 30, stdin);
    if(strchr(input, '\n') == NULL) //if the input doesn't contain a \n
        while(fgetc(stdin) != '\n') {}  //clear out stdin
    int year = atoi(input); //convert the input to an int (returns 0 if input is not numeric)
    if(year == 0)   //if input wasn't numeric
    {
        puts("Invalid input");  //print error message and return
        return;
    }
    int i;
    bool found = false; //bool to store if any states were found
    for(i = 0; i < numStates; i++)  //loop through states[]
    {
        if(states[i].year == year)  //check if the year matches the input
        {
            printf("%s joined the union in %d.\n", states[i].name, states[i].year); //if so, print the state
            found = true;   //and set found to true
        }
    }
    if(!found)  //if no states were found
        printf("No states joined the union in %d\n", year);
}

//listletter() will prompt the user for a letter and print all states that start with that letter
void listletter(State states[], int numStates)
{
    printf("Please enter a letter: ");  //prompt and store input
    char str[30];
    scanf("%s", str);
    char input = toupper(str[0]);   //isolate first char of input and make it uppercase
    if(strchr(str, '\n') == NULL)   //if the input doesn't contain a \n
        while(fgetc(stdin) != '\n') {}  //clear out stdin
    if(input < 'A' || input > 'Z' || strlen(str) > 1)   //if the input char is not between A and Z or the user input more
    {                                                   //than one character
        puts("Invalid input");  //print error and return
        return;
    }
    bool found = false; //bool to store whether or not any states were found
    int i;
    for(i = 0; i < numStates; i++)  //loop through states[]
    {
        if(states[i].name[0] == input)  //if the state starts with input
        {
            printf("%s\n", states[i].name); //print the state
            found = true;   //and set found to true
        }
    }
    if(!found)  //if no states were found
        printf("No states begin with %c\n", input);
}
