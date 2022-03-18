// rectangle2.c
#include <stdio.h>

// function prototypes go here
float find_perim(float, float);
float find_area(float, float);
void display(float, float);


int main()
{
    float len, wid;
    float perim, area;

    printf("enter the length: ");
    scanf("%f", &len);
    printf("enter the width: ");
    scanf("%f", &wid);

    perim = find_perim(len, wid);   // call the find_perim function
    area = find_area(len, wid);     // call the find_area function

    display(perim, area);           // call the display function    

    return 0;
}

// function definitions go here
float find_perim(float length, float width)
{
    float perim = 2*(length + width);
    return perim;
}

float find_area(float length, float width)
{
    float area = length*width;
    return area;
}

void display(float perim, float area)
{
    printf("the perimeter is: %.2f\n", perim);
    printf("the area is: %.2f\n", area);
}
