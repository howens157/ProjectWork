//ndfootball.c
//Hayden Owens
//CSE 20311
#include <stdio.h>
#include "nd_data.h"//two arrays, int wins[], int losses[] that store the wins
                    //and losses of ND Football (wins[0] = wins in 1900) 
int arrSize;    //Global variable for size of the arrays
//function prototypes
int prompt();
void record();
void minWins();
void minLosses();
void losingRecs();
void winningRecs();
void losingStreaks();
void winningStreaks();

int main()
{
    arrSize = sizeof(wins)/sizeof(wins[0]); //Calculate the size of the arrays
    
    int userChoice = prompt();  //prompt user
    while(1)    //continue to run unti user breaks out
    {
        switch(userChoice)  //call appropriate function according to userChoice
        {
            case 1:
                record();
                break;
            case 2:
                minWins();
                break;
            case 3:
                minLosses();
                break;
            case 4:
                losingRecs();
                break;
            case 5:
                winningRecs();
                break;
            case 6:
                losingStreaks();
                break;
            case 7:
                winningStreaks();
                break;
            case 0:                     //If user chooses 0
                printf("Goodbye!\n");   //return and end
                return 0;               //program
        }
        printf("\n");
        userChoice = prompt();
    }
}

int prompt()    //prompts the user and returns their choice
{
    int userChoice;
    printf("1: Display the record for a given year.\n");
    printf("2: Display years with at least \"n\" losses.\n");
    printf("3: Display years with at least \"n\" wins.\n");
    printf("4: Display all years with a losing record.\n");
    printf("5: Display all years with a winning record.\n");
    printf("6: Display all streaks of losing records of at least \"n\" years.\n");
    printf("7: Display all streaks of winning records of at least \"n\" years.\n");
    printf("0: Exit\n");
    printf("Please enter your choice: ");
    scanf("%d", &userChoice);
    return userChoice;
}

void record()   //outputs the record of a given year
{
    int year;
    printf("Enter the year: ");
    scanf("%d", &year);
    printf("Wins: %d, Losses: %d\n", wins[year-1900], losses[year-1900]);
    return;
}

void minWins()  //outputs all years with a minimum number of wins
{
    int minWin, i;
    printf("Enter number of wins: ");   //prompts user for the min number of wins to look for
    scanf("%d", &minWin);
    printf("Years with at least %d wins: ", minWin);
    for(i = 0; i < arrSize; i++)    //loops through the whole array
    {                               //and if the number of wins is greater
        if(wins[i] >= minWin)       //than or equal to minWin,
            printf("%d ", i + 1900);//print the year
    }
    printf("\n");
    return;

}

void minLosses()    //outputs all years with a minimum number of losses
{
    int minLoss, i;
    printf("Enter number of losses: "); //prompts user for the min number of losses to look for
    scanf("%d", &minLoss);
    printf("Years with at least %d losses: ", minLoss);
    for(i = 0; i < arrSize; i++)    //loops through the whole array
    {                               //and if the number of losses is
        if(losses[i] >= minLoss)    //greater than or equal to minLoss,
            printf("%d ", i + 1900);//print the year.
    }
    printf("\n");
    return;
}

void losingRecs()   //outputs all years with a losing record
{
    int i;
    printf("Years with a losing record: "); 
    for(i = 0; i < arrSize; i++)    //loops through whole array
    {                               //and if there are more 
        if(wins[i] < losses[i])     //losses than wins
            printf("%d ", i + 1900);//print the year
    }
    printf("\n");
    return;
}

void winningRecs()  //outputs all years with a winning record
{
    int i;
    printf("Years with a winning record: ");
    for(i = 0; i < arrSize; i++)    //loops through the whole array
    {                               //and if there are more
        if(wins[i] > losses[i])     //wins than losses
            printf("%d ", i + 1900);//print the year
    }
    printf("\n");
    return;
}

void losingStreaks()    //outputs all losing streaks of a specified length or greater
{
    int streak_length, streak_count, i;
    printf("Please enter the length of the streak to look for: ");  //prompt user for length of streak
    scanf("%d", &streak_length);
    streak_count = 0;
    for(i = 0; i < arrSize; i++)    //loop through whole array
    {
        if(wins[i] < losses[i])     //if it is a losing season,
        {
            streak_count++;         //add one to the streak count
            if((streak_count >= streak_length) && (wins[i+1] >= losses[i+1]))   //if the streak is longer than the specified length
                                                                                //and it is the end of the streak, print the streak
                printf("There was a streak of %d losing seasons from %d to %d.\n", streak_count, i + 1901 - streak_count, i + 1900);
        }
        else    //if it is a winning season
            streak_count = 0;   //set the streak to 0
    }
    return;
}

void winningStreaks()   //outputs all winning streaks of a specified length or greater
{
    int streak_length, streak_count, i;
    printf("Please enter the length of the streak to look for: ");  //prompts user for length of streak
    scanf("%d", &streak_length);
    streak_count = 0;
    for(i = 0; i < arrSize; i++)    //loop through whole array
    {
        if(wins[i] > losses[i])     //if it is a winning season,
        {
            streak_count++;         //add one to the streak count
            if((streak_count >= streak_length) && (wins[i+1] <= losses[i+1]))   //if the streak is longer than the specified length   
/********/                                                                      //and it is the end of the streak, print the streak
                printf("There was a streak of %d winning seasons from %d to %d.\n", streak_count, i + 1901 - streak_count, i + 1900);
        }
        else    //if it is a losing season
            streak_count = 0;   //set the streak to 0
    }
    return;
}
