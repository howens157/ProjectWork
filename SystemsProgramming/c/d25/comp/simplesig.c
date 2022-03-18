#include <stdio.h>
#include <stdlib.h>
#include <signal.h>

void handle_sigusr1(int sig)
{
	printf("got signal %d\n", sig);
}

int main()
{
	signal(SIGUSR1, handle_sigusr1);	

	return 0;
}

