// rectangle.c
#include <stdio.h>

typedef struct {
  float height;
  float width;
  float area;
  float perimeter;
} Rectangle; 

int readvalues(FILE *, Rectangle []);

float find_area(Rectangle);
float find_perim(Rectangle);
void display(Rectangle);

int main()
{
  FILE *fp = fopen("values.txt", "r");
  Rectangle rectangle_arr[20]; 
   
  int count = readvalues(fp, rectangle_arr);

  int i;
  for (i = 0; i < count; i++) {
    rectangle_arr[i].area = find_area(rectangle_arr[i]);
    rectangle_arr[i].perimeter = find_perim(rectangle_arr[i]);
  }

  for (i = 0; i < count; i++) {
    display(rectangle_arr[i]);
  }

  return 0; 
}

int readvalues(FILE *fp, Rectangle arr[])
{
  int n = 0;
  while (1) {
    fscanf(fp, "%f %f", &arr[n].height, &arr[n].width);
    if (feof(fp)) break;
    n++;
  }
  return n;
}

float find_area(Rectangle r)
{ return r.height*r.width; }

float find_perim(Rectangle r)
{ return 2*(r.height + r.width); }

void display(Rectangle r)
{
  printf("rectangle is %g x %g\n", r.height, r.width);
  printf("  its area is %g\n", r.area);
  printf("  its perimeter is %g\n", r.perimeter);
}

