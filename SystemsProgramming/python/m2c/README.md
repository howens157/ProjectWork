# Python Milestone Part C - Parallel Password Cracker

Write a password cracker and measure performance differences due to parallelism.  A password cracker is a tool that, given an encrypted password, tries thousands, millions, even billions of possible passwords against that encrypted password.  Eventually it finds a match.

Earlier in the class I gave you a file of cleartext passwords that had been lifted from Yahoo and released by news websites online.  It provides an invaluable dataset for studying how people write passwords, even if we detest the way the dataset was released.  Fortunately this is not how passwords usually are leaked.  Usually crooks steal the encrypted versions of passwords, because usually websites do not store cleartext passwords.

Usually how websites work is that you enter a cleartext password, then the website encrypts the password with some algorithm, say, MD5.  Let's say my password is 'akagi'.  If you encrypt this with MD5 it becomes '3ffdca867bd294a890bef8eec470824f'.  This process is known as one-way encryption because going from cleartext to encrypted is fast, but going from the encrypted version to cleartext is extremely difficult.

So websites store the '3ffdca867bd294a890bef8eec470824f' in a database.  Then when you enter the password 'akagi' to login, the website encrypts whatever you typed in and sees if the encrypted version is the same as what is stored in the database.  This way if crooks steal the database, they have your encrypted password but cannot easily obtain the cleartext password.  This provides some protection against crooks stealing your password from one site and using it elsewhere.

But this is where a brute force password cracker comes in.  Such a program will try millions and millions of possible passwords against an encrypted one.

Consider this example:

Imagine you have an encrypted version of a password, say '3ffdca867bd294a890bef8eec470824f'.  And let's say I try every possible five letter, lowercase word:

aaaaa -> 594f803b380a41396ed63dca39503542
aaaab -> 11649b4394d09e4aba132ad49bd1e7db
aaaac -> 16a08135a7d44b3d6beac2d84f9067c6
...
aaaba -> 01b4c32db5e1e8145ec63cb3f9ee015e
aaabb -> eddba504a0b22786dfd862465202e873
aaabc -> 4020b5f131e0770179a526362b5b8dc2
...
(much later)
...
zzzzx -> 7aa7c88dc17cb5556ff254617fc8d217
zzzzy -> 203a66a9a3b53863a5b821bbc1a63539
zzzzz -> 95ebc3c7b3b9f1d2c40fec14415d3cb8

That is 26^5 = 11,881,376 possible passwords!  If it took, say, 1/100th of a second to encrypt one password, that would be 11,881,376 / 100  = 118,814 seconds = 33 hours of compute time in the worst case.

If our password is 'akagi', then we will not have to compute everything.  We'd eventually get to:

akagg -> cc1ce17507f3b735dc77a9df09515389
akagh -> b27bf2b5ac3f400b326a7f370de98721
akagi -> 3ffdca867bd294a890bef8eec470824f

And we'd see that the '3ffdca867bd294a890bef8eec470824f' matches the encrypted password, so we'd know the cleartext password must be 'akagi'.

These days of course we have multicore CPUs, so we can process several at a time.  With four cores running, we could get a maximum theoretical speedup of four.  I.e. it would only take 25% the amount of time, 8.25 hours instead of 33.  Though in practice, there is overhead in managing the workload, so realworld speedup will be something less than 4. (Note, also in practice we actually use GPUs for this, which would be much, *much*, faster.  But let's stick with the CPU for this assignment.)

# Program to Write

The program I want you to write works like this:

    $ python3 m2c.py
    usage: m2c.py [-h] -r REGEX [-t NUMTHREADS] (-f PWF | -e EPW | -p PW)

The -r flag is a regular expression.  Your program should try every possible string of that regex.  By "try" I mean encrypt that string and see if it matches a provided encrypted password.

Hint: there is a Python module called exrex which generates all possible matches to a given regex:
    https://github.com/asciimoo/exrex
I already installed this on the student machines for you.  Check the link above for documentation on how to use it.

The -f, -e, and -p flags are a mutually exclusive flag group.  You can do some sleuthing online for how to make argparse create mutually exclusive flags.  What they mean is:

    -f  If this flag is specified, read encrypted passwords from a file.  Each line of this file would have one encrypted password in it.  Every string generated for the regex should be compared to every one of the encrypted passwords in the file.
    
    -e  If this flag is specified, use a single provided encrypted password from the command line.
    
    -p  If this flag is specified, read a cleartext password from the command line and encrypt it, then try to crack the encrypted version.  This flag is for debug purposes only, since obviously the cleartext password is already known.
    
Examples:

    $ python3 m2c.py -r '[a-z]{5}' -e 3ffdca867bd294a890bef8eec470824f

The example above would check the encrypted password '3ffdca867bd294a890bef8eec470824f' against every five letter, lowercase word.

    $ python3 m2c.py -r '[a-z]{5}[0-9]{2}' -p akagi88

The example above would encrypt the password akagi88, then use the encrypted version against every possible match of a five letter, lowercase word followed by two digits.

    $ python3 m2c.py -r '[a-zA-Z]{3}' -f pw.txt

Where pw.txt is something like:

    47bce5c74f589f4867dbd57e9ca9f808
    e65075d550f9b5bf9992fa1d71a131be
    8010fd0f87d3aaa0ea48aa78948c081e
    9b462ca7da89153d0106bffea35b4fa1
    
The example above would read the four encrypted passwords from pw.txt.  Then it would loop through every three letter upper or lowercase word and check them against the four encrypted passwords.  The program would continue until all four passwords were cracked or until no more regex matches are possible.

# How do I encrypt things for this assignment?

The encryption in this assignment is different from the encryption you used in D11.  It's easier.  There is a module called hashlib with a function called md5().  Give that function a utf-8 encoded bytestring.  It will give you back an encrypted password object.  What you want is a hexidecimal digest of that password object.  A hexidecimal digest is just a string that represents the encrypted password.  There is a function called hexdigest() that belongs to encrypted password objects.

I am not giving you code examples for everything in this assignment.  You can poke about online for how to use the libraries, just as you would outside of class.

# How do I parallelize things?

You will need to use the library called ray.  Some documentation is here:
    https://github.com/ray-project/ray
I already installed it on the student machines for you.

You will need to implement a "thread" limit (recall that ray uses pseudothreads, which are actually separate processes).  Do NOT just spawn a million threads.  DO NOT JUST SPAWN A MILLION THREADS.  There is a parameter flag -t that specifies the number of threads.  Use a reasonable default like 2.  Try it up to 3 or 4 on some small examples.  The student machines are going to get swamped if you all run multithreads at once for hours at a time, so keep it limited.

# Tests to run

Create a file called report.txt in your work directory (call that directory m2c and put it in your dropbox root, please).  Try the following examples and report how long they take.  Be sure to report which student machine you use for your test, as well as the load averages just before running your code:

    $ uptime
    10:15:16 up 21:28,  4 users,  load average: 0.84, 0.77, 0.59

Load average is just a measure of how burdened the CPU is.  If you have a four-core CPU, then anything under 4.0 means the CPU is below capacity.
    
Case 1) crack the encrypted password '2747f01cd0b445b2a488d8391640a7a4' with the regex [a-z]{5} with 1 thread, 2 threads, and 4 threads.

Case 2) crack the encrypted password '8010fd0f87d3aaa0ea48aa78948c081e' with the regex [a-z]{3} with 1 thread, 2 threads, and 4 threads.

Case 3) crack the encrypted password '36a85c434b887cd59ccc0c03dd93d638' with the regex [a-zA-Z]{3}Castle with 1 thread, 2 threads, and 4 threads.

Note: Depending on server conditions, you may not actually see much speedup in these examples.  Others may be running their code, the machine could get swamped with process overhead, etc.  You can run your own tests to convince yourself that parallelism is really beneficial for this task.  It may involve running the code on your own computer under better controlled conditions.  Also you will want to run your code longer, so perhaps try to decrypt a difficult password instead of the short ones in my examples.

# Where to learn more about password security?

Password security is an interesting research area in and of itself.  A great place to start is the project called hashcat.  It uses many GPU optimizations and so on to really speed things up.  You can also look up rainbow tables.  Even with these optimizations, the computing power needed to crack passwords is immense.  By the way, did you know a typical electric bill for an NSA server farm is around $18m?
    https://archive.sltrib.com/article.php?id=56493868&itype=CMSID

# Rubric

Remember the specified usage:
    usage: m2c.py [-h] -r REGEX [-t NUMTHREADS] (-f PWF | -e EPW | -p PW)

This assignment is worth 20 points.  There is no test script, but grading will be applied using the following rubric:

a) 4 points.  Program tests every string that can be matched to a given regex.  I.e., use exrex to generate all possible matches to given regex and encrypt them.

b) 8 points.  Program uses a given number of 'threads' (given via the -t flag) via the ray library.  Each 'thread' operates a function that takes in a possible regex match and an encrypted password, encrypts the possible regex match, and then returns True or False depending on if the given possible regex match is the same as the encrypted password.  Your program must use exactly the provided number of threads at any one time.

c) 2 points.  Do the encryption AND the string comparison in the thread.  You DO NOT want to just return the encrypted regex match and then do the string comparision in the main thread... then you bottleneck the whole program with string comparison in a single thread.  Your program must do both the encryption and string comparison in the ray 'thread'.

d) 2 points.  -f flag functionality

e) 2 points.  -e flag functionality

f) 2 points.  -p flag functionality
