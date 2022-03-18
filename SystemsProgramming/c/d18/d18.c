#include <stdio.h> 

#include "littlelib.h"

int main() 
{
    init_littlelib();
    
    int a[] = { 2, 3, 4, 5, 6, 0 };
    int i;
    
    printf("sum: %d\n", sumnums(a));
    
    for(i=0; i<10; i++)
    {
	//printf("%d\n", arraylen(a));
   	shuffle(a, arraylen(a));
        printarray(a);
    }
        
    return 0; 
}
