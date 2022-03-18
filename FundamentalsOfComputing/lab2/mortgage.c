#include <stdio.h>

int main ()
{  
    //inititalize variables
    float init, rate, monthly, totPayment, balance, monthlyRate;
    int totMonths, months, years;

    //set variables to -1 for the first time through while loops
    init = -1;
    rate = -1;
    monthly = -1;

    while(init < 0){
        printf("Please enter the initial amount of the loan: "); //prompt user
        scanf("%f", &init); //assign variable
        if(init < 0) //check if valid, if not, send error message
            printf("Please enter a positive initial amount.\n");
    }
    
    while(rate < 0) {
        printf("Please enter the annual interest rate as a decimal: "); //prompt user
        scanf("%f", &rate); //assign varialbe
        if(rate < 0) //check if valid, if not, send error message
            printf("Please enter a positive interest rate.\n");
        monthlyRate = rate*1/12; //assign value to monthlyRate
    }
    
    while(monthly < 0){
        printf("Please enter the desired monthly payment: "); //prompt user
        scanf("%f", &monthly); //assignm variable
        if(monthly < 0) //check if negative, send error message if required
            printf("Please enter a positive monthly payment.\n");
        else if(monthly < init*monthlyRate){ //check if the monthly payment is large enough
            printf("Your desired payment is too low. Please try again.\n"); //error message if monthly too small
            monthly = -1; //reset monthly for while loop
        }      
    }
    printf("%5s%14s%15s%13s\n", "Month", "Payment", "Interest", "Balance"); //print header
    
    //assign values to months and balance
    months = 1; 
    balance = init;

    //create table and keep going until balance is less than monthly payment
    while(balance > monthly){
        printf("%-5d       $%-13.2f$%-13.2f$%-13.2f\n", months, monthly, monthlyRate*balance, balance - monthly + monthlyRate*balance);
        balance = balance - monthly + monthlyRate*balance; //update balance
        months++;
        totPayment += monthly; //update totPayment to keep track of the total amount paid
    }

    //print row for the final month of payments
    printf("%-5d       $%-13.2f$%-13.2f$%-13.2f\n", months, balance + monthlyRate*balance, monthlyRate*balance, 0);
    totPayment += balance + monthlyRate*balance; //Add final payment to totPayment

    //Output total payment on the loan and time it took to pay it off
    printf("You payed a total of %.2f over %d years and %d months.\n", totPayment, months/12, months%12);
    
}
