// newgrades2.c
#include <stdio.h>

float find_avg(int [], int);

int main()
{
  int grades[50], grd;
  int count = 0;
  FILE *fp;
  char infile[20];

  printf("enter a file name: ");
  scanf("%s", infile);

  fp = fopen(infile, "r");    // connect to the file
  if (!fp) {                  // OR:  if (fp == NULL);
    printf("file %s not found\n", infile);
    return 1;
  }

  while (1) {
    fscanf(fp, "%d", &grd);   // read the next grade
    if(feof(fp)) break;       // end the loop if EOF reached
    grades[count] = grd;      // put the grade in the array
    count++;                  // increment the count
  }

  float avg = find_avg(grades, count);
  printf("there are %d grades\n", count);
  printf("their average is: %.2lf\n", avg);

  return 0;
}

float find_avg(int g[], int sz)
{
  int g_sum = 0;

  int i;
  for (i = 0; i < sz; ++i) 
    g_sum = g_sum + g[i];

  return (float) g_sum / sz;
}

