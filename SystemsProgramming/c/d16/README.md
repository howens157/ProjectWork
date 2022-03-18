# C - Compiling & Linking Part 1

There is an impression in the world that C is "hard" compared to a lot of languages.  One of the biggest reasons for that is confusion over the compilation process.  People get used to being pampered by Python, Javascript, and other interpreted languages.  As a result, they never really learn what the compilation process is and that lack of understanding leads to bugs and problems later.  Naturally, people blame "the computer" or "the language" rather than themselves.

Today I want you to practice the compilation process in C along with some light C programming.  I am providing you a small library called littlelib.  Here is the contents of littlelib.h:

    int init_littlelib();
    int randint(int lower, int upper);
    int is_prime(int n);

The first function is just an initialization function to set up some values for the other functions.  It must be called before calling any other functions in littlelib.  Not all libraries have initialization functions, but many do.
    
The second function takes in a lower and upper bound and gives back a number n where (lower <= n <= upper).

The third function takes in a number n and returns 1 if n is prime and 0 if n is not prime.

Start by writing a short program that:

1) calls init_littlelib()
2) calls randint() ten times with the values lower=5 upper=800 
3) calls is_prime() each number given back by randint()
4) each time, print out a message like "NUM is prime" or "NUM is not prime"

(DON'T START CODING YET, READ TEMPLATE BELOW)

Once you're done, the output should be:

    $ LD_LIBRARY_PATH=. ./d16 
    718 is not prime
    111 is not prime
    688 is not prime
    96 is not prime
    791 is not prime
    375 is not prime
    546 is not prime
    209 is not prime
    677 is prime
    536 is not prime

Note the use of LD_LIBRARY_PATH=. prior to calling the program.  In bash, if you preface a program with an environment variable, it runs the program with that variable set just for that program.  The LD_LIBRARY_PATH environment variable tells the program where to go look for any libraries it needs.  The dot as a value means look in this directory.

Here's some code for d16.c to get you started.  Notice that in main() we call init_littlelib() right away.  Then we loop and call printprime() ten times.  Inside that function is where you should call randint() and is_prime() and printf().

    #include <stdio.h> 

    #include "littlelib.h"

    void printprime()
    {
        // YOUR CODE HERE
        printf("nothing here yet\n");
    }

    int main() 
    { 
        int i = 0;
    
        init_littlelib();
        
        for (i=0; i<10; i++)
            printprime();
        
        return 0; 
    }

Go ahead and try compiling this template with this command:

    $ gcc -Wall -o d16 d16.c
    
Uh oh!  You get an error... copy-paste the error here:

============== COPY PASTE BELOW THIS LINE ==============

/tmp/ccBfZ1y4.o: In function `main':
d16.c:(.text+0x25): undefined reference to `init_littlelib'
collect2: error: ld returned 1 exit status

============== COPY PASTE ABOVE THIS LINE ==============

Looks like it doesn't know where to find the functions it needs.  It's in the library.  But we need to tell it that.  Try this next:

    $ gcc -Wall -o d16 d16.c -llittlelib

Still an error!?  Copy-paste it:
    
============== COPY PASTE BELOW THIS LINE ==============

/usr/bin/ld: cannot find -llittlelib
collect2: error: ld returned 1 exit status

============== COPY PASTE ABOVE THIS LINE ==============

Ok fine, so we need to tell it where to find littlelib.  How about this:

    $ gcc -Wall -o d16 d16.c -llittlelib -L.
    
Whew!  It should work now!
    
-Wall           means "print out all warnings not just select ones"
-o d16          means "set the output filename to d16"
d16.c           is the list of source files, in this case just a single source file
-llittlelib     is the name of the library (littlelib.so)
-L .            means "look in the current directory for the shared library file"

If you run the template, you should get this:

    $ ./d16-template 
    nothing here yet
    nothing here yet
    nothing here yet
    nothing here yet
    nothing here yet
    nothing here yet
    nothing here yet
    nothing here yet
    nothing here yet
    nothing here yet

Now you need to write printprime() the functions in littlelib to get the right output.  I provide a test script like you're used to!

    $ bash d16test.sh 
    Testing  ...
    Sample 1, 3 points             ... Success
    Time: 0 seconds (max allowed=5)
    Score: 3 / 3


# Welcome to C!

Learning C well will make you a much more serious computer scientist.  Python, Javascript, and other high level languages are fine languages.  But if that is all you know, it's like driving a motor boat around for an hour and calling yourself Captain.  Yeah, I guess *technically* you are a captain, kind of.  I mean, if you call yourself that most people will smile and nod, and try not to get into an argument with you.

             o_.-._                            .   . .
             |_.-._|                        .  . .  ' 
             |                         . '. '
        ^^^^^^^                       :'
^^^ ^^^ | : : | ^^^ ^^^              .;
| |_| |_|     |_| |_| |              ..
|                     |           .--++-.
|  :   :  .-.  :   :  |        .__|]_[]_'-...... 
|         | |         |         \ o o o '=-=-=-!
"'"''""'"""''''"'"''""'''~~~~~~~~\_____________|~~~~

But they won't take you seriously.  Maybe they won't confront you, but they will know, and really, if you are honest with yourself, *you* will know.  You know you are no "captain."

Now maybe if your boat is 30 feet long and you have hundreds of hours of practice, you are on your way to being taken seriously.

And if your boat is 100 feet long and you command a crew of four, well, now you are getting to be a real Captain.

If your "boat" is an aircraft carrier with a crew of three thousand, you are definitely a serious Captain.

You get my point.  You can't float around in the Python paddleboat your whole life and expect to be taken seriously.  Learn C.
