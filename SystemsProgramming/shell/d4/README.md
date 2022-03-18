# Systems Programming Daily 4

DUE FRIDAY, SEPT. 3 @ 11:30AM (start of class)

Today you will practice using regular expressions in small bash scripts.  You will write two scripts that automate some text search and analysis.

# Tasks - Shakespeare

Write a script called d4-shakespeare.sh and place it in your dropbox.  Make sure this script is executable and can be run like so:

$./d4-shakespeare.sh shakespeare.txt fish
finless
plain
salt
unclean

$ ./d4-shakespeare.sh shakespeare.txt man | head -n 10
baser
better
blessed
blind
brave
British
broken
careful
common
Cotsole

./d4-shakespeare.sh shakespeare.txt cow | head -n 10
couterfeit
curst
more
natural
needless
slanderous
traitor
treacherous
very
villanous

Notice that it takes in two parameters: the name of the text file and a word.  For the purposes of this assignment, assume that the word is a noun.  You are not really doing grammar parsing in this homework.

Make your script into an adjective finder.  Look for patterns in the text of the form "a <WORD> <NOUN>" and "the <WORD> <NOUN>".  For example:

a finless fish
the plain fish
a salt fish
the unclean fish

Remember, this is regex, meaning you have to make assumptions about the input.  Let's assume that whenever you see the given noun preceeded by "the" or "a", then the word that comes between the "the" or "a" is an adjective.

Sort the adjectives and print only the unique ones.  See the test script and ref directory for example input/output.

# Tasks - Passwords

The template file d4-passwords-TEMPLATE.sh has several prompts for you to complete, similar to what we did in class.  Copy this template to your dropbox, rename it to d4-passwords.sh, and fill in the regex.

Your script must accept parameters to satisfy the usage requirements for each thing the script has to do:

./d4-passwords.sh <PASSFILE> <MAX> <NLEN> <WLEN> <LENA> <LENB>

where:

PASSFILE = password file
MAX = show top MAX results e.g. top 3 or top 10 results
NLEN = length of number sequences to look for
WLEN = length of letter sequences to look for
LENA = start length of number sequence to count
LENB = end length of number sequence to count

Example output:

./d4-passwords.sh yahoo.clean.txt 3 3 4 1 5
top 3 most-common passwords
  10654 
   1667 123456
    780 password

top 3 most-common number sequences of length 3
    410 123
     52 039
     44 456

top 3 most-common words of length 4
     49 love
     32 life
     26 ever

top 3 most-common of pattern letters-numbers-letters (out of 18672 total)
     79 ca55ablanc
     54 thomas09a
     46 passw0rd

number of total (non-unique) passwords that match pattern: my NUM XYZ
192

number of occurrences of number sequences of various lengths
length num_occur
1 26707
2 10078
3 3411
4 2287
5 290

# Grading

TWO OPTIONS FOR GRADING!  Regular expressions can be really fickle, with one or two tiny differences in the input/output.  So I provide a test script that shows what I did.  If you match this output and pass the tests, you can reliably get full credit.  But I do *not* want you spending hours and hours fighting teeny tiny regex issues when you get the big picture correct.  I have a hand grading option available if you get really close and are convinced your regex is correct or "correct enough" to match the specification/interpretation I put above.

OPTION 1:

I provide a script called d4test.sh.  Hopefully your output will look like:

$ ./d4test.sh DROPBOXFOLDER
Testing D4 ...
   Test 1                         ... Success
   Test 2                         ... Success
   Test 3                         ... Success
   Test 4                         ... Success
Time: 15 seconds (max allowed=60)
Score: 5 / 5

Note the time limit of 60 seconds.  Like before, that ought to be oodles.  It is just to make sure you don't do anything way too inefficient.

OPTION 2:

Create a file called NOTES in your d4 directory in your dropbox.  Inside that file, describe why you think your program/regex is correct.  Make a case and I will grade it by hand.  I will try to be lenient and understanding here, but you still do need to make a reasonable case.

If I do not see a NOTES file, I will assume you want Option 1.

