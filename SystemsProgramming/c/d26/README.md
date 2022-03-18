# Systems Programming Daily 26

THIS ASSIGNMENT IS DUE MONDAY NOVEMBER 22, not Friday November 19 as it normally would.  There will be no daily given Friday.

Today you will practice using threads.  Real threads!  Not those phony Python/Ray threads which are actually super-heavy-duty processes that communicate via super-heavy-duty sockets.

Start by copying your D25 code and making the usual small name changes: d25.c to d26.c, the Makefile, etc. etc.

You should have code leftover from D23 in which you created and used nearest_dino().  Recall you wrote that function to take a function pointer such as to calc_geodist().  The nearest_dino() function then calculated the distance between a given dino and every other dino in the list of dinos.

Your job in this assignment is to calculate the distance between every dinosaur and every other dinosaur.  Start by writing the code for this in a sequential (non-parallel, no threads) fashion.  All your changes will be to d26.c.  No changes should be necessary to libdinos.c (though you are free to make small changes there if necessary).

***Important Note:*** Since there are a variety of solutions for split() and readdinos() out there, I am only asking you to calculate the first 20000 dinosaurs that you extracted.  And because you will be using threads, there is no promise about the order in which the calculations will return.  As a result the test output I give you is just an example.  I will be grading this assignment by hand rather than with a test script.

Anyway, the basic procedure is to:

1) Create an array of 20000 doubles.  Call it nearest_dinos or something obvious like that so I can find it easily in your code.

2) For every dino in dinos, call nearest_dino() for that dino.  Use calc_geodist() with it.  Store the result in nearest_dinos under the same index as the dino in dinos.  For example, nearest_dinos[5] should have the distance to the nearest dinosaur to dinos[5].

So... you notice this is not that efficient for two reasons:

a) You calculate the distance between each pair of dinosaurs twice.  E.g. dino[5] to dino[6] and then dino[6] to dino[5].  *Ignore* this bit of inefficiency for now.  First of all, I am trying to get you practice threads.  Second of all, some distance measures are one-way only, so you can't assume that dino[5] to dino[6] is always the same as dino[6] to dino[5].

b) You have several cores available and only one is active.  This is where threads come in!

So next parallelize your calls to nearest_dino() with pthreads.  Set a global variable or preprocessor macro/define called MAX_THREADS.  Let's say you set MAX_THREADS to 4.

On your call to nearest_dino(), call it 4 times simultaneously, each one in a thread of it's own.  You will need to write a wrapper function for this.  The wrapper function will do the following:

1) Receive a dino index number as an argument (remember our class discussion on how to use the void* argument to get a struct).

2) Calculate the nearest_dino() to the given dino index.

3) Store the distance to the nearest_dino() as, say, nearest_dinos[index].

This is a rare time that you should use globals.  If you set dinos and nearest_dinos to be global, than you can read and write to them with threads using the index.  The threads will not interfere with each other because they should *only* be accessing their index number.

In other words, keep it simple.  Don't try to create some complex call chain with pointers going everywhere just to avoid using a global.

Now, you're spinning up four (NUM_THREADS) threads in a loop.  The next thing to do is wait for them to all finish using join().  So you create four threads, then join those threads.  On the next loop iteration, create four new threads and then join them.  This way you parallelize your calls to nearest_dino() in a very simple way.

You may complain, "but what if nearest_dino() takes a long time for some dinos and not much for others?"  That is a risk to this strategy.  To avoid it, you could create a thread pool or use some other more complex strategies.  But here's the thing: the simple strategy will get you a vast majority of the benefits of parallization for only a minimum cost.  Your program is still easy to read and write and debug.  You don't have to have any complex shared memory management etc.

This simple strategy is therefore very popular and useful and will get you through a vast majority of situations when parallization will help.  If this interests you, there are whole courses on parallel programming in how you can specialize in squeezing that bit of power out of your CPU and minimize waste.

Generate some meaningful output of the index and nearest_dino values at the end of your d26.c, like in my example below.

# Grading

As mentioned above, I am not providing a test script because of the variety of implementations and the variable nature of using threads (you can't know which will finish first).  But I do provide an example under ref/1, with output like so:

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
    
It just prints out the index and the value in nearest_dinos.  Your mileage may vary slightly, but be wary if it is *way* off.  I will be grading by hand and assigning one of three possible scores:

Check) Full six points of credit.  You use pthreads correctly and store and output some reasonable results.  Have some way to adjust the number of threads like via setting NUM_THREADS to whatever value.

Check Minus) Two points of credit.  Elements of using pthreads are present but not correct.  Output is not reasonable or otherwise seems to be baloney.  Code has major errors but attempts were made.

No Check) Zero points.  Code includes no elements of using pthreads.  Code is a giant spaghetti that I can't read.  Doesn't even compile.  Etc.
