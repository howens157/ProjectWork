# Systems Programming Daily 28

Your objective today is to write a small server program that receives connections from a client program and then returns information about a dinosaur.

For example, if you start your d28 like this:

    $ LD_LIBRARY_PATH=. ./d28 8090
    
I should be able to connect via port 8090 (or whatever is specified on the command line).  Then I should be able to send a single integer, say 9.  Then I should receive information about that dinosaur, like this:

    50.737015 -111.549347 83.500000 70.600000 Gorgosaurus libratus

To be 100% clear, the code for creating this string is:

    sprintf(wrk, "%f %f %f %f %s\n", d->lat, d->lng, d->maxma, d->minma, d->name);
    
Where wrk is some buffer large enough to hold all this information (make it 2048 bytes, not larger or smaller) and d is a pointer to a dino struct.  If you got '9' on the socket, it would be the STRING 9, not the integer, so use strtol() to convert it to an int.  Do NOT use atoi() because atoi() does not do error checking.  Read about strtol() in the man pages and figure out how to use it.  Note that strtol() returns a LONG, which is much larger than an int, so you will need to cast it from a long to an int.

Your program must use fork() to ensure that multiple connections can be made at the same time.  Don't try to write all this at once, though.  Write a program that passes the first test in d28test.sh, which just checks for a single connection.  Then work on making it parallel.  That way you will know your networking code is correct, before tackling multiprocessing.

Start with your D24 code and make modifications to support networking and then multiprocessing.  Remember that this is five point assignment: it is meant to be possible fairly quickly.  If you find yourself writing some giant spaghetti, you are on the wrong track.

# Grading

This assignment is worth 6 points.  I provide a test script like usual.  Note that this test script REQUIRES that your d28 code be running beforehand, just like the homework on signals did.  An additional requirement is to run the test script with the port number.  I use the port number 8090 below, but pick another one if that one is taken (usually manifested by "unable to bind" errors).

So for example, in one terminal run:

    $ LD_LIBRARY_PATH=. ./d28 8090

Then in another terminal:

    $ bash d28test.sh 8090
    Testing  ...
    single connection, 3 points ... Success
    parallel connections, 3 points ... Success
    Time: 6 seconds (max allowed=20)
    Score: 6 / 6

Then you can close the d28 running in the first terminal.

While the test is running, I will be watching for zombie processes.  Be sure to wait() for all of your children to keep them from being zombies.

READ THE TEST SCRIPT.  Notice that is uses d28_asker and d28_asker_fork.  I provide the source code for these programs, so you can see exactly what input your program needs to handle.
