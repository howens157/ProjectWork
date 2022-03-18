#include <stdio.h> 

#include "littlelib.h"

void printprime()
{
    int lower = 5, upper = 800, r, b;
    
    r = randint(lower, upper);
    b = is_prime(r);
    
    if (b)
        printf("%d is prime\n", r);
    else
        printf("%d is not prime\n", r);    
}

int main() 
{ 
    int i = 0;
  
    init_littlelib();
    
    for (i=0; i<10; i++)
        printprime();
    
    return 0; 
}
