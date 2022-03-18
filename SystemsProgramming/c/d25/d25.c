#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <signal.h>

#include "libdinos.h"
#include "libgeodist.h"

dino *dinos[30000];
int n;

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

void handle_sigusr1(int sig, siginfo_t *siginfo, void *context)
{
    int dinonum;
    FILE *ifp = fopen("dinonum.bin", "rb");
    fread(&dinonum, sizeof(int), 1, ifp);
    char *buf = malloc(30*sizeof(char));
    sprintf(buf, "dino_%d.bin", dinonum);
    save_dino(dinos[dinonum], buf);
    free(buf);
    fclose(ifp);
}

void handle_sigusr2(int sig, siginfo_t *siginfo, void *context)
{
    int dinonum;
    FILE *ifp = fopen("dinonum.bin", "rb");
    fread(&dinonum, sizeof(int), 1, ifp);
    char *buf = malloc(30*sizeof(char));
    sprintf(buf, "dino_%d.bin", dinonum);
    free(dinos[dinonum]->name);
    load_dino(dinos[dinonum], buf);
    free(buf);
    fclose(ifp);
}

void handle_sigint(int sig, siginfo_t *siginfo, void *context)
{
    int i;
    for(i = 0; i < n; i++)
    {
        free(dinos[i]->name);
        free(dinos[i]);
    }
    exit(EXIT_SUCCESS);
}
int main()
{
    struct sigaction act1 = {0};
    act1.sa_sigaction = &handle_sigusr1;
    act1.sa_flags = SA_SIGINFO;
    sigaction(SIGUSR1, &act1, NULL);

    struct sigaction act2 = {0};
    act2.sa_sigaction = &handle_sigusr2;
    act2.sa_flags = SA_SIGINFO;
    sigaction(SIGUSR2, &act2, NULL);

    struct sigaction act3 = {0};
    act3.sa_sigaction = &handle_sigint;
    act3.sa_flags = SA_SIGINFO;
    sigaction(SIGINT, &act3, NULL);

    n = readdinos("dinosaur.dat", dinos);
    
    int pid = getpid();
    printf("%d\n", pid);
 
    while(1){}
 
    return 0; 
}
