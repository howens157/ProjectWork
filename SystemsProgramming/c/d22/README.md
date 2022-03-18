# Systems Programming Daily 22 - Practice Reading Files into Memory

We have more fun planned with the dinosaurs!  But all the data are stuck in dinosaur.dat.  Today you will write a function readdinos() and supporting code to read every dinosaur find into memory.  Later assignments will build on this one, and this one builds on previous assignments.

In the last assignment, you practiced reading and writing BINARY files.  Just working the the bytes and such.  This assignment, you'll return temporarily to reading separated volumes.  You worked with separated volumes in Python and Bash.  Those languages make it easy to work with text files.  The stength of C tends to be with binary files, but I still want you to see how separated volumes can also work in C.

Take a look at the new libdinos.h I provide:

    typedef struct
    {
        double lat;
        double lng;
        
        double maxma;
        double minma;
        
        int namelen;
        char *name;
    } dino;

    int split(char *buf, char **splits, char delim, int max, int len);
    int readline(FILE *fp, char *buf, int len);
    int readdinos(char *fn, dino **dinos);

Notice how this combines several of the past dailies into a new libdinos.  I also expand the dino struct to include maxma and minma.  Before it just had the dinosaur name, lat, and lng.

You also have readline() and split() from previous assignments.  You can probably tell what you have to do now... check out the d22.c I provide:

    #include <stdio.h>
    #include <stdlib.h>

    #include "libdinos.h"

    void printdino(dino *d)
    {
        printf("%f %f %f %f %s\n", d->lat, d->lng, d->maxma, d->minma, d->name);
    }

    int main()
    {
        int n;
        
        dino *dinos[30000];
        
        n = readdinos("dinosaur.dat", dinos);
        
        printf("read %d dinos\n", n);

        printdino(dinos[0]);    
        printdino(dinos[250]);
        printdino(dinos[3000]);
        
        return 0; 
    }

The output from running this should be (assuming LD_LIBRARY_PATH=. is set):

    $ ./d22 
    read 29652 dinos
    51.083332 -1.166667 55.800000 37.200000 Aves indet.
    24.500000 33.000000 2.588000 0.011700 Anas penelope
    -9.704053 39.236462 152.100000 145.000000 Brachiosaurus brancai

Notice the 29652 is a bit fewer than the number of lines in dinosaur.dat.  The reason is that there are some corrupt/bad lines.  Such is life; it is a real world dataset.  I have a condition in my readdinos() function to filter them.  The filter is to make sure that the number of splits equals 27.  All valid data entries have the same number of splits.  And the splits() function should be returning the number of splits it found.  So I just check to make sure splits() finds the correct number of splits.

Note: if you wrote your split() function in a slightly different way such that it consistently returns 26, 28, etc., for the same data, that is fine.  Just check that condition.  The point is that you filter invalid data entries in a way that fits your code.  If your program returns 29652 +/- 10 entries, I plan to accept it for credit so long as the data lines (the three lines following the "read 29652 dinos") are correct.  The learning exercise here is to see that there are a few ways to read in lines and filter for real world invalid data entries in a way that won't just crash your program.

Anyway, your readdinos() function takes in a filename and an array of dino pointers.  I just put these in the stack:

    dino *dinos[30000];
    
but I could also have said:

    dino **dinos = malloc(30000 * sizeof(dino));
    
to put them in the heap.  And yes, I waste a little bit of space by setting this to 30k instead of counting the lines then allocating the space.  But in such a simple program it doesn't matter much.  There is always a tradeoff between CPU time and memory space... counting all the lines first would take time.  Instead I just waste a little space and save time.  It's a choice you will have to make often.

Your readdinos function should malloc a new dino for every successful split() and give that dino the data from that line.  Remember that name is the identified_name.  And minma, maxma, lat, lng, all have their own columns.

But... uh oh... these are strings in the file and you want doubles for the dino struct!  Look up the function strod() in stdlib.h.  It converts strings to doubles.

Do NOT change libdinos.h or d22.c.  Only create and modify your Makefile and libdinos.c.

# Testing

Take a look at d22test.sh.  It calls make clean and make.  So you will need to be sure your Makefile is set up to produce libdinos.so and d22.

It ought to give back:

    $ bash d22test.sh 
    Testing  ...
    Sample 1, 6 points             ... Success
    Time: 1 seconds (max allowed=5)
    Score: 6 / 6
    
# Whale
       .
      ":"
    ___:____     |"\/"|
  ,'        `.    \  /
  |  O        \___/  |
~^~^~^~^~^~^~^~^~^~^~^~^~

You are on a boat in calm Pacific Ocean waters.  Your eyes are closed but you feel the boat sway and the sun on your face.  You hear a splash and then feel water droplets hit you.  You open your eyes and see a whale cresting just off the side of the boat.  You *just barely* make eye contact with the creature from the deep. In that moment, time seems to stop, as if it came up just for you.  A thought enters your head, and you somehow know it is from this ancient beast.  You ponder its meaning, knowing that you have just seen something beautiful.  But you don't worry.  You will see it again, when you are ready.  It sinks down, and the boat lists slightly towards the spot where the whale dove down.  The whale's tail glides silently down next, and he is gone.  You think to pull your journal from your bag.  What otherworldly inspiration did you receive today?
