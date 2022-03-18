//polar.c
//Hayden Owens
//CSE 20311
#include <stdio.h>
#include <math.h>

//function prototypes
int get_quadrant(double, double);
double get_radius(double, double);
double get_angle(double, double);
void show_info(int, double, double);

int main() {
    double X, Y;    //declare X, Y
    
    printf("Please enter the X coordinate: ");  //prompt user and assign inputs
    scanf("%lf", &X);
    printf("Please enter the Y coordinate: ");
    scanf("%lf", &Y);

    show_info(get_quadrant(X, Y), get_radius(X, Y), get_angle(X, Y)); //call all functions

    return 0;
}

//Determines the quadrant of the coordinate based on whether or not X/Y are +/-
int get_quadrant(double X, double Y) {
    if((X > 0) && (Y > 0))  //If +, +
        return 1;           //quadrant 1
    else if((X < 0) && (Y > 0)) //If -, +
        return 2;               //quadrant 2
    else if((X < 0) && (Y < 0)) //If -, -
        return 3;               //quadrant 3
    else if((X > 0) && (Y < 0)) //If +, -
        return 4;               //quadrant 4
    else
        return -1;  //return -1 as an error indicator if none of the above
}

//Calculate the radius of the coordinate
double get_radius(double X, double Y) {
    return sqrt(pow(X, 2) + pow(Y, 2)); //return the radius using the distance formula
}

//Calculate the angle in radians and then convert to degrees
double get_angle(double X, double Y) {
    return atan2(Y, X)*180/M_PI; //Calls atan2(Y, X) to get angle in radians. *180/pi to convert to degrees
}

//Display all relevant information of a polar coordinate
void show_info(int quad, double radius, double angle) {
    printf("\nThe point is in Quadrant %d.\n", quad);
    printf("The point's polar coordinates are:\nRadius = %g\tAngle = %g Degrees\n", radius, angle);
}
