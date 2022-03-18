// quad.c
// computes the roots of a quadratic equation
#include <stdio.h>
#include <math.h>

int main()
{
    double a, b, c, disc;
    double x1, x2;

    printf("Enter the coefficients (a,b,c) of a quadratic equation: ");
    scanf("%lf %lf %lf", &a, &b, &c);
    disc = pow(b,2)-4*a*c;
    if(disc < 0) 
    {
        printf("There are no real solutions.\n");
    }
    else if(disc > 0) 
    {
        x1 = (-b + sqrt(disc))/(2*a);
        x2 = (-b - sqrt(disc))/(2*a);
        printf("There are two solutions:\nx1 = %lf\nx2 = %lf\n", x1, x2);
    } 
    else 
    {
        x1 = -b/(2*a);
        printf("There is one solution:\nx = %lf\n", x1);
    }
    return 0;
}
