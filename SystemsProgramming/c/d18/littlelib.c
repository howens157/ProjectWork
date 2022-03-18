#include <stdio.h> 
#include <stdlib.h> 
#include <time.h>

#include "littlelib.h"

int init_littlelib()
{
    srand(1337);
}

int randint(int lower, int upper)
{
    //srand(time(0));
    //srand(1337);
    int num = (rand() % (upper - lower + 1)) + lower; 
    return num;
}

int is_prime(int n)
{
    int i;
    
    for (i=2; i <= n/2; i++)
        if (n % i == 0)
            return 0;
    
    return 1;
}

int arraylen(int a[])
{
    int length = 0;
    int i = 0;
    while(a[i] != 0)
    {
        length++;
        i++;
    }
    return length;
}

int sumnums(int a[])
{
    int sum = 0;
    int i = 0;
    while(a[i] != 0)
    {
        sum += a[i];
        i++;
    }
    return sum;
}

void printarray(int a[])
{
    printf("{ ");
    int i = 0;
    while(a[i] != 0)
    {
        printf("%d ", a[i]);
        i++;
    }
    printf("}\n");
}

void shuffle(int *a, int len)
{
    int i;
    for(i = 0; i < len; i++)
    {    
        int A = randint(0, len-1);
        int B = randint(0, len-1);
        int temp = a[A];
        a[A] = a[B];
        a[B] = temp;
    }
}
