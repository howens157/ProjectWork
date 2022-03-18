#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "libsoftmodem.h"

int main(int argc, char **argv)
{
    char *msg;
    char *nmg;
    char *adt;
    
    int msglen;
    int nmglen;
    int adtlen;
    
    if(argc < 2)
        return 1;
    
    msg = argv[1];
    msglen = strlen(msg);
    
    printf("%d %s\n", msglen, msg);
    
    // msg points to the string to be converted to audio
    // adt points to nothing right now
    
    adtlen = tx(msg, &adt, msglen);
    
    // msg still points to the string to be converted to audio
    // adt now points to a buffer of audio data of length adtlen
    
    printf("%d\n", adtlen);
    
    nmglen = rx(&nmg, adt, adtlen);
    
    // nmg now points to a NEW buffer that contains the message converted from audio data
    
    printf("%d %s\n", nmglen, nmg);
    
    // note that libsoftmodem allocates the space for adt and nmg for you, you do not 
    // need to do that yourself... but... you still have to free it yourself
    
    free(nmg);
    free(adt);
}
