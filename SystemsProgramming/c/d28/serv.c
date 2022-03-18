#include <errno.h>
#include <sys/wait.h>
#include <signal.h>
#include <netdb.h>
#include <netinet/in.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

void handle_incoming_conn(int cl)
{
	int buflen = 256, rc;
	char *buf = malloc(buflen * sizeof(char));
	memset(buf, 0, buflen);

	while((rc = read(cl, buf, buflen)) > 0)
	{
		printf("read %d bytes: %s\n", rc, buf);
		memset(buf, 0, buflen);
	}
}

int main()
{
	int sock, t, port, cl, cpid;

	sock = socket(AF_INET, SOCK_STREAM, 0);

	port = 8001;

	struct sockaddr_in addr;
	addr.sin_family = AF_INET;
	addr.sin_addr.s_addr = INADDR_ANY;
	addr.sin_port = htons(port);

	t = bind(sock, (struct sockaddr *) &addr, sizeof(addr));

	if(t < 0)
	{
		perror("could not bind!");
		return -1;
	}

	listen(sock, 5);

	while(1)
	{
		cl = accept(sock, NULL, NULL);

		cpid = fork();

		if(cpid == 0)
		{
			handle_incoming_conn(cl);
			return 0;
		}
	}
}

