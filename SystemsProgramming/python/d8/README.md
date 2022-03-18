# Systems Programming Daily 8 - Python Intro

The objective of this assignment is to set up your Python workspace and to practice writing and executing a small script.

VALUE: 3 points
DUE: Sept. 20, 2021 at 11:30am (start of class)

## FizzBuzz

FizzBuzz is a numeracy game for kids.  The kids sit in a circle and each count from one to one hundred.  So the first kid says 1, the next says 2, and so on.

Except, if the number is divisible by 3, the kid is supposed to say "fizz."

If the number is divisible by 5, the kid is supposed to say "buzz."

If the number is divisible by both 3 and 5, the kid is supposed to say "fizzbuzz."

## Interviews

FizzBuzz was made famous in computer programming circles by a blog post a few years ago.  The post said that around 75% of applicants *fail* to write a program that can successfully play FizzBuzz.  The problem description is:

"Write a program that loops through every integer between 1 and 100.  If the integer is divisible by 3, print 'fizz' on a line by itself.  If the integer is divisible by 5, print 'buzz' on a line by itself.  If the integer is divisible by both 3 and 5, print 'fizzbuzz' on a line by itself.  If the number is divisible by neither 3 nor 5, just print the number."

For example:
1
2
fizz
4
buzz
fizz
7
8
fizz
buzz
11
fizz
13
14
fizzbuzz
16

etc...

Personally I don't see it as an exaggeration that 75% of applicants fail to write this small program.  I have heard many stories from colleagues in industry about how they use simple weed out questions like this to check if job applicants know the most basic programming skills.  Note that it may not necessarily be that the applicant cannot work the logic of the program.  It may be that the person claims to know, say, C++, but then can't write this little task in C++.  The applicant may ask to write it in some other language instead.  That's a sign that the applicant is faking some knowledge on their resume.

## Task

Write a program to complete the FizzBuzz task description above.  You will need to set up your work environment to accomplish this.

## Work Environment

Set up your work environment by adding the following line to the end of your .profile using your favorite text editor:

export PATH=$PATH:/escnfs/home/cmc/public/python/bin

Then either log out and log back in, or "source your profile" like this:
cmc@nanook:~$ source ~/.profile

Be sure the following checks out:

$ which python3
/escnfs/home/cmc/public/python/bin/python3
$ python3 --version
Python 3.6.8

So if you type "python3", your code will be pointing to my custom Python 3 installation.  We have to do this because the student machines do not have recent-enough versions of Python.  Also I have several packages installed that are necessary for the later homework assignments.

*BE CERTAIN* not to use just "python", since that is the system's Python 2.7 installation:

$ which python
/usr/bin/python
$ python --version
Python 2.7.5

Notice how that is a different version of python in a different directory.

## Script

Write a script called fizzbuzz.py and place it in a directory in your dropbox called d8.  As with the shell assignments, you probably just want to copy the public d8 folder (public/python/d8) into your dropbox and add files as needed there.  That way you can run the test:

$ cd ~/esc-courses/fa21-cse-20289.01/
$ cd dropbox
$ mkdir python
$ cd python
$ cp -r ~/esc-courses/fa21-cse-20289.01/public/python/d8 .
$ cd d8

... now do your programming in fizzbuzz.py ...

$ bash d8test.sh fizzbuzz.py 
Testing D8 ...
   Test 1                         ... Success
Time: 1 seconds (max allowed=10)
Score: 3 / 3

Notice that we still run the test with bash, but give it a Python script this time.

