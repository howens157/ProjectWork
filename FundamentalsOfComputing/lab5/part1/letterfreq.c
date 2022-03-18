//letterfreq.c
//Hayden Owens
//CSE 20311
//
//Find the frequency of occurrences of the letters of the alphabet in 
//a text file

#include <stdio.h>
#include <ctype.h>

void init_freq (int[], int);
int find_freqs (char[], int[], int[]);
void results (char[], int[], int, int[]);

int main()
{
    char filename[30];  //filename input by user
    const int alphasize = 26;   //const var to store alphabet size
    int freqs[alphasize];   //create array to store the frequency of each letter of the alphabet
    int numChars[2] = {0, 0};
    
    printf("Please enter the file name: "); //prompt the user for the filename
    scanf("%s", filename);  //read input from user

    init_freq(freqs, alphasize);
    if(find_freqs(filename, freqs, numChars))
        return 1;
    results(filename, freqs, alphasize, numChars);

    return 0;
}

//init_freq() initializes every element of freqs[] to 0
void init_freq(int freqs[], int textsize)
{
    int i;
    for(i = 0; i < textsize; i++)
    {
        freqs[i] = 0;
    }
}

//find_freqs() counts the # of occurrences of each letter of the alphabet in the text file and the # of letters in the file
int find_freqs(char filename[], int freqs[], int numChars[])
{

    FILE *fp;
    fp = fopen(filename, "r");  //open file
    if(!fp) //if the the file was not succesfully opened
    {
        printf("File %s not found\n", filename);    //print error
        return -1;                                   //and exit file
    }
    char c = ' ';
    while(1)
    {
        c = fgetc(fp);    //read in the next character of the file
        if(feof(fp)) break; //if EOF reached then break
        if(isalpha(c))    //if the current char is a letter of the alphabet,
        {
            ++numChars[1];      //add one to numChars[1] (num of letters in the file)
            if(isupper(c))        //if the current character is uppercase,
                ++freqs[c-'A'];   //increment freqs[c = 'A'] (Ex. If c is R, then 'R' - 'A' = 17 and freqs[17] will be incremented
            else if(islower(c))  //if the current character is lowercase,
                ++freqs[c-'a'];   //subtract 'a' to find the index instead
        }
        ++numChars[0];  //add one to numChars[0] (num of characters in the file
    } 
    return 0;
}

//results() calculates the percents of each letter and then prints all the results to the screen
void results(char filename[], int freqs[], int alphasize, int numChars[])
{
    float percents[alphasize];  //create an array to store the percentage of each letter
    int i;
    for(i = 0; i < alphasize; i++)  //loop through the freqs array and calculate the percentage of each letter by dividing
                                    //the # of occurrences of each letter by the # of total letters in the file
        percents[i] = (float)freqs[i]/numChars[1];

    //print results to the screen
    printf("Here are the results for %s:\n", filename);
    printf("There were %d total characters.\n", numChars[0]);
    printf("There were %d letters.\n", numChars[1]);
    printf("Letter counts:");
    for(i = 0; i < alphasize; i++)
    {
        if(i%6 == 0)
            printf("\n");
        printf("  %c: %6d", i+'a', freqs[i]); 
    }
    printf("\n\nLetter percentages:");
    for(i = 0; i < alphasize; i++)
    {
        if(i%6 == 0)
            printf("\n");
        printf("  %c: %4.1lf%%", i+'a', percents[i]*100); 
    }
    printf("\n");
}
