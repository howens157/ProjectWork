# Python Daily 12 - SSH Version Scanner

Due: 9/29/21 at classtime

A common task for network administrators, scientists, and others who work with multiple networked machines is to keep track of all the versions of a program on these machines.  The SSH server is one of those programs that often has different versions operating together on the same network.  It can happen that all these are working together just fine, but one or two are out of date and have a security bug.  So your job is to scan all the machines quickly to get a list of all the versions.

Write a small program that scans a list of hosts for their SSH version.  Your file should read a list of hosts and port numbers from a file.  Then for each host:port combination, connect to that host:port and read whatever the server sends (up to 64 bytes).  Then your program should disconnect and display the result.

For an SSH server, the data from the server will be a string with the SSH version numbers.  For example:

SSH-2.0-OpenSSH_7.4

You may assume three conditions on connection:

1) You are connected to a valid SSH server.
2) Your connection attempt is refused (a ConnectionRefusedError exception).
3) Your connection times out (a socket.timeout exception).

Your program should display each host:port followed by the SSH string, the message <connection refused>, or the message <connection timeout>.  For the given hosts.txt, the expected output is:

    $ python3 scanner.py hosts.txt 
    ash.cse.nd.edu:22             SSH-2.0-OpenSSH_7.9p1 Debian-5
    newt.cse.nd.edu:22            SSH-2.0-OpenSSH_7.6p1 Ubuntu-4ubuntu0.5
    student00.cse.nd.edu:22       SSH-2.0-OpenSSH_7.4
    student00.cse.nd.edu:90       <connection refused>
    mcmillco.com:22               SSH-2.0-OpenSSH_8.2p1 Ubuntu-4ubuntu0.3
    student02.cse.nd.edu:22       SSH-2.0-OpenSSH_7.4
    google.com:22                 <connection timeout>

Use only the modules:

    import socket
    import sys

Set the socket timeout to 2 seconds.

# hosts.txt

The hosts.txt file has one host:port per line, like so:

    ash.cse.nd.edu:22
    newt.cse.nd.edu:22
    student00.cse.nd.edu:22
    student00.cse.nd.edu:90
    mcmillco.com:22
    student02.cse.nd.edu:22
    google.com:22

Your program should read each line of the specified file.  Split each line so you get the host and port.  Then try to connect to the host via that port.  Catch any ConnectionRefusedError and socket.timeout exceptions.
fi
When I say "Catch any ... exceptions", I mean use a try-except block.  Do NOT just say:

    try:
    ...
    except Exception as ex:
    ...

Instead, use the actual exception types to do something different for each exception.  In this case, you'll want to print out a <connection refused> or <connection timeout> message.

You can read in the filename via a positional argument, i.e. sys.argv instead of using the argparse library.

# Pretty printing

Notice the output format above has nice, clean whitespace between the host:port and the SSH version string.  You can get this in Python using f-strings like so:

    print(f'{line:<30s}{hostver}')

Where line is the host:port string and hostver is the SSH version string.  The <30s part means that the string (the host:port in this case) must be at least 30 chars long.  If it is not that long, fill the rest with spaces.  Oftentimes you'll hear this called "pretty printing" because it makes the output easier to read.

# Testing

As usual, I provide a test file called d12test.sh.

    $ bash d12test.sh scanner.py 
    Testing scanner.py ...
    Sample 1, 1 points             ... Success
    Sample 2, 1 points             ... Success
    Sample 3, 1 points             ... Success
    Sample 4, 2 points             ... Success
    Time: 2 seconds (max allowed=600)
    Score: 5 / 5

# Turnin

As a courtesy to me, please call your script scanner.py and place it in a directory called d12 in your dropbox under your python/ subdirectory.  Please do not put it in, e.g., randomsomething/d12 or name it scanner-LASTNAME.py and so on.

Will I count off for that?  No, I am not some kind of pedantic monster trying to take off points over tiny things like filenames.  But it sure would help me find your files faster if I know they are all in the right place.  It's just a favor I am asking.
