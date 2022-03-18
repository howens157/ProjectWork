#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <pthread.h>
#include "libdinos.h"
#include "libgeodist.h"

#define MAX_THREADS 4

typedef struct {
    int dinoindex;
    int totaldinos;
} threadarg;

dino *dinos[30000];
int n = 20000;
double nearest_dinos[20000];

void printdino(dino *d)
{
    printf("%f %f %f %f %d %s\n", d->lat, d->lng, d->maxma, d->minma, d->namelen, d->name);
}

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

void * threadfcn(void *varg)
{
    threadarg *arg = (threadarg *) varg;
    dino d1;
    double closest = nearest_dino(dinos[arg->dinoindex], &d1, dinos, arg->totaldinos, &calc_geodist);
    nearest_dinos[arg->dinoindex] = closest;
}

int main()
{
    int numdinos;
    numdinos = readdinos("dinosaur.dat", dinos);

    int i;
    int j;
    
    for(j=0; j<n; j=j+4)
    {
        pthread_t tid[MAX_THREADS];
        threadarg targs[MAX_THREADS];

        for(i=0; i<MAX_THREADS; i++)
        {
            targs[i].dinoindex = j+i;
            targs[i].totaldinos = numdinos;
        }
     
        for(i=0; i<MAX_THREADS; i++)
            pthread_create(&tid[i], NULL, threadfcn, (void *) &targs[i]);

        for(i = 0; i < MAX_THREADS; i++)
        {
            pthread_join(tid[i], NULL);
        } 
    }

    for(i = 0; i <= 10; i++)
    {
        printf("%d\t%f\n", i, nearest_dinos[i]);
    }

    for(i = 0; i < numdinos; i++)
    {
        free(dinos[i]->name);
        free(dinos[i]);
    } 

    return 0; 
}
