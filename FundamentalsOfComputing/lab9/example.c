// a simple example 

#include "gfx.h"

int main()
{
  const int xsize = 500, ysize = 300;
  char c;

  // Open a new window for drawing.
  gfx_open(xsize, ysize, "Example Graphics Program");

  // Set the current drawing color 
  gfx_color(0,200,100);

  // Draw a triangle on the screen.
  gfx_line(100,100,200,100);
  gfx_line(200,100,150,150);
  gfx_line(150,150,100,100);

  // change color, and draw a circle
  gfx_color(200,100,50);
  gfx_circle(300,150,40);

  while(1) {
    // Wait for the user to press a character.
    c = gfx_wait();

    // Quit if it is the letter q.
    if(c == 'q') break;
  }

  return 0;
}

