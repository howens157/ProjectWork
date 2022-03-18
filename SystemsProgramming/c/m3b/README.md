# C Milestone Part 2 - M3B

Well, you saw this coming!  Now you will write libsimg.  I provide my simg_display, simg_convert, and simg_edit reference binaries (not source code) for you to test against your libsimg implementation.  You must use my libsimg.h file.  You are on your own for libsimg.c.  I provide a test file which tests all the same conditions as m3a, except it will be running my reference binaries and your library (rather than my library and your utilities like before).  The ultimate test is for your utilities to work with your library, so any mix-and-match of utilities and libraries is possible.

All the information you need is already in the previous assignment's readme, except...

How do we actually print out color?  Well I'm not going to tell you everything, but here's a little clue program:

    #include <stdio.h>

    int main()
    {
        char c = 35;
        printf("\033[0;31m");
        printf("%c\n", c);
        printf("\033[0m");
        return 0;
    }

In UNIX programming environments, you can set the color of the text to be printed by giving some special chars that indicate color values.  Try this out in the program above.  Then try these values in place of the [1;31m in the first printf():

    [0m
    [0;31m
    [0;32m
    [0;33m
    [0;34m
    [0;35m
    [0;36m

These correspond to the colors in libsimg.h:

    enum simg_color_list {
        SIMG_RESET,
        SIMG_RED,
        SIMG_GREEN,
        SIMG_YELLOW,
        SIMG_BLUE,
        SIMG_MAGENTA,
        SIMG_CYAN
    };
    
I.e. 0m is for RESET, 0;31m is for RED, etc.

Also take a look at the hexdump of the file format in the readme for m3a.  Notice the extra chars that I said were color values?  This is why.  Before every char it sets the color, then afterwards it sets it back to RESET.

# Grading

The grading scripts and rubric are identical to m3a.  The only difference is that it is *my* utility binaries and *your* library implementation.

This m3b assignment is worth 20 points.  The m3a assignment is also worth 20 points.  The total is 40 points.  There is no overlap of grading i.e. it is possible to get a zero for one and 20 for the other.
