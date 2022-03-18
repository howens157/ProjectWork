#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int is_pal(char *s)
{
	char *head = s;
	char *tail = s + strlen(s) - 1;

	while(*head == *tail)
	{
		head++;
		tail--;

		if(head <= tail)
			break;
	}

	if(head >= tail)
		return 1;

	return 0;
}

void chomp(char *s)
{
	if(s[strlen(s)-1] == '\n')
		s[strlen(s)-1] = '\0';
}

int main()
{
	char *buf = malloc(24 * sizeof(char));
	fgets(buf, 24, stdin);

	chomp(buf);

	printf("%d\n", is_pal(buf));

	free(buf);

	return(0);
}


