#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
    int a, b;
    if(argc == 1)
    {
        printf("Please enter two integers: ");
        scanf("%d %d", &a, &b);
    }
    else if(argc == 3)
    {
        a = atoi(argv[1]);
        b = atoi(argv[2]);
    }
    else if(argc == 2)
    {
        printf("Only one number was entered\n");
        return 1;
    }
    else if(argc > 3)
    {
        printf("Too many numbers were entered\n");
        return 1;
    }
    
    printf("Their sum is %d\n", a+b);
    return 0;
}
