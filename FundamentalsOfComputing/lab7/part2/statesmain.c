//statesmain.c
//Hayden Owens
//CSE 20311
//statesmain.c will read in an array of states from a csv file and allow the user to display certain info about states

#include <stdio.h>
#include "statesfunc.h" //includes definition for State struct

int main(int argc, char *argv[])
{
    const int MAXSIZE = 50; //max size of states in the array
    State states[MAXSIZE];  //create an array of States of maxsize
    
    int numStates = 0;  //initialize and define var for the number of states

    if(argc == 1)   //if the user did not enter the file as a command line argument
    {
        numStates = readUser(states);   //read in the filename from the user
    }
    else if(argc == 2)  //if the user did enter the text file as a command line argument
    {
        numStates = readFile(argv[1], states);  //go straight to reading in the data from the file
    }
    else    //otherwise print an error message and quit
    {
        puts("Too many arguments");
        return 1;
    }
    if(numStates == -1) //if readUser()/readFile(0) returned -1, print "File not found" and quit
    {
        puts("File not found");
        return 1;
    }
    int command;    //declare a var to store the user's input command
    while(1)    //loop continously
    {
        command = prompt(); //prompt the user and get their command
        switch(command) //switch based on command that will call the appropriate function
        {
            case 1: //display the info of all the states
                display(states, numStates);
                break;
            case 2: //prompt user for an abbreviation and display the info of that state
                abbrevinfo(states, numStates);
                break;
            case 3: //prompt the user for a state and display its capital
                putcap(states, numStates);
                break;
            case 4: //prompt the user for a year and print all states that joined the union in that  year
                joinedyear(states, numStates);
                break;
            case 5: //prompt user for a letter and print all states that start with that letter
                listletter(states, numStates);
                break;
            case 0: //quit the program
                puts("Goodbye!");
                return 0;
            default:
                puts("Command not recognized");
        }
    }

    return 0;
}
