//Hayden Owens
//CSE 20311
//bounce.c

#include "gfx.h"
#include <unistd.h>
#include <stdlib.h>
#include <time.h>

//function prototypes
void colorrand();
void drawball(int x, int y, int radius);
void move(int *x, int *y, int *vx, int *vy, int Xmon, int Ymon, int radius);

int main()
{
    //allocate memory for x and y positions and x and y velocities
    int *x = (int*)malloc(sizeof(int));
    int *y = (int*)malloc(sizeof(int));
    int *vx = (int*)malloc(sizeof(int));
    int *vy = (int*)malloc(sizeof(int));
    int vmax = 5;   //set vmax to 5
    srand(time(NULL));  //seed rand()
    //set values for the width and height of the monitor
    const int Xmon = 1000;
    const int Ymon = 700;
    gfx_open(Xmon, Ymon, "bounce.c");   //open the window
    int radius = 50;    //set the radius of the ball
    //set the initial location of the ball to the center of the window
    *x = Xmon/2;    
    *y = Ymon/2;
    //randomize vx and vy between -vmax and +vmax
    *vx = (rand()%(2*vmax-1)) - vmax;
    *vy = (rand()%(2*vmax-1)) - vmax;
    //randomize the drawing color
    colorrand();
    char c; //char to store user input
    //loop until user quits
    while(1)
    { 
        move(x, y, vx, vy, Xmon, Ymon, radius); //update position of the ball
        gfx_clear();    //clear the screen
        drawball(*x, *y, radius);   //draw the ball at the current position
        gfx_flush();    //flush the draw commands to the screen
        usleep(10000); 
        
        if(gfx_event_waiting()) //if the user has pressed a key
        {
            c = gfx_wait(); //read in the key
            if(c == 1)  //if the user pressed the left mouse button
            {
                //change the position to the position of the mouse
                *x = gfx_xpos();
                *y = gfx_ypos(); 
                //randomize the velocity in both directions
                *vx = (rand()%(2*vmax-1)) - vmax;
                *vy = (rand()%(2*vmax-1)) - vmax;
                //randomize the color
                colorrand();
            }
            else if(c == 'q')   //if the user presses q, quit the program
                return;
        }
    }
}

//colorrand will set the drawing color to a random color
void colorrand()
{
    //call gfx_color() with three random numbers between 0 and 255
    gfx_color(rand()%256, rand()%256, rand()%256);
}

//drawball will draw a solid ball with a given radius at a given position
void drawball(int x, int y, int radius)
{
    int i;
    for(i = radius; i > 0; i -= 2)  //draw the ball by drawing tightly packed
    {                               //concentric circles
        gfx_circle(x, y, i);
    }
}

//move will check for collisions with the wall and move the location of the ball
void move(int *x, int *y, int *vx, int *vy, int Xmon, int Ymon, int radius)
{
    if(*x < radius) //if the x position is within radius of the left wall 
    {
        *vx *= -1;  //bounce by flipping the x velocity
        colorrand();    //and set the color to a new random color
        if(*x + *vx < radius)   //if velocity won't get the ball out of the wall    
            *x = radius;    //force the ball to the correct distance so it won't get stuck
    }
    //repeat the above process for all 3 remaining walls
    else if(*x > Xmon - radius)
    {
        *vx *= -1;
        colorrand();
        if(*x + *vx > Xmon - radius)
            *x = Xmon - radius;
    }
    if(*y < radius)
    {
        *vy *= -1;
        colorrand();
        if(*y + *vy < radius)
            *y = radius;
    }
    else if(*y > Ymon - radius)
    {
        *vy *= -1;
        colorrand();
        if(*y + *vy > Ymon - radius)
            *y = Ymon - radius;
    }

    //update the x and y position of the ball by adding the velocities
    *x += *vx;
    *y += *vy;
}
