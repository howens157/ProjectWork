//primes.c
//Hayden Owens
//CSE 20311
#include <stdio.h>
#include <stdbool.h>

int main()
{
    int i,j;    //ints for loops
    int max = 1000; //Declare max number to search through
    bool nums[max+1];   //Initialize a bool array of size max+1
    for(i = 0; i <= max; i++)   //Loop through the full array
    {                           //and set the value at each
        nums[i] = 1;            //index to 0
    }
    for(i = 2; i <= max; i++)   //Outer loop starts at 2 and goes through every value
    {
        if(nums[i] == 1)    //If i is prime
        {
            for(j = i*i; j <= max; j += i)  //then set all multiples of i to 0
            {
                nums[j] = 0;
            }
        }
    }
    int num_prints; //Variable to keep track of how many prints there have been
    for(i = 2; i <= max; i++)   //Loop through the array starting at 2
    {
        if(nums[i] == 1)    //If i is prime
        {
            printf("%3d ", i);  //print it
            num_prints++;       //increment prints
            if(num_prints%10 == 0)  //and if the num_prints is a multiple of 10
                printf("\n");   //go to next line in order to have 10 columns
        }
    }
    printf("\n");
    return 0;
}
