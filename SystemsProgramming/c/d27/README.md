# Systems Programming Daily 27

Well, you couldn't get away from a Systems Programming class without practicing the famous fork() call.  Remember that unlike pthreads, fork() creates a whole new process.  At a high level, what it does is create a new process, copy everything from the parent process into the child process, and then keeps running both the parent and child.

As you can imagine, fork() is wayyy slower than pthreads.  There is just so much more overheard in creating/copying the process data.  To make matters worse, you have to use IPC to communicate, because now you have two completely different processes.  For us, it means using the file systems to store and load results from different processes.  Yikes, it is slow.

In this assignment, your job is to do the same thing you did for D26, except with fork() and wait() instead of pthreads create/join.

Start by copying your D26 code and making appropriate name changes e.g. d26.c to d27.c and in the Makefile.  Then eraticate pthreads code from d27.c by commenting it out.

Change the NUM_THREADS variable to NUM_PROCESSES.

Now instead of creating a pthread, call fork().  The child process should call the "thread function" that pthreads had been using.  The parent process can just keep going.  The parent should create NUM_PROCESSES processes by calling fork() that many times.

When the child process is done running the "thread function", it should store the result in a binary file.  The binary file should also have the index number for the result.  All you're doing is taking a struct like this:

    typedef struct {
        int mynum;
        double dist;
    } fret;

And writing it to disk.  Be sure to use a name like "ret_CPID.bin" where CPID is the child process ID.  **The child process should exit once it is done writing this file.**

The parent process should then enter a loop that calls wait() NUM_PROCESSES times.  Each time it will get an arbitrary child process ID.  Use that ID to read "ret_CPID.bin" to get the index and distance information and store it like so:

    nearest_dinos[ret->mynum] = ret->dist;
    
Then your code for displaying the nearest dino information should work the same.

Run your D27 code with, say, NUM_PROCESSES=4.  Then go back and run D26 with NUM_THREADS=4.  Observe just how much faster D26 is.  Here are my results:

Using fork():

    $ time ./d27
    172.86user 57.36system 1:25.35elapsed 269%CPU (0avgtext+0avgdata 69516maxresident)k
    0inputs+160000outputs (0major+1214591minor)pagefaults 0swaps

Using pthreads:

    $ time ./d26
    100.88user 0.94system 0:35.78elapsed 284%CPU (0avgtext+0avgdata 64924maxresident)k
    0inputs+0outputs (0major+15658minor)pagefaults 0swaps

My D26 implementation took about 36 seconds, versus 1m25s for D27.  That's almost three times faster!  And the overhead of fork() will grow with each extra process!  Yikes!

The moral to the story is that you want to use pthreads if you need to create a lot of little threads to do little, discrete tasks.  You want to use fork() when you need complete separation of memory between child and parent, especially when you only have a handful of children that run for a long time.

# Grading

The expectation for this assignment is that it outputs exactly the same output as your d26 (pthreads) solution.  The test script will run your d26 code and copy the result to ref/1.  Then it will run your d27 and put the result in wrk/1.  It should be exactly the same.

Recall that in d26 you wrote out the nearest_dino information like this:

0       16.889824
1       16.889824
2       11.588992
3       1.944737
4       1.944737
5       8.298629
6       89.547127
7       0.149479
8       0.228284
9       0.288488
10      0.166582

This is the output from this code in my d26.c:

    for(i=0; i<n; i++)
    {
        printf("%d\t%f\n", i, nearest_dinos[i]);
        
        free(dinos[i]->name);
        free(dinos[i]);
    }
    
I gave you quite a bit of leeway in the exact output because your code for readdinos() and split() might be a little different here and there.  But now you know that your code for this assignment is exactly the same a the previous one, so it ought to be consistent to what you did before.

Of course, I will also be checked to make sure you actually use fork() and file I/O as IPC instead of pthreads.
