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
