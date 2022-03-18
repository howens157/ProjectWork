# C - Slowly returning to Jurassic Park

Today we finally see our friend dinosaur.dat again!

We discussed file I/O and a function called readline() in class.  Take a look at d19-template.c, which has a completed version of readline():

    #include <stdio.h>
    #include <stdlib.h>

    int readline(FILE *fp, char *buf, int len)
    {
        char c = fgetc(fp);
        int i = 0;
        
        while((c != '\n') && (i < len))
        {
            buf[i] = c;
            
            c = fgetc(fp);
            i++;

            if (c == EOF)
            {
                i = -1;
                break;
            }
        }
        
        return i;
    }

    int redelim(char curdelim, char newdelim, char *buf, int len)
    {
        // your code here
    }

    void clearbuf(char *buf, int len)
    {
        // your code here
    }

    int main()
    {
        FILE *fp;
        char delim = '\t';
        int len = 2048;
        char *buf = malloc(len * sizeof(char));
        int n, r, i = 0;
        int maxlines = 50;
        
        fp = fopen("dinosaur.dat", "r");
        
        n = readline(fp, buf, len);
        printf("read %d chars\n", n);
        
        while((n != -1) && (i<maxlines))
        {
            r = redelim('\t', ';', buf, len);
            printf("changed %d delims: %s\n", r, buf);
            
            clearbuf(buf, len);
            n = readline(fp, buf, len);
            
            i++;
        }
        
        return 0; 
    }

This program should output the first 50 lines of dinosaur.dat, but with the delimiter changed from a tab to a semicolon.  Your job is to write the two functions redelim() and clearbuf().

# The BIG LESSON

I want you to keep practicing the C way of functions: you create some buffer space, then the function modifies the data in that buffer space.  This is different from what you saw in Python or many other languages, where the return value of a function is the modified data, such as a new array or whatever.

Take a look at main() above.  Notice how I malloc 2048 bytes.  That space is on the heap!  But I have a pointer to that space called buf.  I pass that pointer to readline(), which reads one line of the file and puts it in that buffer.  I have a while loop which does this for a maximum of 50 lines.  Notice also the n!=-1 condition of that while loop.  n would equal -1 if readline() returns -1.  And readline() would return -1 if the end of the file is reached (notice the c==EOF condition in readline()).

To be clear, key points:

1) The actual data you want modified is in a buffer on the heap.

2) The function modifies that buffer *in place*.

3) The function returns a value that tells you something about the buffer, such as how many chars it read in a line.  The error value is typically in this return value too!  Such as returning -1 if there is an error.

# So... what do I do?

Write redelim() and clearbuf().  The purpose of redelim() is to replace all instances of a char curdelim with a given char newdelim.

A potential problem here is that we end up reusing buf!  Some lines in the file may be longer than others, such as in a sample comma-separated file like this:

    aaa,bbb,ccc
    x,y,z 
    
The first time I call readline(), buf will be "aaa,bbb,ccc".  The second time I call it I use the same buffer space, so it will be "x,y,zbb,ccc"!  Whoops!

The answer is to clear the buffer space.  That just means setting every single value to be a zero.  So write clearbuf() which does that.

# Testing

I provide a test script like usual!

    Testing  ...
    Sample 1, 4 points             ... Success
    Time: 0 seconds (max allowed=5)
    Score: 4 / 4
