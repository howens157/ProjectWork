#include <stdio.h> 

#include "littlelib.h"

void printprime()
{
    int randnum = randint(5, 800);
    if(is_prime(randnum)){
        printf("%d is prime\n", randnum);
    }
    else {
        printf("%d is not prime\n", randnum);
    }
}

int main() 
{ 
    int i = 0;
  
    init_littlelib();
    
    for (i=0; i<10; i++)
        printprime();
    
    return 0; 
}
