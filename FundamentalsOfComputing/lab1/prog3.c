/*CSE 20311 - Hayden Owens
 * Calculates the interest that is accumulated based on the compound
 * interest formula.
 */
#include <stdio.h>
#include <math.h>

int main()
{
	//Declares variables
	double P;
	double r;
	double n;
	double t;
	double total;

	//Prompts user and assigns variables
	printf("Please enter the principal: ");
	scanf("%lf", &P);
	printf("Please enter the interest rate as a decimal: ");
	scanf("%lf", &r);
	printf("Please enter the number of years that the interest accumulates: ");
	scanf("%lf", &t);
	printf("Please enter the number of times per year that the interest compounds: ");
	scanf("%lf", &n);

	//Calculates the total including initial principal and accumulated interest and outputs result
	total = P*pow((1 + r/(n)), (n*t));
	printf("Your total is $%lf.\n", total);

	return 0;
}
