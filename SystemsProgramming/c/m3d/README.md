# Systems Programming M3D - Decoding Messages

Well now, aren't you clever?  You made a libsoftmodem that can decode messages in the format that your target spies are using.  Great work, agent.  Now you get a break in your case.

Hard work by your colleagues studying the radio station has discovered single object file called libsecretradio.so.  That turns out to be a library that uses the computer's sound card to receive audio information from the radio station in chunks.  The spies' code is encoding the data as audio, then sending that audio a little at a time mixed in with the regular broadcast.  Even a trained ear would not distinguish the transmission from a little extra noise here and there.

So instead of transmitting "secret message" all at once, it transmits the encoding for:

"se"
"cret"
" me"
"ssag"
"e"

or

"secre"
"t messa"
"ge"

etc.  With each transmission being a few seconds later.  Before the message is sent though, it also encodes a header with the length of the message like "AA14BB" (14 letters and spaces, does not include newline or null byte).  The header message always comes as one block i.e. it never gets choped into, say "A", "A14", "BB".  It always comes as a single unit "AA14BB".  And you know that only one message is transmitted at a time.

But then the rest of the message comes through in randomly-sized chunks at random intervals.  You only know you have the end of the message once you have received the indicated number of bytes (14, say).

An entire communication might look like:

"AA14BB"
"se"
"cret"
" me"
"ssag"
"e"
"AA12BB"
"me"
"eet at"
" dawn"

But libsecretradio receives the *audio*.  So you don't get, say "se" and "cret" in chars.  You get the audio encoding of "se" and "cret".  The library is taking care of pulling the audio from the radio broadcast for you, but you still need to decode the audio and stitch them together into a complete message.  You may get many messages.  In the above example, you have two messages:

"secret message"

and

"meet at dawn"

# M3D

Write a program that uses the provided libsecretradio.so (I am only giving you the object file) along with your libsoftmodem from m3c.  The libsecretradio interface is as follows:

    void secretradio_init();
    char * secretradio_get_audioloc();
    void secretradio_register_callback(void (*f)(int));
    void secretradio_listen();

This library is a simulation of an unbuffered driver support library, and works in almost exactly the same way.  It creates a memory space which is mapped to the virtual device.  When you read from that buffer, it is like reading directly from that device.
    
You start by calling secretradio_init() to set up data structures.

Then you call secretradio_get_audioloc(), which returns a pointer to that memory location.  Remember: writing to this memory area is like writing directly to the device, and reading from it is like reading from the device.  That means that you can't just read whenever you want!  If you do, you might read in the middle of the device writing to the memory!  You could get some garbled crazy message.

So instead, you create a CALLBACK FUNCTION.  That is a function in YOUR PROGRAM that gets called by libsecretradio whenever some data in the buffer is ready to be read.  The way this works is that you register your callback function.  You'd have some function like this:

    void radio_callback(int audlen)
    {
        // do something with the audio buffer
    }

A real device would do whatever it does, such as read information from a digital radio, and the store it in its own internal buffer.  Then when it is done, it calls back to some handler function to say, essentially "hey I just wrote some stuff now you can use it, I promise not to touch it until your handler returns."  This type of handler function is called a CALLBACK.

So how does libsecretradio know to call back to that function?  With a function pointer, of course!

    secretradio_register_callback(&radio_callback);
    
Once the audio space is set up and the callback is registered, you can tell the radio to start listening.  Notice the parameter "int debug" (in the h file).  A value of 1 tells the library to just send a single message with the word "debug".  A value of 2 tells the library to send two messages: "debug" then "ladybug".  A value of 0 tells the library to operate normally.  It will transmit five long messages.

    secretradio_listen(1);

Once you are all done listening, you tell the library to clean up after itself.  This is basically just free()ing the audio space.

    secretradio_cleanup();
    
Check out m3d-template.c:

    #include <stdio.h>
    #include <stdlib.h>
    #include <string.h>

    #include "libsoftmodem.h"
    #include "libsecretradio.h"

    char *audio;
    char *message;

    int msglen;
    int msgpos;

    int nummsg;

    void radio_callback(int audlen)
    {

    }

    int main(int argc, char **argv)
    {
        nummsg = 0;
        msgpos = 0;
        msglen = 0;
        
        secretradio_init();

        audio = secretradio_get_audioloc();
        
        secretradio_register_callback(&radio_callback);
        
        secretradio_listen(1);
        
        secretradio_cleanup();
        
        return 0;
    }


The lion's share of your coding should happen in radio_callback().  Notice that it receives the number of bytes as a parameter.  But where does it get the audio?  From the char *audio global!  And what is the meaning of that char *audio?  It is the memory address area mapped to the audio device.  It is a single memory area that gets rewritten whenever the device calls the callback.

The audio char pointer is NOT a newly-malloc()'d space on every call to callback.  It is a single space defined ONE time and then reused.

Your job is to write m3d.c so that it receives all five messages (call secretradio_listen() with a debug value of 0).  Remember that each message will start with the AA<LENGTH>BB text where <LENGTH> is an integer saying how many chars to look for in the coming message.  Those chars could come in any number of chunks, though.  For instance, "secret message" could be transmitted as:

AA14BB
se
cret
 me
ss
age

or...

AA14BB
secret me
ssage

or...

AA14BB
s
e
c
r
e
t message

And each chunk will come after some random number of seconds.  So you don't know how much or how soon the chunks will arrive.  You just know that after 14 chars, the message is over.  After that you're looking for another AA<LENGTH>BB communication.

GET THE MESSAGES AND STORE THEM AS TEXT FILES.  Your program should place each message in a text file called "msg_X.txt" where X is a number id for the message from 0 up to however many messages.

For example, for the communication:

"AA14BB"
"se"
"cret"
" me"
"ssag"
"e"
"AA12BB"
"me"
"eet at"
" dawn"

you'd have:

    $ ls messages
    msg_0.txt   msg_1.txt
    $ cat messages/msg_0.txt
    secret message
    $ cat messages/msg_1.txt
    meet at dawn
    $
    
Notice that the txt files have a newline at the end.  The message text from the radio does not.  So be sure to write a single newline just before closing the file.

It will take about four minutes for all the messages to be transmitted.  But remember that the intervals are random, so it could be longer or shorter.

# Grading

I provide a test script.  *Notice* that the test script *deletes* files inside the messages subdirectory.  Then it runs make clean and make to rebuild m3d.  Then it runs m3d.  Then it checks the contents of those files.

The tricky thing is... I didn't give you the reference output for the debug=0 input to secretradio_listen()!  The test file I gave you expects debug=2.  Again: THE TEST FILE I GAVE YOU EXPECTS DEBUG=2.

But I will be using a test script that expect debug=0.  Again: THE TEST FILE I WILL USE EXPECTS DEBUG=0.

That means that you should build your program and do your own debug testing with debug=2.  Then at the end, when you are sure everything is working, recompile with debug=0 and try it out.  Look for the five longish messages.

    $ bash m3d_test.sh 
    Testing ...
    message 0, 1 point             ... Success
    message 1, 1 point             ... Success
    Time: 6 seconds (max allowed=90)
    Score: 2 / 2
      NOTE: This is just a sample test file.  See end of README file for details.  This assignment is really worth 20 points not 2.

The real test file will be exactly the same, except it will look for five different messages.  Each one will be worth four points.  This assignment is worth 20 points total.
