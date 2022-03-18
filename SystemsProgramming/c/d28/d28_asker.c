#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <math.h>
#include <limits.h>
#include <errno.h>
#include <sys/wait.h>
#include <signal.h>
#include <netdb.h>
#include <netinet/in.h>

void test_dinos(int sockfd)
{
    int dinonums[] = { 9, 0, 2, 1, 0, 50, -1 };
    int di, n;

    int buflen = 2049;
    char buf[buflen];
    
    for(di=0; di<7; di++)
    {
        memset(buf, 0, buflen);
        sprintf(buf, "%d", dinonums[di]);
        n = write(sockfd, buf, strlen(buf));
        
        if (n < 0) {
            perror("could not write");
            exit(1);
        }
        
        //sleep(1);
        
        memset(buf, 0, buflen);
        n = read(sockfd, buf, buflen-1);
        
        if (n < 0) {
            perror("could not read");
            exit(1);
        }
            
        if (dinonums[di] != -1)
            printf("dino %d is %s", dinonums[di], buf);
   }
}

int main(int argc, char *argv[])
{
    int sockfd, portno, n;
    struct sockaddr_in serv_addr;
    struct hostent *server;

    int buflen = 32;
    char buf[buflen];

    if (argc < 3) {
        fprintf(stderr,"usage %s hostname port\n", argv[0]);
        exit(0);
    }

    portno = atoi(argv[2]);

    sockfd = socket(AF_INET, SOCK_STREAM, 0);

    if (sockfd < 0) {
        perror("could not create socket");
        exit(1);
    }

    server = gethostbyname(argv[1]);

    if (server == NULL) {
        fprintf(stderr,"could not find host\n");
        exit(0);
    }

    bzero((char *) &serv_addr, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    bcopy((char *)server->h_addr, (char *)&serv_addr.sin_addr.s_addr, server->h_length);
    serv_addr.sin_port = htons(portno);

    if (connect(sockfd, (struct sockaddr*)&serv_addr, sizeof(serv_addr)) < 0) {
        perror("could not connect");
        exit(1);
    }

    test_dinos(sockfd);
    
    close(sockfd);
    
    return 0;
}
