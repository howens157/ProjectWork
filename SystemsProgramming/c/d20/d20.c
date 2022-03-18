#include <stdio.h>
#include <stdlib.h>

#include "libdinos.h"

int main() 
{
    FILE *fp;
    char delim = '\t';
    int len = 2048;
    char *buf = malloc(len * sizeof(char));
    int n;
    
    fp = fopen("dinosaur.dat", "r");
    
    n = readline(fp, buf, len);
    
    printf("read %d chars\n", n);
    
    int max = 50;
    char *splits[max];
    int ns = split(buf, splits, delim, max, len);
    
    int i;
    for(i=0; i<ns; i++)
    {
        printf("%s\n", splits[i]);
    }
    
    return 0; 
}
