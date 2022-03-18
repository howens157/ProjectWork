#include <math.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "libgeodist.h"

#define pi 3.14159265358979323846

double deg2rad(double deg) { return (deg * pi / 180); }
double rad2deg(double rad) { return (rad * 180 / pi); }

double geodist(double lat1, double lon1, double lat2, double lon2)
{
    double theta, dist;
    if ((lat1 == lat2) && (lon1 == lon2)) {
        return 0;
    }
    else {
        theta = lon1 - lon2;
        dist = sin(deg2rad(lat1)) * sin(deg2rad(lat2)) + cos(deg2rad(lat1)) * cos(deg2rad(lat2)) *    cos(deg2rad(theta));
        dist = acos(dist);
        dist = rad2deg(dist);
        dist = dist * 60 * 1.1515;
        return (dist);
    }
}

int palindrome(char *s)
{
    char *head = s;
    char *tail = s + strlen(s) - 1;

    while(head < tail && *head == *tail)
    {
            head++;
            tail--;
    }

    if(head >= tail)
            return 1;

    return 0;
}

void setperson(person *p)
{
    p->age = 3500;
    p->name = "Santa Claus";
}

void initpeople(person **people, int numpeople)
{
    int i;
    for(i=0; i<numpeople; i++)
    {    
        person *p = malloc(sizeof(person));
        setperson(p);
        people[i] = p;
    }
}
