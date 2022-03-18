//menucalc.c
//Hayden Owens
//CSE 20311
#include <stdio.h>

//Function Prototypes
void add();
void sub();
void mult();
void div();
int prompt();

int main() {
    int choice; //choice holds the user's input to determine what function to call

    while(1) {  //Loops until user enters 5 to quit
        choice = prompt();  //prompt user
        switch(choice) {    
            case 1: //User enters 1 -> call add
                add();
                break;
            case 2: //User enters 2 -> call sub
                sub();
                break;
            case 3: //User enters 3 -> call mult
                mult();
                break;
            case 4: //User enters 4 -> call div
                div();
                break;
            case 5: //User enters 5 -> say goodbye and return to exit program
                printf("Goodbye!\n");
                return 0;
            default: //User enters any other int, display error and repeat
                printf("Error: please enter a number between 1 and 5.\n");
        }
    }
}

//FUNCTION DEFINITIONS

//Prompts user to enter what operation they would like to perform and returns that choice
int prompt() {
    int choice;
    printf("\nWhat would you like to do?\n");
    printf("1 for addition\n");
    printf("2 for subtraction\n");
    printf("3 for multiplication\n");
    printf("4 for division\n");
    printf("5 to quit\n");
    printf("Enter your choice: ");
    scanf("%d", &choice);
    return choice;
}

void add() { 
    double X, Y;
    printf("Enter two numbers: ");  //Prompt user for two numbers
    scanf("%lf", &X);
    scanf("%lf", &Y);
    printf("Inputs: %g, %g\n", X, Y);
    printf("(%g) + (%g) = %g\n", X, Y, X+Y);    //Output the sum of the inputs
}

void sub() {
    double X, Y;
    printf("Enter two numbers: ");  //Prompt user for two numbers
    scanf("%lf", &X);
    scanf("%lf", &Y);
    printf("Inputs: %g, %g\n", X, Y);
    printf("(%g) - (%g) = %g\n", X, Y, X-Y);    //Output the difference of the inputs
}

void mult() {
    double X, Y;
    printf("Enter two numbers: ");  //Prompt user for two numbers
    scanf("%lf", &X);
    scanf("%lf", &Y);
    printf("Inputs: %g, %g\n", X, Y);
    printf("(%g) * (%g) = %g\n", X, Y, X*Y);    //Output the product of the inputs
}
void div() {
    double X, Y;
    printf("Enter two numbers: ");  //Prompt user for two numbers
    scanf("%lf", &X);
    scanf("%lf", &Y);
    printf("Inputs: %g, %g\n", X, Y);
    printf("(%g) / (%g) = %g\n", X, Y, X/Y);    //Output the quotient of the inputes
}

