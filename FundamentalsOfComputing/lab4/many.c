//many.c
//Hayden Owens
#include <stdio.h>

int main() {
    int userNum, i, j;
    int nums[20];
    userNum = 0;
    printf("Please enter up to 20 positive integers: ");
    for(i = 0; i < 20; i++) {
        scanf("%d", &nums[i]);
        if(nums[i] == -1)
            break;
    }
    i--;
    for(j = i; j >= 0; j--) {
        printf("%d ", nums[j]);
    }
    printf("\n");
    return 0;
}
