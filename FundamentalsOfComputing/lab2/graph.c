#include <stdio.h>
#include <math.h>

int main()
{
    //declare necessary variables
    double X, Y, max, min, locMax, locMin;
    int i, j;

    //print header
    printf("Plot for y = 20 + 8*sin(x)/(x/5) from 0.2 to 20.0\n");
    printf("   X   Y");

    //set initial values and locations for max and min to the first value of the graph
    max = 20 + 8*sin(0.2)/(0.2/5);
    min = 20 + 8*sin(0.2)/(0.2/5);
    locMax = 0.2;
    locMin = 0.2;
    
    //create graph
    for(i = 1; i <= 100; i++) {
        X = 0.2*i; 
        Y = 20 + 8*sin(X)/(X/5); //calculate Y
        printf("\n%5.2lf %5.2lf ", X, Y); //Print vertical header
        //print a '>' for every value of Y
        for(j = 0; j < Y; j++) {
            printf(">");
        }
        //check for new max
        if(Y > max) {
            max = Y;
            locMax = X;
        }
        //check for new min
        if(Y < min) {
            min = Y;
            locMin = X;
        }
    }
    
    //print max and min and their locations
    printf("\nThe maximum of %.2lf was at %.2lf\n", max, locMax);
    printf("The minimum of %.2lf was at %.2lf\n", min, locMin);

    return 0;
}
