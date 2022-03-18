// cstringsdemo.c
#include <stdio.h>
#include <string.h>
 
#define MAXLENGTH 30

int main() 
{
  char states[][MAXLENGTH] = 
     {"Indiana", "Michigan", "Ohio", "Illinois", "New York", "Texas"};
  const int size = sizeof(states)/MAXLENGTH/sizeof(char);
  int i, j;

  printf("the states are:\n");
  for (i = 0; i < size; i++) {
     printf(" - %s\n", states[i]);
  }

  printf("displaying the states with a space between letters:\n");
  for (i = 0; i < size; i++) {
     printf(" - ");
     for (j = 0; j < strlen(states[i]); j++) {
        printf("%c ", states[i][j]);
     }
     printf("\n");
  }

  return 0;
}

