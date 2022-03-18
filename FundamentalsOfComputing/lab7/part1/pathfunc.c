//pathfunc.c
//Hayden Owens
//CSE 20311
//pathfunc.c contains functions related to pathmain.c
#include <stdio.h>
#include <math.h>
#include "pathfunc.h"   //includes function prototypes and defintion for Point struct

//readUser will read in the filename from the user and then call readFile on that final. It will
//return the numbner of points read in or -1 if the file could not be found
int readUser(Point points[])
{
    int maxlength = 30; 
    char filename[maxlength];   //create a string of length maxlength
    puts("Please enter the filename: ");    //prompt user
    scanf("%s", filename);  //and read in their input
    return readFile(filename, points);  //call readFile and return its value
}

//readFile will connect to filename and then read the data in the file into points[]
int readFile(char filename[], Point points[])
{
    FILE *fp = fopen(filename, "r");    //create a file pointer
    if(!fp) //if the file did not connect, 
    {
        return -1;  //return -1
    }

    int count = 0;  //count will store the number of points in the array

    while(1)    //will loop continuously
    {   
        fscanf(fp, "%f %f", &points[count].x, &points[count].y);    //read in the next line of the file to the
        if(feof(fp))    //if the end of the file has been reached,
            break;  //break
        count++;    //increment count
    }
    return count;
}

//findDistance() will return the distance of the path through points[]
float findDistance(Point points[], int numPoints)
{
    float distance = 0; //distance will hold the total distance through the points
    int i;
    for(i = 0; i < numPoints-1; i++)    //loop through the points[] array
    {   //and add the distance from the current point to the next point
        distance += sqrt(pow((points[i+1].x - points[i].x), 2) +  pow((points[i+1].y - points[i].y), 2));
    }
    return distance;
}

//display() will print the points[] array in a table and output the distance
void display(Point points[], int numPoints, float distance)
{
    printf("There are %d points:\n\n", numPoints);  //output numPoints
    printf("    x    |    y    \n");    //print header for table
    printf("---------+---------\n");
    int i;
    for(i = 0; i < numPoints; i++)  //print every point in points[]
    {
        printf(" %5.1f   | %5.1f\n", points[i].x, points[i].y);
    }
    printf("\nThe path distance through them is %.2f\n", distance); //output the distance
}
