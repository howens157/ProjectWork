#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <limits.h>


int main()
{
	int ppid = getpid();

	printf("here first! %d\n", ppid);

	int cpid = fork();

        if(cpid == 0)
        {


                return 0;
        }

	cpid = fork();

        if(cpid == 0)
        {


                return 0;
        }
	
	int pid = getpid();

	printf("got here! %d, %d\n", pid, cpid);

	int r = wait(NULL);

	printf("got back %d\n", r);

	r = wait(NULL);

	printf("got back %d\n", r);

	while(1) { }

	return 0;
}

