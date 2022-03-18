# C Milestone Part 1 - M3A

Go to the class public directory and look for a folder called c_simg_ref.  Go in that folder.  Now run:

    $ LD_LIBRARY_PATH=. ./simg_display dino_ref_cl.simg
    
You should see a dinosaur in ASCII art with blue water background and a yellow sky.  Did you know that when Sauropods were first discovered, people thought they must have lived in water?  They thought that the animals' massive size could not have been supported on land, so they'd need to be slightly bouyant in water.  Strong evidence to the contrary was found later in the form of findings which could only have occurred on land, such as footprints and particular bone scatter patterns.

Hmm, well, anyway, for this assignment you're going to write some programs that write this cool color ASCII art format.  It turns out that one of the BIGGEST reasons for using C is manipulating file formats.  Even if you do this in Python or some other language, usually there is some binding to a C program under-the-hood which is actually manipulating the files themselves.  C is a great tool for this because it is so good at working with the actual bytes flowing around memory.  You are not burdened by wondering what parts of, say, a string are really the string data versus all the object fluff Python/Java/whatever, puts there.  In C, it's just the data you need and no fluff.

I've created a simple file format called "simple image" or "simg".  It consists of the following:

    BYTES 1-4:  height of the image in rows as an integer
          5-8:  width of the image in chars as an integer
          9+:   height X width pixel data with last row printed first

So for the image (sorry can't do color in this readme file):


     \ /           __
    - O -         / _)
     / \ _.----._/ / 
        /         /  
    ~~~/ (  | (  |~~~~
    /__.-'|_|--|_|~~~~

Count the rows and columns.  You'll notice it is 6 rows and 18 columns/chars for each row.  Shorter rows are padded with spaces until they are 18 chars long.

Now try this:

    $ xxd dino_ref_cl.simg 
    00000000: 0600 0000 1200 0000 2f00 0000 005f 0000  ......../...._..
    00000010: 0000 5f00 0000 002e 0000 0000 2d00 0000  .._.........-...
    00000020: 0027 0000 0000 7c00 0000 005f 0000 0000  .'....|...._....
    00000030: 7c00 0000 002d 0000 0000 2d00 0000 007c  |....-....-....|
    00000040: 0000 0000 5f00 0000 007c 0000 0000 7e04  ...._....|....~.
    00000050: 0000 007e 0400 0000 7e04 0000 007e 0400  ...~....~....~..
    00000060: 0000 7e04 0000 007e 0400 0000 7e04 0000  ..~....~....~...
    00000070: 002f 0000 0000 2000 0000 0028 0000 0000  ./.... ....(....
    00000080: 2000 0000 0020 0000 0000 7c00 0000 0020   .... ....|.... 
    00000090: 0000 0000 2800 0000 0020 0000 0000 2000  ....(.... .... .
    000000a0: 0000 007c 0000 0000 7e04 0000 007e 0400  ...|....~....~..
    000000b0: 0000 7e04 0000 007e 0400 0000 2000 0000  ..~....~.... ...
    000000c0: 0020 0000 0000 2000 0000 0020 0000 0000  . .... .... ....
    000000d0: 2f00 0000 0020 0000 0000 2000 0000 0020  /.... .... .... 
    000000e0: 0000 0000 2000 0000 0020 0000 0000 2000  .... .... .... .
    000000f0: 0000 0020 0000 0000 2000 0000 0020 0000  ... .... .... ..
    00000100: 0000 2f00 0000 0020 0000 0000 2000 0000  ../.... .... ...
    00000110: 0000 0000 0000 2000 0000 002f 0300 0000  ...... ..../....
    00000120: 2000 0000 005c 0300 0000 2000 0000 005f   ....\.... ...._
    00000130: 0000 0000 2e00 0000 002d 0000 0000 2d00  .........-....-.
    00000140: 0000 002d 0000 0000 2d00 0000 002e 0000  ...-....-.......
    00000150: 0000 5f00 0000 002f 0000 0000 2000 0000  .._..../.... ...
    00000160: 002f 0000 0000 2000 0000 0000 0000 0000  ./.... .........
    00000170: 2d03 0000 0020 0000 0000 4f03 0000 0020  -.... ....O.... 
    00000180: 0000 0000 2d03 0000 0020 0000 0000 2000  ....-.... .... .
    00000190: 0000 0020 0000 0000 2000 0000 0020 0000  ... .... .... ..
    000001a0: 0000 2000 0000 0020 0000 0000 2000 0000  .. .... .... ...
    000001b0: 0020 0000 0000 2f00 0000 0020 0000 0000  . ..../.... ....
    000001c0: 5f00 0000 0029 0000 0000 2000 0000 005c  _....).... ....\
    000001d0: 0300 0000 2000 0000 002f 0300 0000 2000  .... ..../.... .
    000001e0: 0000 0020 0000 0000 2000 0000 0020 0000  ... .... .... ..
    000001f0: 0000 2000 0000 0020 0000 0000 2000 0000  .. .... .... ...
    00000200: 0020 0000 0000 2000 0000 0020 0000 0000  . .... .... ....
    00000210: 2000 0000 005f 0000 0000 5f00 0000 0000   ...._...._.....
    00000220: 0000 0000

That is a hexdump of the sample simg file.  Notice you see: 06 00 00 00 as the first four bytes.  That is 6h (hex) which is also 6 decimal.  Then you see the next four bytes: 12 00 00 00.  That is 12h or 18 decimal.  Then you see a bunch of chars... eventually you see a / then underscore then underscore and so on.  That's the LAST row of the dinosaur!  Row after row is stored in the file.  You can see the very last row as the \ and / of the sun and two underscores on the dinosaur's head.

The file also contains color data for each char.  That's why the file is so much longer than you'd think based on just the text chars.

More about the format later.  But for now there is a library called libsimg that I provide for working with these files.  The interface is available in libsimg.h:

    typedef struct {
        char c;
        int r;
    } simg_pixel;

    typedef struct {
        int height;
        int width;
        simg_pixel ***data;
    } simg_img;

    typedef struct {
        int cx;
        int cy;
        char c;
        int r;
    } simg_cursor;

    enum simg_color_list {
        SIMG_RESET,
        SIMG_RED,
        SIMG_GREEN,
        SIMG_YELLOW,
        SIMG_BLUE,
        SIMG_MAGENTA,
        SIMG_CYAN
    };

    extern const char *simg_colors[7];

    int simg_create(simg_img *img, int height, int width, char bg);
    int simg_setpixel(simg_img *img, int x, int y, int color, char c);
    int simg_write(simg_img *img, char *fn);
    int simg_read(simg_img *img, char *fn);
    int simg_print(simg_img *img, simg_cursor *cur);

First let's look at the structs.  There is simg_pixel, which has c (the char at a particular X,Y coordinate), and r (an integer for the colorcode of that pixel).

The colorcodes are defined in the enum simg_color_list.  There are only seven possible colors.  RESET is the default terminal color, usually a slight gray/white on a black background.  The other colors are terminal red, green, etc.  Remember how enums work.  RESET will be 0, RED will be 1, GREEN 2, etc.

The pixels are held in a struct called simg_img.  That struct has the height and width as ints.  But then it has an interesting triple-star structure called data.  Let's break that down.

If you want to point to an simg_pixel, you'd do:

    simg_pixel *pixel;

If you want to point to an ARRAY of simg_pixels, you'd do:

    simg_pixel **pixels;

That's a pointer to an array of pointers.  Each pointer in the array points to a pixel.  That is a single row in the image: an array of pointers to simg_pixel structs.  But we need many rows.  So what we need is:

    simg_pixel ***data;
    
That is a pointer to an array of pointers, each of which points to an array of pointers to simg_pixels.  Whew!

The last struct we have is called simg_cursor.  It represents a floating cursor above the image and is used for proper display during editing.  Be sure to check out the lectures where I show how this works!

Now let's look at the function interface.  We have five functions.  Try them out!

    int simg_create(simg_img *img, int height, int width, char bg);
    int simg_setpixel(simg_img *img, int x, int y, int color, char c);
    int simg_write(simg_img *img, char *fn);
    int simg_read(simg_img *img, char *fn);
    int simg_print(simg_img *img, simg_cursor *cur);

simg_create: given a pointer to a blank simg_img, this function sets the height and width and allocates memory for ***data structure.  It sets each pixel to a given bg (background) and the RESET color.  So for instance, height=3 width=5 bg=# would yield an simg_img structure representing:

    #####
    #####
    #####
    
Next up you can try simg_setpixel(), which changes the char and color at a given X,Y coordinate to a given char and color.  Be sure to try this out so you fully understand what's happening, because remember the file format is stored upside-down!  Be sure you understand where 0,0 is.  No I'm not giving you tons of examples because I want you to practice having to figure out some things.

Next are simg_read() and simg_write().  The read function takes a filename, reads the simg data, and fills in the given img struct with the file's data.  The write function does the reverse.  Don't get fancy here.  Your code has to work with mine.  So the file format has to be exactly the same.

Finally we see simg_print().  This is what actually prints out a given simg_img struct to the terminal.  Again: try this out and learn how it works.  I am not giving you every detail.  Note the cursor parameter.  If you give this a simg_cursor, the print function will display that cursor char/color at the cursor location without modifying the underlying image.  But if you give it NULL for cursor, it will just display the image without any cursor.

# OK but what now?  A totally reasonable question.

Your job is to write three utilities that use libsimg:

    simg_display (2 points)
    simg_convert (8 points)
    simg_edit (10 points)
    
Write them in this order, because it goes from easiest to hardest.  I provide a test script for the first two.  You can refer to that test script for usage examples.  The last one will be graded by hand.

You run simg_edit like so (assuming LD_LIBRARY_PATH=. is set):

    $ ./simg_edit <simg file>
    
Such as:

    $ ./simg_edit dino.simg

Rubric for simg_edit follows:
    
    a) 1 point.  Load and display an image if the provided filename exists.  If it doesn't exist, create a default background and size.
    
    b) 2 points.  Have a cursor display over the image.  The cursor should be controllable with the arrow keys.  If you press the up arrow, for instance, the cursor should move up one row and the image redrawn to show the cursor in the new location.  The cursor should not be permitted to leave the height and width range of the image.
    
    c) 1 point.  If you press "c" followed by a char on the keyboard, the cursor will change to that char.  The image should be redrawn to show the cursor with the new char.
    
    d) 1 point.  If you press "r" followed by a number 0-6, the color of the cursor should change to that color.  The image should be redrawn to show the cursor with the new color.
    
    e) 2 points.  If you press "p", the pixel in the image underneath the cursor is set to the cursor's char and color.
    
    f) 1 point.  If you press "s", the image is saved to the given filename.
    
    g) 1 point.  If you press "l", the image is reloaded from the given filename.  Redraw the image.
    
    h) 1 point.  If you press "q", the program quits without saving changes or annoying "are you sure?" messages I mean come on just let me quit already.

# libsimg

For m3a, you may use my reference libsimg.so and libsimg.h files.  You get full credit for this assignment for writing the three utility programs that use my implementation of libsimg.  Part of what you are practicing is to work with unfamiliar libraries.  If you aren't sure how a function works, write a test program and try some things!  Give it different inputs and see what the outputs are.

I found this to be a fun assignment to create.  I hope you have fun with it, too!
