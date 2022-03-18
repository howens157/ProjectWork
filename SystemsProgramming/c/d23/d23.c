#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "libdinos.h"
#include "libgeodist.h"

double calc_geodist(dino *d0, dino *d1)
{
    return geodist(d0->lat, d0->lng, d1->lat, d1->lng);
}

double calc_timedist(dino *d0, dino *d1)
{
    double t0 = (d0->maxma + d0->minma) / 2;
    double t1 = (d1->maxma + d1->minma) / 2;
    return fabs(t0 - t1);
}

void printdino(dino *d)
{
    printf("%f %f %f %f %s\n", d->lat, d->lng, d->maxma, d->minma, d->name);
}

int main()
{
    int n;
    double d;
    
    dino *dinos[30000];
    
    n = readdinos("dinosaur.dat", dinos);
    
    printf("dino 50 is:\n");
    printdino(dinos[50]);

    dino d1;
    
    d = nearest_dino(dinos[50], &d1, dinos, n, &calc_timedist);
    
    printf("nearest in time is %f units distant\n", d);
    printdino(&d1);
    
    d = nearest_dino(dinos[50], &d1, dinos, n, &calc_geodist);
    
    printf("nearest in geography is %f units distant\n", d);
    printdino(&d1);

    printf("\n");
    printf("dino 256 is:\n");
    printdino(dinos[256]);
    
    d = nearest_dino(dinos[256], &d1, dinos, n, &calc_timedist);
    
    printf("nearest in time is %f units distant\n", d);
    printdino(&d1);
    
    d = nearest_dino(dinos[256], &d1, dinos, n, &calc_geodist);
    
    printf("nearest in geography is %f units distant\n", d);
    printdino(&d1);
    
    return 0; 
}
