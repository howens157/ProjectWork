//mysayings.c
//Hayden Owens
//CSE 20311
#include <stdio.h>
#include <string.h>
#include <ctype.h>

//global consts for max sizes
const int maxlen = 256;
const int maxsayings = 50;
const int filenamelen = 30;

//function prototypes
int startup(char[][maxlen], char[]);
int prompt();
void display(char[][maxlen], int);
int enternew(char[][maxlen], int);
int delete(char[][maxlen], int);
void search(char[][maxlen], int);
void savetonew(char[][maxlen], int);

int main()
{
    char sayings[maxsayings][maxlen];   //create an array to store all the sayings
    char infilename[filenamelen];   //string to store the filename to read from

    printf("Please enter the name of a startup file: ");    //prompt user for startup file
    scanf("%s", infilename);    //and store it in infilename
    
    int size = startup(sayings, infilename);    //call startup to read in the file and store its size
    
    if(size == -1)  //if the file could not connect
        return 1;   //quit the program

    int userchoice; //userchoice will store the option the user enters
    while(1)    //will loop until user decides to quit
    {
        userchoice = prompt();  //prompt the user
        switch(userchoice)  //switch statement will call appropriate function based on userchoice or quit
        {
            case 1:
                display(sayings, size); //option 1 will call display() to print all the sayings in sayings[][]
                break;
            case 2:
                size = enternew(sayings, size); //option 2 will add a new saying to sayings[][] and update the size
                break;
            case 3:
                size = delete(sayings, size);   //option 3 will allow the user to choose a saying to delete and update the size
                break;
            case 4:
                search(sayings, size);  //option 4 will allow the user to search for a substring and display all sayings that contain that substring
                break;
            case 5:
                savetonew(sayings, size);   //option 5 will allow the user to save the current sayings[][] with their changes to a file of their choice
                break;
            case 6:
                printf("Goodbye!\n");
                return 0;
        }
    }
}

//startup() attempts to connect to the filename input by the user, prints error and returns -1 if not successful. If succesful it reads in the file and returns the size
int startup(char sayings[][maxlen], char infilename[])
{
    FILE *ifp = fopen(infilename, "r"); //create a pointer to the file in read mode
    if(!ifp)    //if the file could not connect
    {
        printf("File %s not found.\n"); //print error
        return -1;  //and return -1
    }
    int count = 0;  //count will keep track of the size of the file
    char curr[maxlen];  //string to store the current saying being read in
    while(1)    //will loop until EOF
    {
        fgets(curr, maxlen, ifp);   //store the next line of the file in curr
        if(feof(ifp)) break;    //if EOF has been reached, break
        strcpy(sayings[count], curr);   //copy the current string into the sayings array
        count++;    //increment count to keep track of the number of sayings
    }
    return count;   //return count which is the number of sayings read in
}

//prompt() displays the choices, prompts the user, and returns their selection
int prompt()
{
    int userchoice;
    PROMPT: //label for goto statement
    //print all the choices
    printf("\nHere are the tasks you can perform:\n");
    printf("1. Display all saying currently in the file.\n");
    printf("2. Enter a new saying into the file.\n");
    printf("3. Delete a saying from the file.\n");
    printf("4. List sayings that contain a given word.\n");
    printf("5. Save all sayings in a new text file.\n");
    printf("6. Quit the program.\n");
    printf("Please enter a choice: ");
    scanf("%d", &userchoice);   //read in the users choice
    if((userchoice > 6) | (userchoice < 1)) //if it is not within the acceptable range
    {
        while(fgetc(stdin) != '\n'){}   //clear out stdin because if they enter a word for some reason there may be left over letters in stdin
        printf("%d is not a valid choice.\n", userchoice);  //print error
        goto PROMPT;    //and jump back to PROMPT to try again
    }
    return userchoice;  //once user has made a valid selection, return their choice.
}

//display() will print all the sayings currently stored in sayings[][]
void display(char sayings[][maxlen], int size)
{
    if(size == 0)   //if sayings[][] is empty,
        printf("There are no sayings in the file\n");   //inform user
    int i;
    for(i = 0; i < size; i++)   //loop through the rows of sayings[][]
    {
        printf("%d) %s", i+1, sayings[i]);  //and print each saying
        if(!strchr(sayings[i],'\n'))    //if the current saying does not have a new line character already
            printf("\n");   //then print one at the end (this is because if the user enters a saying that is maxlen or greater, 
                                                       //fgets will not be able to include the new line character)
    }
}

//enternew() will prompt the user to enter a new saying and add it as the last row of sayings[][] and return the updated size
int enternew(char sayings[][maxlen], int size)
{
    if(size >= maxsayings) //if there are already maxsayings in sayings[][],
    {
        printf("Sorry, the file can't hold anymore sayings!\n");    //inform user
        return size;    //and return the size unchanged
    }

    char newsaying[maxlen]; //string to store users input saying
    printf("Please enter the new saying: \n");  //prompt user
    fgetc(stdin);   //fgetc() in case there is a stray \n in stdin
    fgets(newsaying, maxlen, stdin);    //read the users saying into newsaying
    char *pch;  //create a pointer
    pch = strchr(newsaying, '\0');  //pch will point to the first occurrence of the null character in newsaying
    if(pch-newsaying == maxlen-1)   //pch-newsaying is the difference between the addresses of the null character and the first character.
    {                               //If this is equal to maxlen-1, that indicates that the user input a saying of length maxlen or greater
                                    //meaning that there may be stray characters left in stdin
        while(fgetc(stdin) != '\n'){}   //clear out stdin 
        printf("Your saying may have been too long. Only the first 255 characters were saved.\n");  //inform user that the saying may have been cut off
    }
    strcpy(sayings[size++], newsaying); //copy the users saying into the next open row in sayings[][] and increment size
    return size;    //return the incremented size
}

//delete() will prompt the user to input the number of a saying to delete, remove it from sayings[][] and shift the elements after it back up
int delete(char sayings[][maxlen], int size)
{
    if(size == 0)   //if sayings[][] is already empty,
    {
        printf("There are no sayings in the file.\n");  //inform the user
        return 0;   //and return 0 as the size
    }
    int del_index;
    int i;
    printf("Please enter the number of the saying you would like to delete: "); //prompt the user for which saying to delete
    scanf("%d", &del_index);    //and store it in del_index (note: as the sayings are printed starting at index 1, an input of i will delete sayings[del_index - i])
    if(size == maxsayings)  //if sayings[][] is full
    {
        for(i = del_index-1; i < size-1; i++)   //loop from the saying to be deleted to the second to last saying
        {
            strcpy(sayings[i], sayings[i+1]);   //and copy them backwards in order to delete sayings[del_index - 1]
        }
        strcpy(sayings[maxsayings-1], "\0");    //finally replace the last saying in sayings[][] will a null character
    }
    else    //otherwise, if sayings[][] is not full, meaning looping until size will not reach the end of the allocated memory
    {
        for(i = del_index-1; i < size; i++) //loop from the saying to be deleted until the end
        {
            strcpy(sayings[i], sayings[i+1]);   //and copy backwards in order to delete sayings[del_index - 1]
        }
    }
    size--; //update size after deletion
    return size;    //and return the new size
}

//search() prompts the user to enter a substring to search for, and displays all sayings that contain that substring
void search(char sayings[][maxlen], int size)
{
    int i;
    char target[maxlen];    //target substring to search for
    while(fgetc(stdin) != '\n'){}   //clear out stdin of any stray newline characters
    printf("Please enter the word you would like to search for: "); //prompt user
    fgets(target, maxlen, stdin);   //and store their entered substring in target[]
    char *pch = strchr(target,'\n');//create a pointer to the first occurence of '\n' in target[]
    *pch = '\0';    //and replace it with a null character in order to eliminate the \n
    for(i = 0; i < size; i++)   //loop through sayings[][]
    {
        if(strstr(sayings[i], target))  //if there is an occurence of target in sayings[i]
        {
            printf("%d) %s", i+1, sayings[i]);  //print sayings[i]
            if(!strchr(sayings[i],'\n'))    //and as in display() add a \n if there isn't one already
                printf("\n");
        }
    }
}

//savetonew() will write sayings[][] to a file of the users choice
void savetonew(char sayings[][maxlen], int size)
{
    char outfilename[filenamelen];  //outfilename will store the name of the file to write to
    printf("Please enter the name of the file to save to: ");   //prompt user for filename
    scanf("%s", outfilename);   //and read it in

    FILE *ofp;  //create a file pointer
    ofp = fopen(outfilename, "w");  //and open outfilename in write mode
    if(size == 0)   //if sayings[][] is empty
    {
        return; //just return as this will leave the file empty
    }
    
    //otherwise,
    int i;
    for(i = 0; i < size; i++)   //loop through sayings[][]
    {
        fprintf(ofp, sayings[i]);   //and write the sayings to the file
        if(!strchr(sayings[i],'\n'))    //as in display() and search(), add a \n if there isn't one already
            fprintf(ofp, "\n");
    }
}
