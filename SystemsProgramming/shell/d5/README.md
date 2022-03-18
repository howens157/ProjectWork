# Systems Programming Daily 5

DUE MONDAY SEPTEMBER 6 @ 11:30am (start of class)

In today's exercise, you will write a small data utility script based on the zipcodes regex you did in the previous assignment.  The objective is to learn the structure of a typical bash data utility, plus practice your shell and regex skills.

# Task 

I have given you a template for a file d5.sh that currently outputs the following help message:

===================
Usage: d5.sh <FILENAME> <REGEX_TYPE> <TO_SORT>

FILENAME    The name of the file with the password data.

REGEX_TYPE  n: letters-numbers-letters pattern
            l: letters-only pattern

SORT        s: sort the output
===================

Your job is to make the script actually do something.  Make a copy of the d5-TEMPLATE.sh file from the public/shell/d5 folder and put it in your dropbox folder under a subdirectory named d5.

The purpose of the script is to filter the passwords dataset.  Different configurations are possible based on user input.  The 'n' option tells the script to only print out passwords of the letters-numbers-letters pattern.  The 'l' option tells the script to only print out passwords that are letters only.  The *optional* 's' tells the script to sort the output.  If 's' is not given, the default is to not sort anything.  If something other than 'n' or 'l' is given for REGEX_TYPE, the default is to print everything.

Do not rely on this README alone for this assignment.  Refer to the test script for sample inputs and outputs.  Your script must adhear to the test script inputs and outputs.

For ease of reading and clearer understanding, I put a few snippets here, piped to head to limit output size:

$ ./d5.sh yahoo.clean.txt n | head -n 5
mac23c
albert1jemi
red5star
K34123413P
th3midakiFTW

$ ./d5.sh yahoo.clean.txt l | head -n 5
dublin
tomato
telematics
bamadog
zihfon

$ ./d5.sh yahoo.clean.txt l s | head -n 5
a
a
aa
aa
aa

$ ./d5.sh yahoo.clean.txt n s | head -n 5
a00000a
a00100341a
a012194t
a040894a
a041192dfl

$ ./d5.sh yahoo.clean.txt q | head -n 5
jacare01
x3n0m0r9h
madd2142
bXtYk_FA
p@$$w0rd

# Grading

This assignment is worth five points.  I have provided a test script called d5test.sh.  Hopefully the output will look like this:

$ ./d5test.sh YOUR_D5_DROPBOX_DIRECTORY
Testing D5 ...
   Test 1                         ... Success
   Test 2                         ... Success
   Test 3                         ... Success
   Test 4                         ... Success
   Test 5                         ... Success
Time: 1 seconds (max allowed=10)
Score: 5 / 5

# Notes

As many of you have noticed, it's useful to copy the entire public/shell/d5 directory to your own dropbox space, like so:

cd $HOME/esc-courses/fa21-cse-20289.01/
cp -r public/shell/d5 dropbox/shell/d5

And then do your work inside the d5 folder.  That way you get all the reference data along with the test, plus any notes/examples I've left there from lecture.
