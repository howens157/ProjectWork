# Python Daily 13 - Dinosaur Server

Another very common task is to make data services available to many machines over a network, instead of just on one machine.  So far we've only worked with datfiles, dataframes, etc., that are read in from separated volume files.  A great example is D10: read in the dinosaur.dat file into a dataframe, then use that dataframe to calculate the prey-predator ratio of a given list of prey and predator animals.  That works but it means you have to distribute dinosaur.dat to every computer, read all that data in everytime a query is needed, and so on.

Much better would be to have the data centralized and then have queries come in via the network.  The central server can then do the calculations, keep track of the data, and send results back to client computers.  That's what you'll practice in this assignment.

# Overview

I have provided a dinoclient.py file that accesses a given host:port, sends a query string, and prints the result back to the console.  For example:

    $ python3 dinoclient.py -r tyrannosaur -y hadrosaur -n localhost -p 10005
    1025    273     3.7545787545787546

This ought to look familar.  It works just like your D10 code, except that instead of reading in dinosaur.dat itself, it creates a query string and sends it to a remote server program.  The remote server calculates the number of prey, number of predators, and the prey-predator ratio (which are all displayed by the client program: 1025, 273, 3.75...).

Here's the code for dinoclient.py:

    import socket
    import sys
    import argparse

    parser = argparse.ArgumentParser()
    parser.add_argument('-p', dest='port', type=int, default=9999, help='port number for connection')
    parser.add_argument('-n', dest='hostname', type=str, default='localhost', help='host number for connection')
    parser.add_argument('-r', dest='preds', action='append', required=True, help='single predator animal')
    parser.add_argument('-y', dest='preys', action='append', required=True, help='single prey animal')
    args = parser.parse_args()

    s = socket.socket()
    s.settimeout(60)
    s.connect((args.hostname, args.port))

    preys = ','.join(args.preys)
    preds = ','.join(args.preds)
    msg = f'{preys}|{preds}\n'

    msg = msg.encode('utf-8')

    s.send(msg)

    ret = s.recv(128)
    ret = ret.decode('utf-8')

    print(ret)

Notice the format of the string it sends:

    hadrosaur|tyrannosaur
    
The prey animal is on the left and the predator on the right.  They are separated by a bar symbol.  Multiple prey and predators can be combined via a comma, like so:
    
    hadrosaur,ceratop|tyrannosaur,raptor
    
# OK so what do I do?

Your job is to write dinoserver.py, a server/listener program that listens for a connection, waits to receive a string in the format described above, calculates the prey-predator ratio, then returns the result back to the client program.

# Task 1 - Modify your dinodata module

A very small change is needed to your dinodata module.  The interface so far required you to send the prey and predator lists as parameters to the __init__ function.  That is a nice illustration of class behavior, but it is kind of silly if you want to call preypredrat() multiple times: you'd have to re-initialize the class every time.

Change your module so that it does not need preys and preds as parameters to __init__.  Make it so that you can now just call preypredrat(preys, preds).

To summarize.  Before:
    
    __init__(self, preys, preds, password):
        ...
        
    preypredrat(self):
        ...
        
Change your module to:

    __init__(self, password):
        ...
        
    preypredrat(self, preys, preds):
        ...
        
Minor changes to the rest of your code may be requred to make this work.

# Task 2 - Make a server program that reads dinodata

Write a server program that listens on localhost on a specified port.  For example, you could call it via:

    $ python3 dinoserver.py -p 10005

And it would start listening on localhost port 10005.  In principle, your program could work on any interface and be accessible from the outside, but for simplicity and security let's keep it on localhost.

Have your program import dinodata and read in dinosaur.dat.  Then add server functionality so that it receives a string sent to it (in the prey|pred format described above), calculates the prey-predator ratio, and returns the result.

# Caveat

Watch out for encoding.  Remember you are sending bytestrings on the network, but work with regular strings elsewhere.  Specifically, remember:

    msg = 'dinosaurs are the best'

Above, msg is a regular string.

    msg = msg.encode('utf-8')

Now msg is a bytestring!  What encode does is take the regular string above and convert it into a series of bytes with the utf-8 character encoding.

    msg = msg.decode('utf-8')
    
Now msg is a regular string again.  What decode does is take the bytestring and convert it to a regular string, assuming that bytestring is utf-8 format.

To be even clearer, try this in the console:

    $ python3
    >>> msg = 'dinosaurs are the best'
    >>> type(msg)
    <class 'str'>
    >>> msg = msg.encode('utf-8')
    >>> type(msg)
    <class 'bytes'>
    >>> msg = msg.decode('utf-8')
    >>> type(msg)
    <class 'str'>
    
# Testing

Remember that you're dealing with a server program here, so you need to have that server running prior to testing!  The test script assumes your server is running on localhost on the specified port.  E.g.:

    $ bash d13test.sh 10005
    Testing  ...
    Sample 1, 1 points             ... Success
    Sample 2, 1 points             ... Success
    Sample 3, 3 points             ... Success
    Time: 0 seconds (max allowed=30)
    Score: 6 / 6

If you don't run your server beforehand, you'll get output like this:

    Testing  ...
    Sample 1, 1 points             ... Traceback (most recent call last):
    File "dinoclient.py", line 14, in <module>
        s.connect((args.hostname, args.port))
    ConnectionRefusedError: [Errno 111] Connection refused
    0a1
    > 1025  273     3.7545787545787546
    Failure
    Sample 2, 1 points             ... Traceback (most recent call last):
    File "dinoclient.py", line 14, in <module>
        s.connect((args.hostname, args.port))
    ConnectionRefusedError: [Errno 111] Connection refused
    0a1
    > 1777  273     6.509157509157509
    Failure
    Sample 3, 3 points             ... Traceback (most recent call last):
    File "dinoclient.py", line 14, in <module>
        s.connect((args.hostname, args.port))
    ConnectionRefusedError: [Errno 111] Connection refused
    0a1
    > 1777  442     4.020361990950226
    Failure
    Time: 0 seconds (max allowed=30)
    Score: 0 / 6

The connection is refused because your server isn't running!  You will get the same message if you run it on the wrong port, are bound to the wrong hostname/interface, if your server crashes, etc.  Don't be misled.
