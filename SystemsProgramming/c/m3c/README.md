# Systems Programming M3C - Soft Radio

You are a counterintelligence special agent: your job is to catch spies.  You know a few things about your targets.  You know they are hacking together a new way to communicate, and some reports of strange vehicles at the radio station lead you to suspect it is through a secret subtransmission on public radio broadcasts.

You know that they are not so dumb as to use the internet to communicate, since that would be so easy to track, and especially from their own computers.  So you revert to old fashioned police work: checking public places for clues.  At the local library you find a little gem on a book search terminal.  Someone forgot to clear their browser history.  You notice many internet searches for a simple frequency-shift key modulation in which 0s are one frequency and 1s are another.  And then the searches stop, and this page was last: https://stackoverflow.com/questions/10693590/source-for-a-good-simple-soft-modem-library/35954063

So you think you have it.  You download the code from that page (softmodem.c, already in this folder).

(If you think this scenario is far-fetched, read the book American Kingpin.  Look for how the IRS agent caught the perpetrator.)

Take a look at that program.  Compile it and see that works like this:

    ./softmodem tx 8000 0.0 message.txt message.pcm
    
That converts a data file (txt in this case) to a sound file.  The sound file can be broadcast somewhere and recorded, then converted back to data like this:

    ./softmodem rx 8000 message.pcm message.txt
    
The 8000 refers to the audio sampling rate.  The pcm file is a raw sound file.  The tx means transmit and the rx means receive.  In this case, "transmit" just means encode data as sound, and "receive" means decode sound into a data file.  Try this out and notice that the sound files can be quite long.  Up to several minutes for even small files.

The thing is, you know they can't just broadcast for minutes at a time.  They have to be smart.  They must be inserting their data into the broadcast a little at a time.  Somehow you need to capture the entire audio from the radio station and search it for pieces that might match the encoding in softmodem.c.  That program works, but right now it only reads and writes whole files.  You need some way to transmit and receive arbitrary-sized chunks of data recorded from the radio.

# M3C

In this assignment, take softmodem.c and use it to write a library called libsoftmodem.  The h file is simple, like so:

    int tx(char *msg, char **adt, int msglen);
    int rx(char **msg, char *adt, int adtlen);

Recall that softmodem.c reads whole files from disk and converts them to audio (tx) and also reads audio files and writes them to disk as data (rx).  These two functions do the same encoding, but on byte buffers (a byte buffer is just a char buffer here... one char equals one byte on our systems).

Let's look at each function:

    int tx(char *msg, char **adt, int msglen);
    
The input parameter msg is a char buffer containing a string (or other byte buffer) that you would like to convert.  The parameter msglen is the length of that string.

The parameter adt is a pointer to a byte buffer.  What needs to happen in tx() is that tx() reads the msg buffer, encodes it as audio, creates a byte buffer of the proper length (which is much greater than the message), sets adt to point to that buffer, and then returns the length of that buffer.

Take a look at this code from softmodem_test.c, which I provide to help you in this assignment:

    char *msg;
    char *nmg;
    char *adt;
    
    int msglen;
    int nmglen;
    int adtlen;
    
    if(argc < 2)
        return 1;
    
    msg = argv[1];
    msglen = strlen(msg);
    
    printf("%d %s\n", msglen, msg);
    
    // msg points to the string to be converted to audio
    // adt points to nothing right now
    
    adtlen = tx(msg, &adt, msglen);
    
    // msg still points to the string to be converted to audio
    // adt now points to a buffer of audio data of length adtlen
    
    printf("%d\n", adtlen);
    
What this code does is take a given string (argv[1], which is just provided by the command line argument) and use the tx() function to encode it as audio.  The adt variable is a pointer to a string buffer.  What you do is give tx() the ADDRESS of the adt variable.  Then tx() can malloc() whatever buffer it needs and set the value of adt to the address of the newly-malloc()'d buffer.  When tx() returns, adt will point to the buffer containing the audio data.

I'll even help you out with the line in tx() of how to do that:

    *adt = malloc(adtlen * sizeof(char));
    
See how that works?  In softmodem_test.c you create a char pointer.  Then you pass the address of that pointer as a parameter to tx().  Then inside tx(), you malloc() some space and assign the VALUE of adt to the address of the malloc()'d space.

The rx() function works the same way but in reverse.  You give it a char pointer (called nmg in this example) and the audio data (adt and adtlen were set/returned by tx()), and rx() sets nmg to the decoded message.  The rx() function return value is the length of the message.

Both rx() and tx() should return -1 on any errors.

    nmglen = rx(&nmg, adt, adtlen);
    
    // nmg now points to a NEW buffer that contains the message converted from audio data
    
    printf("%d %s\n", nmglen, nmg);
    
    // note that libsoftmodem allocates the space for adt and nmg for you, you do not 
    // need to do that yourself... but... you still have to free it yourself
    
    free(nmg);
    free(adt);

Your job is to create libsoftmodem.c, with implementations of tx() and rx().  I provide my libsoftmodem.so, so you can play around with softmodem_test.c to figure out more about what tx() and rx() do.

Don't do anything crazy.  The real purpose of this assignment is to practice reading someone else's C code and understand it well enough to use it.  You do not need to understand *anything* about FSK modulation etc. to do this assignment.  You do not need to hack and slash the program.  Instead, you are making small changes to existing functions and then writing wrapper functions to create a clean programming interface.

To be very clear, you only need to write one C file for this assignment: libsoftmodem.c.  That file is an implementation of the .h file function definitions I provide.  You will also need to write a Makefile, similar to many previous assignments, that compiles libsoftmodem.so.  You can use my reference libsoftmodem.so to get you started trying out softmodem_test.c:

    $ gcc -g -o softmodem_test softmodem_test.c -lsoftmodem -L.
    $ LD_LIBRARY_PATH=. ./softmodem_test "a secret message"
    16 a secret message
    20670
    16 a secret message
    
# Grading

This assignment is worth 20 points.  Credit is based on the provided test script.  *However* you must also obtain a clean report from valgrind for the provided softmodem_test running with *your* libsoftmodem.so:

    $ LD_LIBRARY_PATH=. valgrind ./softmodem_test "a secret message"
    ==13077== Memcheck, a memory error detector
    ==13077== Copyright (C) 2002-2017, and GNU GPL'd, by Julian Seward et al.
    ==13077== Using Valgrind-3.13.0 and LibVEX; rerun with -h for copyright info
    ==13077== Command: ./softmodem_test a\ secret\ message
    ==13077== 
    16 a secret message
    20670
    16 a secret message
    ==13077== 
    ==13077== HEAP SUMMARY:
    ==13077==     in use at exit: 0 bytes in 0 blocks
    ==13077==   total heap usage: 17 allocs, 17 frees, 99,629 bytes allocated
    ==13077== 
    ==13077== All heap blocks were freed -- no leaks are possible
    ==13077== 
    ==13077== For counts of detected and suppressed errors, rerun with: -v
    ==13077== ERROR SUMMARY: 0 errors from 0 contexts (suppressed: 0 from 0)

If valgrind doesn't give you a clean report, five points will be deducted from whatever score the test script gives you.

    $ bash m3c_test.sh 
    Testing ...
    your tx(), reference rx(), 6 points ... Success
    reference tx(), your rx(), 6 points ... Success
    your tx(), your rx(), 8 points ... Success
    Time: 0 seconds (max allowed=90)
    Score: 20 / 20

Be sure to read the test script itself to understand what is happening.  There are two supporting files called smt_tx and smt_rx.  I have provided the source code to them to help you understand the test, but I will actually be using my compiled versions (which I also provide).

Basically smt_tx uses your libsoftmodem tx() to generate an output file to store the audio information (in binary format, not as a playable pcm!).  Then smt_rx reads that file and converts it to text using your rx() function.  I put the smtadt.bin file generated by my reference solution in the ref folder.  The test file is comparing what your implementation generates to mine and making sure the interoperate.
