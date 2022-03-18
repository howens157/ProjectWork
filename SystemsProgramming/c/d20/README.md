# C - More returning to Jurassic Park

Last time we looked at readline() and got used to the idea of writing functions that modify data in place instead of returning a copy of the changed data.

Now take a look at d20.c, which uses readline:

    #include <stdio.h>
    #include <stdlib.h>

    #include "libdinos.h"

    int main() 
    {
        FILE *fp;
        char delim = '\t';
        int len = 2048;
        char *buf = malloc(len * sizeof(char));
        int n;
        
        fp = fopen("dinosaur.dat", "r");
        
        n = readline(fp, buf, len);
        
        printf("read %d chars\n", n);
        
        int max = 50;
        char *splits[max];
        int ns = split(buf, splits, delim, max, len);
        
        int i;
        for(i=0; i<ns; i++)
        {
            printf("%s\n", splits[i]);
        }
        
        return 0; 
    }

Now... notice that readline() is not in d20.c.  It's over in libdinos!  Start this assignment by creating a new library called libdinos.  Put readline() in it.  Also create a Makefile to compile your library and d20.  Don't forget to create libdinos.h for the function signatures and libdinos.c for the function implementations!

d20.c won't compile yet, of course.  For that you'll need a function called split().  This function behaves like the split function in Python (kinda).  Let's break down the function signature:

    int split(char *buf, char **splits, char delim, int max, int len);
    
Let's say you have a string "garfield,felix,gorgon" that you want to split by the delimiter ','.  You'd put that string into a char buffer and pass it as the parameter 'buf'.  You'd also give it a parameter called 'max' that indicates the maximum number of possible splits.  And you'd give it 'len', which is the maximum possible length of the string in 'buf'.  The function will return the number of split items it found.  So maybe something like this:

    int len = 50;
    char *buf = malloc(len * sizeof(char));
    
    int max = 5;
    char *splits[max];

    char delim = ',';
    
    int ns = split(buf, splits, delim, max, len);
    
So far we have len, max, delim, and buf accounted for.  But what is 'splits'?  It is an ARRAY of CHAR POINTERS.  In this case, we have an array with 5 char pointers in it.  No big deal.  Just a plain old array like any other array.  Except this one has char pointers in it.

Each char pointer points to a string (remember that strings are just arrays of chars with a null byte sentinal at the end).  So in the end, splits will be like this:

    splits[0] = "garfield"
    splits[1] = "felix"
    splits[2] = "gorgon"
    splits[3] = 0
    splits[4] = 0
    
Notice that like shuffle() in the last assignment, both readline() and split() change variables *in place*.  The return value tells you something about the variables that were changed, such as the number of chars read in a line, or the number of splits found in the given string.  This is the TYPICAL way functions are written in C programs.  It is different than, say, Python, where the return value of the function *is* the result you want.  In Python you see things like this:

    (name, email, zipcode) = userdat.split('\t')
    
The return value from split() in Python is the actual split up string.  If you want to catch an error, you do something like this:

    try:
        (name, email, zipcode) = userdat.split('\t')
    except <WHATEVER EXCEPTION YOU'RE LOOKING FOR> as ex:
        print(ex)

In C, usually the error is returned as an error code such as -1 from the function, and the values made available by changed them in place.  So you'd see something like this:

    n = readline(fp, buf, len);
    
    if(n == -1)
    {
        printf("error!  nothing read!");
    } else
    {
        printf("%s\n", buf);
    }
    
Well ANYWAY your job is to write split() into your libdinos library.  Don't overcomplicate things.  Basically what you're trying to do is go through each char in the given 'buf'.  So while the "current" char is not null, check if the char is not the delimiter, and add that char to another buffer called 'section' (you'll have to malloc one).  But if the char is the delimiter add the 'section' buffer to 'splits', then malloc a new 'section' buffer.

Don't overcomplicate things.

Do NOT overcomplicate things!  The only functions you need to call in split() are malloc() and sizeof().

If you find yourself spinning your wheels making a more and more complex function, go back to the drawing board.  My solution is only about 20 lines, including lines with only { and }.

# Testing

I provide a test script like usual!

    $ bash d20test.sh 
    Testing  ...
    Sample 1, 7 points             ... Success
    Time: 0 seconds (max allowed=5)
    Score: 7 / 7
