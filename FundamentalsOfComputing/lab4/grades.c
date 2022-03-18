//grades.c
//Hayden Owens
//CSE 20311
#include <stdio.h>
#include <math.h>

// function prototypes ...
float stdev(int *grades, int size); //Both functions take a pointer to the first
float mean(int *grades, int size);  //element of the array and the size of the
                                    //array as parameters
int main()
{
    int grades[50] =
    { 96,73,62,87,80,63,93,79,71,99,
      82,83,80,97,89,82,93,92,95,89,
      71,97,91,95,63,81,76,98,64,86,
      74,79,98,82,77,68,87,70,75,97,
      71,94,68,87,79, -1 };
    // rest of program goes here ...
    int size;
    for(size = 0; size < 50; size++) { //for loop to determine the size of the array
        if(grades[size] == -1)
            break;
    }
    printf("Standard Deviation: %f\nMean: %f\n", stdev(grades, size), mean(grades, size));   //call functions and output results
    return 0;
}

// function definitions ...
float stdev(int *grades, int size)  //returns standard deviation
{
    //definitions for the calculation of stdev
    float stdev, avg, sum_diff_sq;
    int i;
    avg = mean(grades, size);   //get the mean by calling mean()
    sum_diff_sq = 0;
    for(i = 0; i < size; i++) { //loops through every value in the array
        sum_diff_sq += pow(*(grades + i) - avg, 2); //and computes the square of the difference
    }                                               //between the value and the mean
    stdev = sqrt(sum_diff_sq/i);    //computes the final stdev
    return stdev;
}

float mean(int *grades, int size)   //returns mean
{
    float avg, sum;
    int i;
    sum = 0;
    for(i = 0; i < size; i++) { //loops through every value in the array
        sum += *(grades + i);   //and adds the value to the sum
    }
    avg = sum/size; //divides the sum by the size of the array to find the mean
    return avg;
}
