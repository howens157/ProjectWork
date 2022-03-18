//Hayden Owens
//CSE 20311
//funanim.c

#include "gfx.h"
#include <math.h>
#include <unistd.h>
#include <stdlib.h>
#include <time.h>
#include <stdio.h>
#include <stdbool.h>

//const ints for monitor size
const int Xmon = 500;
const int Ymon = 500;

//function prototypes   
void drawcirc(int SIZE);
void drawpoly(int SIZE, int sides, float offset);
void colorrand();

int main()
{
    srand(time(NULL));  //seed rand()
    //initialize vars
    const int SIZE = 500;   //size const for drawing shapes
    char c; //char for storing user input
    float offset = 0.0; //initial offset for rotation
    float angv = 1.0;   //initial angular velocity
    int i, j;   //for loops
    int maxsides = 5;   //initial maxsides
    //open a window
    gfx_open(Xmon, Ymon, "funanim.c");
    while(1)    //loop until user quits
    {
        offset += angv; //update offset by angv (rotate the drawing)
        if(((int)offset)%10 == 0)
            colorrand();
        //two for loops to draw polygons nested within each other
        for(i = SIZE/2; i > 0; i /= 2)
        {
            drawcirc(i);    //for each size, draw a circle
            for(j = 3; j <= maxsides; j++)  //and draw polygons with 3-maxsides sides
            {
                drawpoly(i*2, j, offset);
            } 
        }
        gfx_flush();    //flush draw commands to window
        usleep(10000);
        if(gfx_event_waiting()) //if the user has pressed a key
        {
            c = gfx_wait(); //read in the key
            if(c == 1)  //if the user pressed the left mouse button
                angv *= -1; //flip the rotation
            else if(c == 'd')   //if the user pressed d
                angv += 0.2;    //add 0.2 to the rotation   
            else if(c == 'a')   //if the user pressed a
                angv -= 0.2;    //subtract 0.2 from the rotation
            else if(c >= '3' && c <= '9')   //if the user pressed between 3 and 9
                maxsides = c - '0'; //set maxsides to the user's input
            else if(c == 'q')   //if the user pressed q
                return 0;   //quit the program
        }
    }
}

//drawcirc draws a circle of radius SIZE centered on the window
void drawcirc(int SIZE)
{
    gfx_circle(Xmon/2, Ymon/2, SIZE);
    
}

//drawpoly draws a polygon with a given number of sides rotated by a given offset and 
//incscribable in a circle of diameter sides
void drawpoly(int SIZE, int sides, float offset)
{
    float angle = 90+offset;    //start the angle at 90 degrees plus the offset
    //set x and y to be the center of the window
    float x = Xmon/2;   
    float y = Ymon/2;
    int i;
    float x1, y1, x2, y2;   //create ints for the start and end of each line
    for(i = 0; i < sides; i++)
    {
        //calculate the start point of the line
        x1 = x-SIZE/2*cos(angle*M_PI/180);
        y1 = y-SIZE/2*sin(angle*M_PI/180);
        //increment the angle depending on the number of sides
        angle += 360/sides;
        //calculate the end point of the line
        x2 = x-SIZE/2*cos(angle*M_PI/180); 
        y2 = y-SIZE/2*sin(angle*M_PI/180);
        //draw the line
        gfx_line(x1, y1, x2, y2); 
    }
}

//colorrand will set the drawing color to a random color
void colorrand()
{
    //call gfx_color() with three random numbers between 0 and 255
    gfx_color(rand()%256, rand()%256, rand()%256);
}

