/* CSE 20311
 * A simple program that calculates that score of a football game.
 */
#include <stdio.h>

int main()
{
	//Declares variables
	int numTD;
	int numXP;
	int numFG;
	int numSF;
	int totScore;

	//Prompts user and assign variables
	printf("Please enter the number of touchdowns scored: ");
	scanf("%d", &numTD);
	printf("Please enter the number of extra points made: ");
	scanf("%d", &numXP);
	printf("Please enter the number of field goals made: ");
	scanf("%d", &numFG);
	printf("Please enter the number of safeties scored: ");
	scanf("%d", &numSF);

	//Calculate score and output it
	totScore = (numTD * 6) + (numXP * 1) + (numFG * 3) + (numSF * 2);
	printf("The Irish scored %d points!\n", totScore);

	return 0;
}
