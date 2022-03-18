#include <stdio.h>
#include "operfn.h"

int main()
{
    float x, y;

    printf("Enter two non-zero numbers: ");
    scanf("%f %f", &x, &y);

    showinfo(x, y);

    return 0;
}
