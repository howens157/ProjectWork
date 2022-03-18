#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <unistd.h>
#include <limits.h>
#include "libdinos.h"
#include "libgeodist.h"

#define NUM_PROCESSES 4

typedef struct {
    int dinoindex;
    int totaldinos;
} threadarg;

typedef struct {
    int mynum;
    double dist;
} fret;

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

    fret myreturn;
    myreturn.mynum = arg->dinoindex;
    myreturn.dist = closest;
    //printf("%d %lf\n", myreturn.mynum, myreturn.dist);
    char *fn = malloc(64*sizeof(char));
    int cpid = getpid();
    sprintf(fn, "ret_%d.bin", cpid);
    FILE *fp = fopen(fn, "wb");
    fwrite(&myreturn.mynum, sizeof(int), 1, fp);
    fwrite(&myreturn.dist, sizeof(double), 1, fp);
    fclose(fp);
    free(fn);
}

int main()
{
    int numdinos;
    numdinos = readdinos("dinosaur.dat", dinos);

    int i, j, cpid, r;
    
    for(j=0; j<n; j=j+4)
    {
        threadarg targs[NUM_PROCESSES];

        for(i=0; i<NUM_PROCESSES; i++)
        {
            targs[i].dinoindex = j+i;
            targs[i].totaldinos = numdinos;
        }
     
        for(i=0; i<NUM_PROCESSES; i++)
        {
            //pthread_create(&tid[i], NULL, threadfcn, (void *) &targs[i]);
            cpid = fork();
            if(cpid == 0)
            {
                threadfcn((void*) &targs[i]);
                return 0;
            }
        }

        for(i = 0; i < NUM_PROCESSES; i++)
        {
            //pthread_join(tid[i], NULL);
            r = wait(NULL);
            char *fn = malloc(64*sizeof(char));
            sprintf(fn, "ret_%d.bin", r);
            FILE *fp = fopen(fn, "rb");
            fret ret;
            fread(&ret.mynum, sizeof(int), 1, fp);
            fread(&ret.dist, sizeof(double), 1, fp);
            fclose(fp);
            remove(fn);
            free(fn);
            nearest_dinos[ret.mynum] = ret.dist;
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
