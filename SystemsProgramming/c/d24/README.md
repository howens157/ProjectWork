# Systems Programming Daily 24

Your objective today is to run your D23 and receive a clean report from Valgrind.  A clean report means NO memory leaks or other memory issues.  Start by copying your D23 code into the D24 folder and renaming d23.c to d24.c.  Update your Makefile accordingly.  Also make sure your Makefile compiles with the -g flag, to enable debug information.  Then:

    $ make clean
    $ make
    $ LD_LIBRARY_PATH=. valgrind --leak-check=full ./d24
    
An example of a clean report is:
    
    ==16843== Memcheck, a memory error detector
    ==16843== Copyright (C) 2002-2017, and GNU GPL'd, by Julian Seward et al.
    ==16843== Using Valgrind-3.13.0 and LibVEX; rerun with -h for copyright info
    ==16843== Command: ./d24
    ==16843== 
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
    ==16843== 
    ==16843== HEAP SUMMARY:
    ==16843==     in use at exit: 552 bytes in 1 blocks
    ==16843==   total heap usage: 892,584 allocs, 892,583 frees, 1,768,707,560 bytes allocated
    ==16843== 
    ==16843== LEAK SUMMARY:
    ==16843==    definitely lost: 0 bytes in 0 blocks
    ==16843==    indirectly lost: 0 bytes in 0 blocks
    ==16843==      possibly lost: 0 bytes in 0 blocks
    ==16843==    still reachable: 552 bytes in 1 blocks
    ==16843==         suppressed: 0 bytes in 0 blocks
    ==16843== Reachable blocks (those to which a pointer was found) are not shown.
    ==16843== To see them, rerun with: --leak-check=full --show-leak-kinds=all
    ==16843== 
    ==16843== For counts of detected and suppressed errors, rerun with: -v
    ==16843== ERROR SUMMARY: 0 errors from 0 contexts (suppressed: 0 from 0)
    
# Hints

Some types of memory issues you're likely to hit are:
    
    ==15532== Invalid read of size 1

This usually is valgrind telling you that you're trying to read something where you are technically allowed to, but it is out of bounds.  Often it is an array.  Something like this:

    char *s = malloc(128 * sizeof(char));
    int i = 128;
    char c = s[i];
    
If the program doesn't crash, it means that technically you were allowed to read from memory location s[128].  But that space wasn't allocated to that array.  Remember, indicies only go from 0 to 127 in that example.  128 is one beyond that.  That space is in the heap and you are technically allowed to read it since it is in your memory space, but it wasn't allocated for that purpose, so valgrind gives you a warning.

You don't want to leave bugs like this because it can mean you read from adjacent arrays on accident!  Let's say you did:

    char *s = malloc(128 * sizeof(char));
    char *t = malloc(128 * sizeof(char));
    int i = 128;
    t[0] = 'Q';
    char c = s[i];
    
If it so happened that t was allocated just after s in memory (which is not a guarantee, but it is likely), then reading s[128] would actually be reading location t[0]!  Almost certainly not what you want!

Another example is:

    ==15532== Conditional jump or move depends on uninitialized values
    
This usually means you read from some value outside malloc()'d space (similar to the previous warning), and then used that value inside an if, for, or a while block.  For example:

    char *t = malloc(3 * sizeof(char));
    t++;
    t++;
    t++;
    t++;
    if(t == '\n')
        // do something
        
The char pointer t starts off pointing to the beginning of a 3 bytes malloc()'d.  Then it points to the second location that was malloc()'d.  Then the third.  Then the fourth and fifth?  "Wait... those were not allocated," Valgrind says.

Finally, you're likely to have memory leaks.  You fix these by free()'ing any space that you malloc()'d.  Just be sure not to free() the space too early, otherwise you could end up with a reallocation bug.  A reallocation bug happens if you do something like this:

    char *s = malloc(128 * sizeof(char));
    free(s);
    char *t = malloc(128 * sizeof(char));
    t[0] = 'Q';
    char c = s[0];

The pointer s points to allocated space which is then free()'d.  Then t is allocated.  But it is possible, even likely, that t will be allocated the same space which was just free()'d.  No bug happens immediately because you can still access s[0]... it's just that now s[0] and t[0] refer to the same memory!  You can imagine how this would be a problem if you end up using s and t for different things.

An example of a memory leak I expect to see a lot is in readdinos() after calling split().  The split() function malloc()s a bunch of stuff which is then returned (via in-place modification of the splits array) to readdinos().  I suspect most people didn't free() anything, which means all that space allocated by split() is used once in readdinos().  The next call to split() will just malloc() yet more space.

# Grading

This assignment is worth 6 points.  Two conditions must be met for full credit:

1) The d24test.sh test must pass, and
2) The valgrind command listed above must report zero errors.

Note that d24test.sh is identical to d23test.sh, except with a much longer time allowance.  You may need to check/clear buffers which can sometimes add a lot of time.  However, your program must still produce the same output as in d23 -- you can't break the program in the process of fixing memory errors.
