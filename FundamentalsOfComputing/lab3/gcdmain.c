// gcdmain.c
// Hayden Owens
// CSE 20311
#include <stdio.h>
#include <math.h>

// Function prototype
int getgcd(int, int);

int main()
{
    int num1, num2, result;
    // Prompt user and store inputs
    printf("Please enter the first integer: ");
    scanf("%d", &num1);
    printf("Please enter the second integer: ");
    scanf("%d", &num2);

    // Call getgcd and store result
    result = getgcd(num1, num2);
    printf("The GCD is %d.\n", result); // Display result

    return 0;
}

// Function defintiion
// I used the Binary GCD algorithm
int getgcd(int A, int B)
{ 
    int D = 0;
    int swapVar;
    int C;
    while(A != B) { 
        if((A%2 == 0) && (B%2 == 0)) {  // If A and B are both even
            A /= 2;                     // divide them both by two
            B /= 2;
            D++;                        // and increment D
        }
        else if((A%2 == 0) && (B%2 == 1)) { // If either A or B is even
            A /= 2;                         // divide it by 2 and continue
        } 
        else if((A%2 == 1) && (B%2 == 0)) {
            B /= 2;
        } 
        else if((A%2 == 1) && (B%2 == 1)) { // If A and B are both odd
            if(A < B) {                     // Make sure A > B
                swapVar = A;
                A = B;
                B = swapVar;
            }
            C = A - B;                      // Define C to be A - B
            A = C/2;                        // and assign it to A then continue
        }
        printf("%d %d\n", A, B);
    }
    return A * pow(2,D);    // The result is defined to be A*2^D
}
