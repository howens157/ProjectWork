#include <stdio.h>

int main()
{
	int i = 33;
	int j = 44;

	int *p = &i;

	printf("%d\n", i);
	printf("%p\n", &i);

	printf("%p\n", p);
	printf("%p\n", &p);

	printf("%d\n", *p);

}

