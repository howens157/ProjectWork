#include<stdio.h>

int main ()
{
    //initializes varialbes
    int i, j, k;
    int X, Y;

    //prompts user and assigns variable
    printf("Enter X (number of columns): ");
    scanf("%d", &X);
    printf("Enter Y (number of rows): ");
    scanf("%d", &Y);

    //Lines 16-26 create horizontal header at the top
    printf(" *  ");
    for(i = 1; i <= X; i++)
    {
        printf("%5d", i);
    }
    printf("\n   -");
    for(i = 1; i <= X; i++)
    {
        printf("-----");
    }
    printf("\n");

    
    for(j = 1; j <= Y; j++) //outer loop increments y and prints the vertical header
    {
        printf("%2d |", j);
        for(k = 1; k <= X; k++) //inner loop prints the table results
        {
            printf("%5d", j*k);
        }  
        printf("\n");
    }
    
    return 0;
}
