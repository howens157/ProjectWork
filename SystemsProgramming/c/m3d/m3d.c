#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#include "libsoftmodem.h"
#include "libsecretradio.h"

char *audio;
char *message;

int msglen;
int msgpos;

int nummsg;

bool decoding;

void radio_callback(int audlen)
{
    char *curraudio = audio;
    char *currmsg;
    int currmsglen = rx(&currmsg, audio, audlen);
    if(!decoding)
    {
        char *totallength = strtok(currmsg, "AA");
        totallength = strtok(totallength, "BB");
        msglen = atoi(totallength);
        message = malloc(msglen+1 * sizeof(char));
        int i;
        for(i = 0; i < msglen+1; i++)
        {
            message[i] = '\0';
        }
        msgpos = 0;
        decoding = true;
        //printf("Start Decoding: Message Length %d:\n", msglen);
    }
    else
    {
        //printf("Next Chunk: %s\n", currmsg);
        int i;
        int j = 0;
        for(i = msgpos; i < msgpos + currmsglen; i++)
        {
            message[i] = currmsg[j];
            //printf("Char %d is %c\n", i, message[i]);
            j++;
        }
        msgpos = msgpos+currmsglen;
        //printf("Running Message: %s\n", message);
        //printf("%d out of %d chars received\n", msgpos, msglen);
    }

    if(msglen == msgpos)
    {
        //printf("Full Message %d: %s\n", nummsg, message);
        char fnbuf[100];
        sprintf(fnbuf, "messages/msg_%d.txt", nummsg);
        remove(fnbuf);
        FILE *output = fopen(fnbuf, "w");
        fprintf(output, "%s\n", message);
        free(message);
        nummsg++;
        

        msglen = 0;
        decoding = false;
    }
     
    free(currmsg);
}

int main(int argc, char **argv)
{
    nummsg = 0;
    msgpos = 0;
    msglen = 0;
    decoding = false;    

    secretradio_init();

    audio = secretradio_get_audioloc();

    secretradio_register_callback(&radio_callback);

    secretradio_listen(0);

    secretradio_cleanup();

    return 0;
}

