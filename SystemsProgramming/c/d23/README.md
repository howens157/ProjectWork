# Systems Programming Daily 23 - Function Pointers

One of the big uses to function pointers that we discussed is in cases where you want to do the same thing to every element in a dataset, but that "same thing" may be slightly different depending on circumstances.  For instance, you may want to calculate the distance in time between a given item and every other item in a group, versus calculating the distance in geography.  The code to go through every other item is the same, and you may want to allow arbitrary "distance" calculations.

Take the following d23.c code as an example:

    #include <stdio.h>
    #include <stdlib.h>
    #include <math.h>

    #include "libdinos.h"
    #include "libgeodist.h"

    double calc_geodist(dino *d0, dino *d1)
    {
        return geodist(d0->lat, d0->lng, d1->lat, d1->lng);
    }

    double calc_timedist(dino *d0, dino *d1)
    {
        double t0 = (d0->maxma + d0->minma) / 2;
        double t1 = (d1->maxma + d1->minma) / 2;
        return fabs(t0 - t1);
    }

    void printdino(dino *d)
    {
        printf("%f %f %f %f %s\n", d->lat, d->lng, d->maxma, d->minma, d->name);
    }

    int main()
    {
        int n;
        double d;
        
        dino *dinos[30000];
        
        n = readdinos("dinosaur.dat", dinos);

        printf("dino 50 is:\n");
        printdino(dinos[50]);

        dino d1;
        
        d = nearest_dino(dinos[50], &d1, dinos, n, &calc_timedist);
        
        printf("nearest in time is %f units distant\n", d);
        printdino(&d1);
        
        d = nearest_dino(dinos[50], &d1, dinos, n, &calc_geodist);
        
        printf("nearest in geography is %f units distant\n", d);
        printdino(&d1);

        printf("\n");
        printf("dino 256 is:\n");
        printdino(dinos[256]);
        
        d = nearest_dino(dinos[256], &d1, dinos, n, &calc_timedist);
        
        printf("nearest in time is %f units distant\n", d);
        printdino(&d1);
        
        d = nearest_dino(dinos[256], &d1, dinos, n, &calc_geodist);
        
        printf("nearest in geography is %f units distant\n", d);
        printdino(&d1);
        
        return 0; 
    }

Notice the two new functions calc_geodist() and calc_timedist().  These functions are NOT part of libdinos.c.  They are ones added by the user of the library, which is d23.c.  However, libdinos DOES have support for using these different calculation functions via the nearest_dino() function.

The nearest_dino() function is in libdinos.c.  It takes in five parameters:

    dino *d0, dino *d1, dino **dinos, int numdinos, FUNCTION POINTER YOU FILL THIS IN :-)
    
d0 is the dinosaur you are checking against.

d1 is the dinosaur that is the closest.

dinos is the list of dinosaurs, usually compiled by readdinos().

numdinos is the number of dinosaurs in dinos (return value from readdinos()).

The last parameter is a function pointer.  In d23.c, you can see how calc_geodist and calc_timedist are both valid parameters.  What happens inside nearest_dino() is that there is a loop through every dinosaur in dinos.  Then d0 is compared to each dinosaur using the given function.  d1 is set to the nearest dinosaur.  The return value of nearest_dino() is the distance between d0 and d1.

I provide libgeodist (c and h files) with supporting functions for calc_geodist() in d23.c.  You don't need to change them.  All you need to do is change your Makefile to compile them and so that d23.c will compile.

When you run d23, you should get the following:

    $ LD_LIBRARY_PATH=. ./d23
    dino 50 is:
    42.035831 -106.389999 157.300000 145.000000 Diplodocus sp.
    nearest in time is 0.250000 units distant
    63.874168 125.149170 201.300000 100.500000 Dinosauria indet.
    nearest in geography is 0.028582 units distant
    42.035831 -106.390556 157.300000 145.000000 Camarasaurus sp.

    dino 256 is:
    24.500000 33.000000 2.588000 0.011700 Platalea leucorodia
    nearest in time is 0.005850 units distant
    35.750000 5.916700 2.588000 0.000000 Aves indet.
    nearest in geography is 5.578768 units distant
    24.433300 32.950001 2.588000 0.011700 Platalea leucorodia

# OK so what do I do?

Your job is to write nearest_dino() in libdinos.c.  You will have a few supporting tasks such as changing the Makefile and libdinos.h, but you should not change d23.c or libgeodist.

Notice in d23.c code like this:

    dino d1;
    
    d = nearest_dino(dinos[50], &d1, dinos, n, &calc_timedist);

Then d1 is used later by d23.c.  That means it is the job of nearest_dino() to ensure that d1 is the dinosaur that is nearest to d0 (dinos[50] in the above code).  The thing is, you can't just do something like this:

    d1 = dinos[WHATEVER_INDEX];
    
because that would only change the value of d1 inside the scope of nearest_dino().  d1 is a local variable of nearest_dino().  Instead you need to copy the data from dinos[WHATEVER_INDEX] to d1.  d1 should be a copy of dinos[WHATEVER_INDEX], not just point to the same memory.

To do this, look up the function memcpy().

Also, remember you are searching for the minimum value.  This is just a conditional in a loop.  The loop goes through every dinosaur.  The conditional checks if the distance between d0 and dinos[WHATEVER_INDEX] is less than a running minimum.  That running minimum should be set to some high value to start with.  You might find the variable INT_MAX in limits.h to be useful.

Obviously you should start with your d22 code and add nearest_dino() to it.  Don't try to do this whole thing from scratch.

# Grading

I provide a test like usual.

    $ bash d23test.sh 
    Testing  ...
    Sample 1, 6 points             ... Success
    Time: 1 seconds (max allowed=20)
    Score: 6 / 6

As before, it calls make clean and make, so be sure those are working properly via the Makefile.
