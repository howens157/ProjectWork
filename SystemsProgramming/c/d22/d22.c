#include <stdio.h>
#include <stdlib.h>

#include "libdinos.h"

void printdino(dino *d)
{
    printf("%f %f %f %f %s\n", d->lat, d->lng, d->maxma, d->minma, d->name);
}

int main()
{
    int n;
    
    dino *dinos[30000];
    
    n = readdinos("dinosaur.dat", dinos);
    
    printf("read %d dinos\n", n);

    printdino(dinos[0]);    
    printdino(dinos[250]);
    printdino(dinos[3000]);
    
    return 0; 
}
