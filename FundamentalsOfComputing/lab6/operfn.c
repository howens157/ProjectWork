#include <stdio.h>
#include "operfn.h"

void showinfo(float x, float y)
{
    printf("their sum is %g\n", sum(x, y));
    printf("their difference is %g\n", difference(x,y));
    printf("their product is %g\n", product(x,y));
    printf("their quotient is %g\n", quotient(x,y));
}

float sum(float a, float b)
{ return (a+b); }

float difference(float a, float b)
{ return (a-b); }

float product(float a, float b)
{ return (a*b); }

float quotient(float a, float b)
{ return (a/b); }
