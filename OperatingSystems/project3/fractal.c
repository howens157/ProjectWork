/* Hayden Owens
 * 2/17/2022
 * Operating Systems - Project 3
 *
 * fractal.c
 *
 * This program displays the Mandelbrot set
 */

#include "gfx.h"

#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <errno.h>
#include <string.h>
#include <complex.h>

//color struct to make changing the color scheme quicker
typedef struct {
    int r;
    int g;
    int b;
} color_t;

color_t red;
color_t orange;
color_t yellow;
color_t green;
color_t blue;
color_t indigo;
color_t violet;

/*
Compute the number of iterations at point x, y
in the complex space, up to a maximum of maxiter.
Return the number of iterations at that point.

This example computes the Mandelbrot fractal:
z = z^2 + alpha

Where z is initially zero, and alpha is the location x + iy
in the complex plane.  Note that we are using the "complex"
numeric type in C, which has the special functions cabs()
and cpow() to compute the absolute values and powers of
complex values.
*/

static int compute_point( double x, double y, int max )
{
	double complex z = 0;
	double complex alpha = x + I*y;

	int iter = 0;

	while( cabs(z)<4 && iter < max ) {
		z = cpow(z,2) + alpha;
		iter++;
	}

	return iter;
}

/*
Compute an entire image, writing each point to the given bitmap.
Scale the image to the range (xmin-xmax,ymin-ymax).
*/

void compute_image( double xmin, double xmax, double ymin, double ymax, int maxiter )
{
	int i,j;

	int width = gfx_xsize();
	int height = gfx_ysize();

	// For every pixel i,j, in the image...

	for(j=0;j<height;j++) {
		for(i=0;i<width;i++) {

			// Scale from pixels i,j to coordinates x,y
			double x = xmin + i*(xmax-xmin)/width;
			double y = ymin + j*(ymax-ymin)/height;

			// Compute the iterations at x,y
			int iter = compute_point(x,y,maxiter);

			// Convert a iteration number to an RGB an RGB color scaled between
			// two chosen colors
			double scalar = (double)iter/maxiter;
            color_t color1 = {217, 108, 134};
            color_t color2 = {255, 209, 220};

			// set the color between color1 and color2
			gfx_color(color2.r + (color1.r-color2.r)*scalar, color2.g + (color1.g-color2.g)*scalar, color2.b + (color1.b-color2.b)*scalar);

			// Plot the point on the screen.
			gfx_point(i,j);
		}
	}
}

int main( int argc, char *argv[] )
{
    //initialize colors
    red.r = 255;
    red.g = 0;
    red.b = 0;
    orange.r = 255;
    orange.g = 127;
    orange.b = 0;
    yellow.r = 255;
    yellow.g = 255;
    yellow.b = 0;
    green.r = 0;
    green.g = 255;
    green.b = 0;
    blue.r = 0;
    blue.g = 0;
    blue.b = 255;
    indigo.r = 75;
    indigo.g = 0;
    indigo.b = 130;
    violet.r = 148;
    violet.g = 0;
    violet.b = 211;

	// The initial boundaries of the fractal image in x,y space.

	double xmin=-1.5;
	double xmax= 0.5;
	double ymin=-1.0;
	double ymax= 1.0;

	// Maximum number of iterations to compute.
	// Higher values take longer but have more detail.
	int maxiter=50;

	// Open a new window.
	gfx_open(640, 640,"Mandelbrot Fractal");

	// Show the configuration, just in case you want to recreate it.
	printf("coordinates: %lf %lf %lf %lf\n",xmin,xmax,ymin,ymax);

	// Fill it with a dark blue initially.
	gfx_clear_color(0,0,255);
	gfx_clear();

	// Display the fractal image
	compute_image(xmin,xmax,ymin,ymax,maxiter);

    double currDimenX, currDimenY;
	while(1) {
		// Wait for a key or mouse click.
		int c = gfx_wait();

		// Quit if q is pressed.
		if(c == 'q') {
            exit(0);
        }
        // if d is pressed, move right
        else if(c == 'd') {
            currDimenX = xmax-xmin;
            xmin += currDimenX*0.2;
            xmax += currDimenX*0.2;
            compute_image(xmin, xmax, ymin, ymax, maxiter);
        }
        // if a is pressed, move left
        else if(c == 'a') {
            currDimenX = xmax-xmin;
            xmin -= currDimenX*0.2;
            xmax -= currDimenX*0.2;
            compute_image(xmin, xmax, ymin, ymax, maxiter);
        }
        // if s is pressed, move down
        else if(c == 's') {
            currDimenY = ymax-ymin;
            ymin += currDimenY*0.2;
            ymax += currDimenY*0.2;
            compute_image(xmin, xmax, ymin, ymax, maxiter);
        }
        // if w is pressed, move up
        else if(c == 'w') {
            currDimenY = ymax-ymin;
            ymin -= currDimenY*0.2;
            ymax -= currDimenY*0.2;
            compute_image(xmin, xmax, ymin, ymax, maxiter);
        }
        // if r is pressed, zoom in
        else if(c == 'r') {
            currDimenX = xmax-xmin;
            currDimenY = ymax-ymin;
            xmin += currDimenX*0.2;
            xmax -= currDimenX*0.2;
            ymin += currDimenY*0.2;
            ymax -= currDimenY*0.2;
            compute_image(xmin, xmax, ymin, ymax, maxiter);
        }
        // if f is pressed, zoom out
        else if(c == 'f') {
            currDimenX = xmax-xmin;
            currDimenY = ymax-ymin;
            xmin -= currDimenX*0.2;
            xmax += currDimenX*0.2;
            ymin -= currDimenY*0.2;
            ymax += currDimenY*0.2;
            compute_image(xmin, xmax, ymin, ymax, maxiter);
        }
        // if t is pressed, increase maxiter by a scalar
        else if(c == 't') {
            maxiter += (int)(maxiter*0.5);
            compute_image(xmin, xmax, ymin, ymax, maxiter);
        }
        // if g is pressed, decrease maxiter by a scalar
        else if(c == 'g') {
            maxiter -= (int)(maxiter*0.5);
            compute_image(xmin, xmax, ymin, ymax, maxiter);
        }
        // if y is pressed, increase maxiter by a constant
        else if(c == 'y') {
            maxiter += 10;
            compute_image(xmin, xmax, ymin, ymax, maxiter);
        }
        // if h is pressed, decrease maxiter by a constant
        else if(c == 'h') {
            maxiter -= 10;
            if(maxiter < 1) {
                maxiter = 1;
            }
            compute_image(xmin, xmax, ymin, ymax, maxiter);
        }
        // if left click, recenter the picture at the click
        else if(c == 1) {
            // get location of click and dimensions of screen
            int xPos = gfx_xpos();
            int yPos = gfx_ypos();
            int width = gfx_xsize();
            int height = gfx_ysize();
            currDimenX = xmax-xmin;
            currDimenY = ymax-ymin;
            double offsetX = (xPos - width/2)/(double)(width)*currDimenX;
            double offsetY = (yPos - height/2)/(double)(height)*currDimenY;
            xmin += offsetX;
            xmax += offsetX;
            ymin += offsetY;
            ymax += offsetY;
            compute_image(xmin, xmax, ymin, ymax, maxiter);
        }
        // if left click, recenter the picture at the click, and zoom in
        else if(c == 3) {
            int xPos = gfx_xpos();
            int yPos = gfx_ypos();
            int width = gfx_xsize();
            int height = gfx_ysize();
            currDimenX = xmax-xmin;
            currDimenY = ymax-ymin;
            double offsetX = (xPos - width/2)/(double)(width)*currDimenX;
            double offsetY = (yPos - height/2)/(double)(height)*currDimenY;
            xmin += offsetX;
            xmax += offsetX;
            ymin += offsetY;
            ymax += offsetY;
            xmin += currDimenX*0.2;
            xmax -= currDimenX*0.2;
            ymin += currDimenY*0.2;
            ymax -= currDimenY*0.2;
            compute_image(xmin, xmax, ymin, ymax, maxiter);
        }
        printf("coordinates: %lf %lf %lf %lf %d\n", xmin, xmax, ymin, ymax, maxiter);
	}
	return 0;
}
