# Systems Programming Daily 3

The objective of this assignment is to practice using regular expressions in the UNIX shell.  Regex is one of the oldest and most commonly-used tools in the UNIX toolbox.  A strong understanding of regex will make you a much more powerful computer user.

DUE: August 30 at class start
POINTS: 4

## Setup

0) Obtain a copy of shakespeare.txt, which contains the complete works of William Shakespeare.  A read-only copy is located here: /escnfs/courses/fa21-cse-20289.01/public/shell/d3/shakespeare.txt

## Tasks - REGEX

Follow the steps below to write a command that outputs the speaker names in Shakespeare's plays.

Start looking at the document and noticing that speaker names come in the format:

  HELENA. My mother greets me kindly; is she well?
  CLOWN. She is not well, but yet she has her health; she's very
    merry, but yet she is not well. But thanks be given, she's very
    well, and wants nothing i' th' world; but yet she is not well.
  HELENA. If she be very well, what does she ail that she's not very
    well?
  CLOWN. Truly, she's very well indeed, but for two things.
  HELENA. What two things?
  CLOWN. One, that she's not in heaven, whither God send her quickly!
    The other, that she's in earth, from whence God send her quickly!

So, names are always capitalized.  There is always a period after them and whitespace before.  And before the whitespace, there is the line start.  After the period there is text.

1) Observing this format, write a command to output all the words that are in capital letters.  You may limit the definition of a "word" to "contiguous blocks of length 3 to 16 of upper case letters."

2) Next, write a command to do the same thing as 1, except only include words that have a period after them.

3) Now write a command to do the same thing as 2, except only include words that have whitespace before them.

4) Finally, write a command to do the same thing as 3, except only when the regex matches the start of a line.

## Tasks - PIPING

Follow these steps to filter the REGEX output such that you get only the top 30 most common speaker names.

5) Run the command from step 4, but this time sort the output.

6) Run the command from step 5, but this time filter for unique entries.  Be sure to also count the number of entries!

7) Run the command from step 6, but this time sort the output by the number of times the entries appear.  Be sure to use human-readable numeric sorting, and be sure to sort ascending so that the most common names appear first.

8) Run the command from step 7, but this time only display the top 30 names.

## Turn in

Write each of these into a separate file of the form d3-X.sh, where X is the task number.  For example, you will have a d3-1.sh which has ONE line in it only, and that line should be the command you wrote to complete task 1.

Make a directory called d3 in your dropbox, under a subdirectory called shell.  Should be something like this:

$ mkdir ~/esc-courses/fa21-cse-20289.01/dropbox/shell/d3

Place your d3-X.sh files into that d3 folder.

## Grading

I provide a test script called d3test.sh.  Run it with your netid like so:

$ ./d3test.sh DROPBOXFOLDER
Testing D3 ...
   Task 1                         ... Success
   Task 2                         ... Success
   Task 3                         ... Success
   Task 4                         ... Success
   Task 5                         ... Success
   Task 6                         ... Success
   Task 7                         ... Success
   Task 8                         ... Success
Time: 1 seconds (max allowed=10)
Score: 4 / 4

Note that this time I have put a resource cap of 10 seconds.  That should be oodles.  Half credit will be taken if the script requires more than 10 seconds to complete.

