#include <signal.h> 
#include <stdio.h> 
#include <stdlib.h> 
#include <unistd.h>
#include <string.h>

#include "libdinos.h"

void printdino(dino *d)
{
    printf("%f %f %f %f %d %s\n", d->lat, d->lng, d->maxma, d->minma, d->namelen, d->name);
}

void clearbuf(char *buf, int len)
{
    int i;
    
    for(i=0; i<len; i++)
        buf[i] = 0;
}

int main(int argc, char **argv) 
{
    if(argc != 3)
        return 1;
    
    int pid = atoi(argv[1]);
    int dn = atoi(argv[2]);

    FILE *fp = fopen("dinonum.bin", "wb");
    fwrite(&dn, sizeof(int), 1, fp);
    fclose(fp);

    kill(pid, SIGUSR1);
    
    sleep(2);

    char *dfn = malloc(256 * sizeof(char));
    sprintf(dfn, "dino_%d.bin", dn);

    dino d;
    load_dino(&d, dfn);
    
    printdino(&d);
    
    free(d.name);
    d.name = "Santaclausosaurus Rex";
    d.lat = 90.0;
    d.lng = 0.0;
    d.maxma = 4500.0;
    d.minma = 0.0;
    d.namelen = strlen(d.name);
    
    printf("changed to:\n");
    printdino(&d);
    
    save_dino(&d, dfn);
    
    kill(pid, SIGUSR2);
    
    sleep(2);
    
    kill(pid, SIGUSR1);

    sleep(2);
    
    printf("received back:\n");

    dino d1;
    load_dino(&d1, dfn);
    
    printdino(&d1);
    
    free(dfn);
    
    return 0;
}
