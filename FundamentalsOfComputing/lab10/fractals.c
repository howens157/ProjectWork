//Hayden Owens
//CSE 20311
//fractals.c

#include "gfx.h"
#include <stdbool.h>
#include <math.h>

// function prototypes
void sierpinski(int x1, int y1, int x2, int y2, int x3, int y3);
void drawTriangle(int x1, int y1, int x2, int y2, int x3, int y3);
void shrinkingsquares(int x1, int y1, int x2, int y2, int x3, int y3, int x4, int y4);
void drawSquare(int x1, int y1, int x2, int y2, int x3, int y3, int x4, int y4);
void spiralsquares(int x, int y, float size, float radius, float maxrad, float angle);
void circularlace(int x, int y, int radius);
void snowflake(int x, int y, int size);
void tree(int x1, int y1, float angle, int length);
void fern(int x1, int y1, float angle, int length);
void spiralofspirals(int x, int y, float radius, float angle);

int main() {
    char c; //char to store user key press
     
    bool loop = true;   //bool to store whether or not the program should keep running
    //Window sizes
    const int Xmon = 600;
    const int Ymon = 600;
    //open window
    gfx_open(Xmon,Ymon,"Fun Fractals");

    while (loop) {  //loop until user sets loop to false
        c = gfx_wait(); //wait for key press
        gfx_clear();    //clear window
        switch (c) {    //switch will call correct function according to the key press
            case '1': // Sierpinski Triangle   
                sierpinski(5, 5, Xmon/2, Ymon-5, Xmon-5, 5); //fuzziness and errors in small triangles
                break;
            case '2': // Shrinking Squares  
                shrinkingsquares(Xmon/4, Ymon/4, Xmon/4, 3*Ymon/4, 3*Xmon/4, 3*Ymon/4, 3*Xmon/4, Ymon/4); 
                break;
            case '3': // Spiral Squares
                spiralsquares(Xmon/2, Ymon/2, 1, 1, Xmon, 0);
                break;
            case '4': // Circular Lace
                circularlace(Xmon/2, Ymon/2, Xmon/3);
                break;
            case '5': // Snowflake
                snowflake(Xmon/2, Ymon/2, Ymon/3);
                break;
            case '6': // Tree
                tree(Xmon/2, Ymon-5, 3*M_PI_2, Ymon*0.32);
                break;
            case '7': // Fern
                fern(Xmon/2, Ymon-5, 3*M_PI_2, Ymon*0.6);
                break;
            case '8': // Spiral of Spirals 
                spiralofspirals(Xmon/2, Ymon/2, Xmon, 0);
                break;
            case 'q': //if the user presses q, don't loop again
                loop = false;
            default:
                break;
    }
  }

  return 0;
}

//sierpinski() takes the x, y coordinates of the original triangle to start from
void sierpinski(int x1, int y1, int x2, int y2, int x3, int y3)
{
    if(abs(x2-x1) < 2) return;  //base case

    drawTriangle(x1, y1, x2, y2, x3, y3);   //draw the triangle

    //then call sierpinski() on 3 segmented triangles within the current triangle
    sierpinski(x1, y1, (x1 + x2)/2, (y1 + y2)/2, (x1 + x3)/2, (y1 + y3)/2);
    sierpinski((x1 + x2)/2, (y1 + y2)/2, x2, y2, (x2 + x3)/2, (y2 + y3)/2);
    sierpinski((x1 + x3)/2, (y1 + y3)/2, (x2 + x3)/2, (y2 + y3)/2, x3, y3);
}
 
void drawTriangle(int x1, int y1, int x2, int y2, int x3, int y3)
{
    //draw three lines to create the triangle
    gfx_line(x1, y1, x2, y2);
    gfx_line(x2, y2, x3, y3);
    gfx_line(x3, y3, x1, y1);
}

//shrinkingsquares takes the x, y coordinates of the original square to start from
void shrinkingsquares(int x1, int y1, int x2, int y2, int x3, int y3, int x4, int y4)
{
    int length = x4-x1; //length of one side of the square
    if(abs(length) < 2) return; //base case
    
    drawSquare(x1, y1, x2, y2, x3, y3, x4, y4); //draw the square

    float scale = 0.22*length;  //scale by which to decrease the square size with each level of recursion
    
    //then call shrinkingsquares() on each corner of the current square with a smaller size square
    shrinkingsquares(x1 - scale, y1 - scale, x1 - scale, y1 + scale, x1 + scale, y1 + scale, x1 + scale, y1 - scale);
    shrinkingsquares(x2 - scale, y2 - scale, x2 - scale, y2 + scale, x2 + scale, y2 + scale, x2 + scale, y2 - scale);
    shrinkingsquares(x3 - scale, y3 - scale, x3 - scale, y3 + scale, x3 + scale, y3 + scale, x3 + scale, y3 - scale);
    shrinkingsquares(x4 - scale, y4 - scale, x4 - scale, y4 + scale, x4 + scale, y4 + scale, x4 + scale, y4 - scale);
}

//sprialsquares() takes the x, y coordinates to center the spiral around, the size of the square, the radius at which
//to draw the square, the max radius before returning, and the angle with which to draw the square
void spiralsquares(int x, int y, float size, float radius, float maxrad, float angle)
{
    if(radius > maxrad) return; //base case

     //calculate the point to center the current square at
    int x1 = x + radius*cos(angle);
    int y1 = y + radius*sin(angle);

    //draw the square of length side centered at x1, y1
    drawSquare(x1 - size/2, y1 - size/2, x1 - size/2, y1+size/2, x1 + size/2, y1 + size/2, x1 + size/2, y1 - size/2);

    //call spiralsquares() with the same center and maxrad, and an increased size and radius, and incremented angle
    spiralsquares(x, y, size*1.14, radius*1.17, maxrad, angle + M_PI_4*.9);
}


void drawSquare(int x1, int y1, int x2, int y2, int x3, int y3, int x4, int y4)
{
    //draw 4 lines to create the square
    gfx_line(x1, y1, x2, y2);
    gfx_line(x2, y2, x3, y3);
    gfx_line(x3, y3, x4, y4);
    gfx_line(x4, y4, x1, y1);
}

//circularlace() take the x, y coordinates to center the first circle on and the original radius
void circularlace(int x, int y, int radius)
{
    if(radius < 2) return;  //base case

    gfx_circle(x, y, radius);   //draw the circle

    int i;
    int num = 6;
    for(i = 0; i < num; i++)  //loop once for each circle to be drawn
    {
        //call circularlace() at 6 points evenly spaced around the circumference of the current circle with a smaller radius
        circularlace(x+radius*cos(2*M_PI/num*i), y+radius*sin(2*M_PI/num*i), radius/3);
    }
}

//snowflake() takes the x, y coordinates of the point to start drawing from and the initial size of the lines to draw
void snowflake(int x, int y, int size)
{
    if(size < 1) return;    //base case
    
    int i;
    int num = 5;    //number of lines to draw originating at each point
    float angle = M_PI_2;   //angle to orient the snowflake vertically
    for(i = 0; i < num; i++)    //loop once for each line to be drawn
    {
        //draw lines originating from x, y oriented at evenly spaced angles
        gfx_line(x, y, x+size*cos(angle+2*M_PI/num*i), y+size*sin(angle+2*M_PI/num*i));
        //and then call snowflake() at the end of each line with a smaller size
        snowflake(x+size*cos(angle+2*M_PI/num*i), y+size*sin(angle+2*M_PI/num*i), size*0.36);
    }   
}

//tree() takes the x, y coordinates of the point to start drawing from, the angle with which to orient the drawing, and the length of the branch
void tree(int x1, int y1, float angle, int length)
{
    if(length < 0.5) return;    //base case

    //calculate the end point of the current branch
    int x2 = x1 + length*cos(angle);
    int y2 = y1 + length*sin(angle);
    //draw the branch
    gfx_line(x1, y1, x2, y2);

    float branchangle = 35*M_PI/180;    //angle with which each new line will branch from the previous lines
    
    //call tree() twice at the end of the current branch with evenly spaced angles and a shorter length
    tree(x2, y2, angle + branchangle, length*.70);
    tree(x2, y2, angle - branchangle, length*.70);
}

//fern() takes the x, y coordinates of the point to start drawing from, the angle with which to orient the drawing, and the length of the branch
void fern(int x1, int y1, float angle, int length)
{
    if(length < 2) return; //base case

    //calculate the end point of the current branch
    int x2 = x1 + length*cos(angle);
    int y2 = y1 + length*sin(angle);
    //draw the branch
    gfx_line(x1, y1, x2, y2);

    float branchangle = 35*M_PI/180;    //angle with which line branches from the previous line

    int i;
    int leaves = 4;
    for(i = 1; i <= leaves; i++)    //loop once for each pair of leaves
    {
        //draw new pairs of lines at evenly separated angles 1/4, 2/4, 3/4, and 4/4 of the way up the previous branch
        fern(x1 + length*i/leaves*cos(angle), y1 + length*i/leaves*sin(angle), angle - branchangle, length/3);
        fern(x1 + length*i/leaves*cos(angle), y1 + length*i/leaves*sin(angle), angle + branchangle, length/3);
    }
}

//spiralofspirals() takes the x, y coordinates to center the spiral around and the initial radius and angle to draw at
void spiralofspirals(int x, int y, float radius, float angle)
{
    if(radius < 1) return;  //base case

    //calculate the next point to draw at
    int x2 = x + radius*cos(angle);
    int y2 = y + radius*sin(angle);

    gfx_point(x2, y2);  //draw the point
    //then start a new spiral centered at that point with a smaller radius but the same angle
    spiralofspirals(x2, y2, radius*0.3, angle);
    //and continue the spiral centered at the current point with a slightly smaller radius and an incremented angle
    spiralofspirals(x, y, radius*.92, angle+M_PI_4*0.6);
}
