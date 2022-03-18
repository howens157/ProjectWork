#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "libsoftmodem.h"

int main(int argc, char **argv)
{
    char *msg;
    char *adt;
    
    int msglen;
    int adtlen;
    
    if(argc < 2)
        return 1;
    
    msg = argv[1];
    msglen = strlen(msg);
    
    adtlen = tx(msg, &adt, msglen);
    
    FILE *fp = fopen("smtadt.bin", "wb");
    fwrite(&adtlen, sizeof(int), 1, fp);
    fwrite(adt, adtlen, 1, fp);
    fclose(fp);

    free(adt);
}
