# Systems Programming Daily 21 - File Formats

Today you will practice reading and writing a file format.  Remember that a file format is essentially just a struct written to memory.  Sometimes it's really easy, such as when you have a struct like this:

    typedef struct {
        int a;
        int b;
        char c;
        double d;
    } sample;

In that case, all of the data in the struct is held as a block in memory, so all you need to do is write out the whole struct to a file.  When you read the file, you just allocate the appropriate amount of space in memory and copy the bytes from the file to that memory space.

It's harder in cases like this:

    typedef struct {
        int a;
        int b;
        char c;
        double d;
        char *s;
    } sample;
    
If you just write that out to disk, you will be writing out the actual pointer value in s, which is a memory address.  So instead you need to store the string itself to disk.  You need to write a function that puts each variable in an assigned spot in the file, so another function can read those assigned spots later and recreate the struct.

In this assignment, you need to create a struct to hold facts about dinosaur finds.  Just three to start: the latitude, the longitude, and the name.  The latitude and longitude are double values.  The name is a string held by a char pointer.

    Take a look at d21-template.c:

    #include <stdio.h>
    #include <stdlib.h>
    #include <string.h>

    // your code here (define the dino struct)
    // use typedef struct, not just struct

    void save_dino(dino *d, char *ofn)
    {
        // your code here
    }

    void load_dino(dino *d, char *ifn)
    {
        // your code here
    }

    int main(int argc, char **argv)
    {
        if(argc != 2)
            return 1;
        
        char *fn = argv[1];
        
        // create a dino struct and give it the following values:
        // latitude = 51.083332
        // longitude = -1.166667
        // name = "Aves indet."
        // do NOT hardcode the string length, get it with strlen() instead
        
        // call save_dino() and save d0 to the given filename (fn)
        
        dino d1;
        
        // call load_dino() and load the file you just saved into d1 (NOT d0)
        
        printf("d1.lat %f\n", d1.lat);
        printf("d1.lng %f\n", d1.lng);
        printf("d1.name %s\n", d1.name);
        
        return 0;
    }

I've given you some comments to get started.  Remember the trick we talked about in class for storing strings: you have to write out the length of the string as well as the string data itself.  An easy way to do this is to just put it into the struct as an int.

Do NOT modify the code I have already written.  Just fill in the commented sections.

Start by making a struct to hold the dino information.  Then write the save and load functions.

Do NOT try to write the save and load functions at the same time, though.  Write the save_dino() function first.  Then use xxd or other tools to see if it is really behaving how you think.  Then write load_dino() to read that file back in.

I provide two more files for your practice: d21-ref and dino-ref.dat.  d21-ref is a program that just reads a given dat file and tries to load it with my implementation of load_dino().  I provide it so that you can verify if your save_dino() is working correctly.  I am not providing the source code for d21-ref, obviously.  But I am giving you dino-ref.dat, which is the output of my reference save_dino() function for this assignment.  You can examine that file to see what is in there.

This assignment is worth six points.  I provide a test script as usual.
