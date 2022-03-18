/* Hayden Owens
 * 2/17/2022
 * Operating Systems - Project 3
 *
 * fractalthread.c
 *
 * This program displays the Mandelbrot set using multithreading
 */

#include "gfx.h"

#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <errno.h>
#include <string.h>
#include <complex.h>
#include <pthread.h>

int numThreads;

//a lock for drawing to the screen
pthread_mutex_t lock;

//arguments to send to the thread function
typedef struct {
    int pixMinX;
    int pixMaxX;
    int pixMinY;
    int pixMaxY;
    double xmin;
    double xmax;
    double ymin;
    double ymax;
    int maxiter;
} t_args;

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

// compute_section is the function that every created thread will run.
// It computes a given section of rows of the full image and then returns
void * compute_section(void *args)
{
    t_args *myArgs = (t_args*)(args);
   
    int width = gfx_xsize();
	int height = gfx_ysize();

    // For every pixel i,j, in the section
    int i, j;
	for(j = myArgs->pixMinY; j <= myArgs->pixMaxY; j++) {
		for(i = myArgs->pixMinX; i <= myArgs->pixMaxX; i++) {

			// Scale from pixels i,j to coordinates x,y
			double x = myArgs->xmin + i*(myArgs->xmax - myArgs->xmin)/width;
			double y = myArgs->ymin + j*(myArgs->ymax - myArgs->ymin)/height;

			// Compute the iterations at x,y
			int iter = compute_point(x,y,myArgs->maxiter);

			// Convert a iteration number to an RGB color scaled between
			// two chosen colors
			double scalar = (double)iter/myArgs->maxiter;
            color_t color1 = {217, 108, 134};
            color_t color2 = {255, 209, 220};

            // changing color and drawing a point must be done atomically
            // or else one thread courl change the color, be preempted, and then
            // draw the point after the color has been changed again
            pthread_mutex_lock(&lock);
            // set the color between color1 and color2
			gfx_color(color2.r + (color1.r-color2.r)*scalar, color2.g + (color1.g-color2.g)*scalar, color2.b + (color1.b-color2.b)*scalar);
			// Plot the point on the screen.
			gfx_point(i,j);
            pthread_mutex_unlock(&lock);
		}
	}

    return 0;
}

/*
Compute an entire image, writing each point to the given bitmap.
Scale the image to the range (xmin-xmax,ymin-ymax).
*/

void compute_image( double xmin, double xmax, double ymin, double ymax, int maxiter )
{
	int i;

	int width = gfx_xsize();
	int height = gfx_ysize();
    
    //set up numThreads phtread_ts and t_argss
    pthread_t tid[numThreads];
    t_args args[numThreads];

    //set up args for each thread
    for(i = 0; i < numThreads; i++) {
        // pixel boundaries of each section
        args[i].pixMinX = 0;
        args[i].pixMaxX = width-1;
        args[i].pixMinY = (height/numThreads) * i;
        args[i].pixMaxY = (height/numThreads) * (i+1)-1;
        // computation args
        args[i].xmin = xmin;
        args[i].xmax = xmax;
        args[i].ymin = ymin;
        args[i].ymax = ymax;
        args[i].maxiter = maxiter;
    }

    //create threads
    for(i = 0; i < numThreads; i++) {
        int r;
        r = pthread_create(&tid[i], 0, compute_section, &args[i]);
        if(r != 0) {
            printf("Could not create thread %d\n", i);
        }
    }

    //join threads
    for(i = 0; i < numThreads; i++) {
        int r;
        void *rval;
        r = pthread_join(tid[i], &rval);
        if(r != 0) {
            printf("Could not join thread %d\n", i);
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

    //initialize numThreads
    numThreads = 8;
    int rc = pthread_mutex_init(&lock, NULL);
    if(rc != 0) {
        printf("lock not initialized\n");
    }

	// The initial boundaries of the fractal image in x,y space.

	double xmin=-1.5;
	double xmax= 0.5;
	double ymin=-1.0;
	double ymax= 1.0;

	// Maximum number of iterations to compute.
	// Higher values take longer but have more detail.
	int maxiter=200;

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
        // if y is pressed, decrease maxiter by a constant
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
        // if right click, recenter the picture at the click, and zoom in
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
        // if 1-8 is pressed, set numThreads to that number
        else if(c >= '1' && c <= '8') {
            numThreads = c - '0';
        } 
        printf("coordinates: %lf %lf %lf %lf %d\n", xmin, xmax, ymin, ymax, maxiter);
	}
	return 0;
}
