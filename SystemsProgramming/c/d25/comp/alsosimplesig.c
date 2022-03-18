#include <stdio.h>
#include <stdlib.h>
#include <signal.h>

void handle_sigusr1(int sig, siginfo_t *siginfo, void *context)
{
	printf("got signal %d from pid %d from uid %d\n", sig, siginfo->si_pid, siginfo->si_uid);
}

int main()
{
	struct sigaction act1;
	act1.sa_sigaction = &handle_sigusr1;
	act1.sa_flags = SA_SIGINFO;

	sigaction(SIGUSR1, &act1, NULL);	

	while(1) { }

	return 0;
}

