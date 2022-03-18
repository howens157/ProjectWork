#include <errno.h>
#include <sys/wait.h>
#include <signal.h>
#include <netdb.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "libdinos.h"

void handle_incoming_conn(int cl, dino *dinos[], int n)
{
    int buflen = 256, rc;
    char *buf = malloc(buflen * sizeof(char));
    memset(buf, 0, buflen);
    int wrklen = 2048;
    char *wrk = malloc(wrklen * sizeof(char));
    while((rc = read(cl, buf, buflen)) > 0)
    {
        char *ptr;
        int dinoindex = (int)strtol(buf, &ptr, 10);
        if(dinoindex >= n || dinoindex < 0)
        {
            sprintf(wrk, "Invalid Index\n");
        }
        else
        {
            dino *d = dinos[dinoindex];
            sprintf(wrk, "%f %f %f %f %s\n", d->lat, d->lng, d->maxma, d->minma, d->name);
        }
        int nw;
        nw = write(cl, wrk, strlen(wrk));
        memset(buf, 0, buflen);
        memset(wrk, 0, wrklen);
    }
    free(buf);
    free(wrk);
}

void handle_sigchld(int sig)
{
    wait(NULL);
}

int main(int argc, char* argv[])
{
    int n;
    double d;

    dino *dinos[30000];

    n = readdinos("dinosaur.dat", dinos);


    int sock, t, port, cl, cpid;

    sock = socket(AF_INET, SOCK_STREAM, 0);

    signal(SIGCHLD, &handle_sigchld);

    char *ptr;
    port = (int)strtol(argv[1], &ptr, 10);

    struct sockaddr_in addr;
    addr.sin_family = AF_INET;
    addr.sin_addr.s_addr = INADDR_ANY;
    addr.sin_port = htons(port);

    t = bind(sock, (struct sockaddr *) &addr, sizeof(addr));

    if(t < 0)
    {
        perror("Could not bind");
        return -1;
    }

    listen(sock, 5);

    while(1)
    {
        cl = accept(sock, NULL, NULL);
        cpid = fork();

        if(cpid == 0)
        {
            handle_incoming_conn(cl, dinos, n);
            close(cl);
            return 0;
        }
        close(cl);
    }


    int i;
    for(i = 0; i < n; i++)
    {
        free(dinos[i]->name);
        free(dinos[i]);
    }
    
    return 0;
}
