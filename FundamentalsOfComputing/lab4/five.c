//five.c
//Hayden Owens
#include <stdio.h>

int main() {
    int i, j;
    int nums[5];
    printf("Please enter 5 positive integers: ");
    for(i = 0; i < 5; i++)
    {
        scanf("%d", &nums[i]);   
    }
    for(j = 4; j >= 0; j--)
    {
        printf("%d ", nums[j]);
    }
    printf("\n");
    return 0;
}
