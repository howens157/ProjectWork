// sum.c
//
#include <stdio.h>
#include <math.h>

int main()
{
    int sumSq = 0;
    double sumSqrt = 0;
    int i;
    for(i = 1; i <= 10; i++)
    {
        sumSq = sumSq + i*i;
        sumSqrt = sumSqrt + sqrt(i);
    }
    printf("The sum of the squares is %d\n", sumSq);
    printf("The sum of the square roots is %lf\n", sumSqrt);
}
