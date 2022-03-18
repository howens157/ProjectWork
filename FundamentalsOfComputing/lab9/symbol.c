//Hayden Owens
//CSE 20311
//symbol.c

#include "gfx.h"
#include <math.h>

//function prototypes
void drawsq(int SIZE);
void drawcirc(int SIZE);
void drawtri(int SIZE);
void drawpoly(int SIZE, int sides);

int main()
{
    const int SIZE = 50;    //SIZE for the different shapes
    char c; //char to store user key presses
    gfx_open(500, 500, "symbol.c"); //open a 500x500 windows

    while(1)    //loop continuously until user quits
    {
        c = gfx_wait(); //wait for user to press a key
        if(c == 1)  //if the user presses the left mouse button
        {
            drawsq(SIZE);   //draw a square
        }
        else if(c == 'c')   //if the user presses c
        {
            drawcirc(SIZE); //draw a circle
        }
        else if(c == 't')   //if the user presses t
        {
            drawtri(SIZE);  //draw a triangle
        }
        else if('3' <= c && c <= '9')   //if the user presses a number between 3 - 9
        {
            int sides = c - '0';    //subtract '0' to get the key as an int
            drawpoly(SIZE, sides);  //draw a polygon with sides according the number pressed
        }
        else if(c == 27)    //if the user presses esc
        {
            gfx_clear();    //clear the screen
        }
        else if(c == 'q')   //if the user presses q
        {
            return 0;   //quit the program
        }
    }
}

//drawsq draws a square with each side of length SIZE centered at the mouse position
void drawsq(int SIZE)
{
    gfx_color(3, 190, 252); //set the drawing color to blue
    int x = gfx_xpos(); //get the x position of the mouse
    int y = gfx_ypos(); //get the y position of the mouse
    
    //draw 4 lines centered around x,y to make the square
    gfx_line(x-SIZE/2, y-SIZE/2, x-SIZE/2, y+SIZE/2); 
    gfx_line(x-SIZE/2, y+SIZE/2, x+SIZE/2, y+SIZE/2);
    gfx_line(x+SIZE/2, y+SIZE/2, x+SIZE/2, y-SIZE/2);
    gfx_line(x+SIZE/2, y-SIZE/2, x-SIZE/2, y-SIZE/2);
}

//drawcirc draws a circle of diameter SIZE centered at the mouse position
void drawcirc(int SIZE)
{
    gfx_color(255, 255, 255);   //set the color to white
    gfx_circle(gfx_xpos(), gfx_ypos(), SIZE/2); //draw a circle with radius SIZE/2
                                                //centered at the x,y positions of the mouse
    
}

//drawtri draws an equilateral triangle with a base length of SIZE centered at 
//the mouse position
void drawtri(int SIZE)
{
    gfx_color(3, 252, 36);  //set the color to green
    int x = gfx_xpos(); //get the x and y positions of the mouse
    int y = gfx_ypos();
    //draw three lines centered around x,y to make the triangle
    gfx_line(x+SIZE/2, y+(SIZE/2)*tan(30*M_PI/180), x, y-(SIZE/2)/cos(30*M_PI/180));
    gfx_line(x, y-(SIZE/2)/cos(30*M_PI/180), x-SIZE/2, y+(SIZE/2)*tan(30*M_PI/180));
    gfx_line(x-SIZE/2, y+(SIZE/2)*tan(30*M_PI/180), x+SIZE/2, y+(SIZE/2)*tan(30*M_PI/180));
}

//drawpoly draws a polygon with a certain number of sides inscribable in a circle of 
//diameter SIZE
void drawpoly(int SIZE, int sides)
{
    gfx_color(111, 3, 252); //set the color to purple
    int x = gfx_xpos(); //get the x and y positions of the mouse
    int y = gfx_ypos();
    int angle = 90; //start the angle at 90 degrees so that the polygon is pointing the top of the screen
    int i;
    int x1, y1, x2, y2; //create ints for the start and end of each line
    for(i = 0; i < sides; i++)  //loop once for each side
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
