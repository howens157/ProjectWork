# Systems Programming Daily 25

Today you will practice using signals to provoke activity in another process.  Recall that every process has a process id (pid).  You can get that pid using the 'ps' tool at the command line or programmatically using getpid() like so:

    #include <stdio.h>
    #include <unistd.h>

    int main()
    {
        int pid = getpid();
        printf("%d\n", pid);
    }

Each process also accepts different signals.  You can see a list here:

    $ man 7 signal
    
An example of a signal is SIGINT, which is what is sent to a program when you hit Ctrl-C on the keyboard.  When a process gets SIGINT, a special handler function is executed for that signal.  The default handler for SIGINT just closes the program.  But you can override the default if you need to, say, clean up some open file handlers or network connections prior to closing.

In this assignment, start by copying your D24 code into the d25 directory.  Rename d24.c to d25.c.  Make appropriate modifications to the Makefile.  Your job is to modify d25.c so that:

1) When a SIGUSR1 signal is received:

    a) Read a file called dinonum.bin for a single integer DINONUM.  This integer will be used as the index in the array of dinosaurs.  E.g. dinos[DINONUM]
    
    b) Save that dinosaur to dino_DINONUM.bin.  For example if you read 91 from dinonum.bin, then you'd save dinos[91] to dino_91.bin.  Remember you wrote save_dino() in a previous assignment.
    
2) When a SIGUSR2 signal is received:

    a) Read dinonum.bin for DINONUM.
    
    b) Read dino_DINONUM.bin for the dinosaur data and put that new data into dinos[DINONUM].

# Hints
    
You must use the sigaction() function to set a sigaction handler for SIGUSR1 and SIGUSR2.  If you go Googling, you'll find tons of resources for signal().  That's not what you want.  The sigaction() function allows you to access information about who signaled you.  Here's an example: https://www.linuxprogrammingblog.com/code-examples/sigaction

Remember you wrote load_dino() and save_dino() in a previous assignment.  Copy them into libdinos.c.  Make appropriate changes to libdinos.h so these functions are accessible by d25.c and d25_signaler.c.

Remember that the dino struct changed since you wrote load_dino() and save_dino().  You will need to slightly modify your load_dino() and save_dino() functions to support saving and loading the minma and maxma variables.

Note that I provide you with d25_signaler but I do not give you my libdinos.so.  Your libdinos.so must be interoperable with my d25_signaler.  My d25_signaler program uses only two functions from libdinos: save_dino() and load_dino().  It also uses the dino struct defined in libdinos.h.

Look up sprintf() to see how to create a string out of a number.  You will read an integer DINONUM from dinonum.bin.  But you need to create a string for the filename like "dino_91.bin".  In Python you'd do something like f'dino_{DINONUM}.bin'.  In C, you use sprintf().

The dinos array will need to be available to the signal handers.  This is a rare case where a global is a good idea.  Declare it in global context and then initialize it in main().

Look at d25_signaler.c to see how dinonum.bin is generated.

Put a while(1) { } loop at the end of your d25.c main function so that your program doesn't quit before receiving the signals.

# Grading

I provide a test script as usual.  You MUST have your d25 script running prior to using the test script.  Get the pid of your script and then put it as a parameter to the test script.  For example, in one ssh terminal I ran this:

    $ LD_LIBRARY_PATH=. ./d25 
    pid: 7596

Then in an other ssh terminal I ran this:

    $ bash d25test.sh 7596
    Testing ...
    Sample 1, 3 points             ... Success
    Sample 2, 2 points             ... Success
    Time: 13 seconds (max allowed=300)
    Score: 6 / 6
