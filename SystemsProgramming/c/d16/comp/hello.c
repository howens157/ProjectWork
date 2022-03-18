#include <stdio.h>

int foo()
{
	return(0);
}

int main()
{
	printf("hello world!\n");

	int a;

	a = foo();

	if (a > 80) {
		printf("got here!\n");
	} else {
		printf("over here!\n");
	}

	return(1);
}


