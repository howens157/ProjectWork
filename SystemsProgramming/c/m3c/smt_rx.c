#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "libsoftmodem.h"

int main(int argc, char **argv)
{
    char *nmg;
    char *adt;
    
    int nmglen;
    int adtlen;
    
    if(argc < 2)
        return 1;
    
    FILE *fp = fopen(argv[1], "rb");
    fread(&adtlen, sizeof(int), 1, fp);
    adt = malloc(adtlen * sizeof(char));
    fread(adt, adtlen, 1, fp);
    fclose(fp);
    
    nmglen = rx(&nmg, adt, adtlen);
    
    printf("%d %s\n", nmglen, nmg);
    
    free(nmg);
    free(adt);
}
