# C - Introduction to Arrays

Today you will expand the littlelib library by adding some functions that work with arrays.  The idea is to become comfortable working with arrays and array pointers in C.

Start by looking at the file d18.c I provide.  Here it is below:

    #include <stdio.h> 

    #include "littlelib.h"

    int main() 
    {
        init_littlelib();
        
        int a[] = { 2, 3, 4, 5, 6, 0 };
        int i;
        
        printf("sum: %d\n", sumnums(a));
        
        for(i=0; i<10; i++)
        {
            shuffle(a, arraylen(a));
            printarray(a);
        }
            
        return 0; 
    }

The output of this should be the following:

    $ LD_LIBRARY_PATH=. ./d18 
    sum: 20
    { 5 6 4 2 3 }
    { 4 3 5 2 6 }
    { 4 5 2 6 3 }
    { 4 3 2 6 5 }
    { 4 6 2 5 3 }
    { 2 6 3 5 4 }
    { 5 2 6 4 3 }
    { 5 6 2 3 4 }
    { 3 5 2 4 6 }
    { 3 6 5 2 4 }
    
Notice how in d18.c, one of the first things main() does is declare an array of integers.  Also notice that the last integer is a zero.  That is called a ``sentinal'' value.  A sentinal is a value that indicates the end of something (like a period at the end of a sentence... see it? sentence, sentinal).  In CS, we often use the sentinal value zero to indicate the end of a list of something.  It does mean that we can't use the zero anywhere else, because then we could be fooled into thinking the list ends sooner than it really does.

Anyway, in this program we have an array with positive integers, followed by a zero sentinal.

Then we run the function sumnums()... and you might notice a few other function calls.  Check out the new littlelib.h:

    int init_littlelib();
    int randint(int lower, int upper);
    int is_prime(int n);
    int arraylen(int a[]);
    int sumnums(int a[]);
    void printarray(int a[]);
    void shuffle(int *a, int len);
    
The functions shuffle(), sumnums(), arraylen(), and printarray() are all new ones that you will need to write for this assignment.  You will write implementations for those functions into the littlelib.c file from d17.  Your library must work with the d18.c and littlelib.h files I provide.

Here are some clues about each function.  I suggest you write them in this order.  At least, you should do shuffle() last!


    int arraylen(int a[])

This function returns the number of *values* in the array.  This does *not* include the sentinal value.  For example, it should return five for the array a[] in d18.c, not six.


    int sumnums(int a[])

This function sums all the values in the given array and returns that sum.


    void printarray(int a[])

This function prints the array starting with a {, then each value in order not including the sentinal, then a }, then a newline char (\n).  See examples above when running d18.


    void shuffle(int *a, int len)
    
This function randomly shuffles a given array.  But unlike the other functions, it operates on the array *in place* via a *pointer*.  Notice how the other functions take the array itself as a parameter.  This function takes a pointer to the array as a parameter instead.  (There is a little surprise about this that we'll talk about in lecture.)  The function also takes the length as a parameter.  This is usually how you see functions written in C that operate on arrays: you give a pointer to the array and the length.  It does not figure out the length itself.  One reason for this is that sometimes you want to use different sentinal values, so you might have your own way of calculating the length.  Another reason is that you may want to operate only one the first few values instead of all values.

Anyway, the algorithm here is simple:
1) pick a random integer A between zero and len,
2) pick another random integer B between zero and len,
3) swap the value in a[A] with a[B],
4) do steps 1-3 for len times.

So for instance, if there are five values in the array, you would do steps 1-3 five times.  Because you set the random seed in init_littlelib(), you should get the same results as I do in the demonstration above.

# Compiling / Makefile

Remember from class that you generate shared libraries like so:

    $ gcc -fPIC -shared littlelib.c -o liblittlelib.so
    
And compile programs with them like this:

    $ gcc -Wall -o d18 d18.c -llittlelib -L.

This time you need to write a Makefile for your library.  You should have the following targets:

    all
    liblittlelib.so
    d18
    clean

all should require liblittlelib.so and d18 but *not* duplicate calls to gcc.
liblittlelib.so should call gcc to compile liblittlelib.so.
d18 should call gcc to compile d18.
clean should delete liblittlelib.so and d18 (don't delete the source files though!!).

# Testing

I provide a test just like usual.  Note this time though that the output from calls to "make clean" and "make" are displayed.

    $ bash d18test.sh 
    Testing  ...
    Sample 1, 6 points             ...
    rm -f liblittlelib.so
    rm -f d18
    gcc -fPIC -shared littlelib.c -o liblittlelib.so
    gcc -Wall -o d18 d18.c -llittlelib -L.
    Success
    Time: 0 seconds (max allowed=5)
    Score: 6 / 6

