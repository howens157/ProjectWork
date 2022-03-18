//pathmain.c
//Hayden Owens
//CSE 20311
//pathmain.c will read in an array of points from a text file and compute the distance of a path through those points
const int MAXSIZE = 30;

#include <stdio.h>
#include "pathfunc.h" //includes definition for Point struct

int main(int argc, char *argv[])
{
    Point points[MAXSIZE];  //create an array of Points of maxsize
    
    int numPoints = 0;  //initialize and define vars for the number of points and final distance
    float distance = 0.0;

    if(argc == 1)   //if the user did not enter the text file as a command line argument
    {
        numPoints = readUser(points);   //read in the filename from the user
    }
    else if(argc == 2)  //if the user did enter the text file as a command line argument
    {
        numPoints = readFile(argv[1], points);  //go straight to reading in the data from the file
    }
    else    //otherwise print an error message and quit
    {
        puts("Too many arguments");
        return 1;
    }
    if(numPoints == -1) //if readUser()/readFile(0) returned -1, print "File not found" and quit
    {
        puts("File not found");
        return 1;
    }
    distance = findDistance(points, numPoints); //compute the distance of the path
    display(points, numPoints, distance);   //print the points and their distance

    return 0;
}
