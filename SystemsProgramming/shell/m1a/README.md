# Bash Milestone 1A

The objective of this assignment is to practice filters and shell scripting.  You will write a bash script outputs information about zipcodes around America.  Your program is a classic "data utility" in that it provides some convenience features to access data from a separated volume, but it does not obtain or analyze that data by itself.

The raw data is in a file called zipcodes.dat.  Take a peek at the first few entries:

48834;Fenwick;MI;43.141649;-85.04948;-5;1;43.141649,-85.04948
55304;Andover;MN;45.254715;-93.28652;-6;1;45.254715,-93.28652
55422;Minneapolis;MN;45.014764;-93.33965;-6;1;45.014764,-93.33965
29079;Lydia;SC;34.296064;-80.11319;-5;1;34.296064,-80.11319
29390;Duncan;SC;34.888237;-81.96902;-5;1;34.888237,-81.96902

This is a classic "separated volume", meaning a dataset in which each line/row is a data entry and each column is some information about that data entry.  Columns are delimited by a semicolon (commas, tabs, and spaces are all common alternatives).  This this dat file, the columns are:
zipcode
city
state
latitude
longitude
timezone (as an offset from UTC)
daylight savings time (1=yes, 0=no)
geolocation (just the latitude and longitude combined as a single string)

The trouble is that a giant dat file is not a very useful form of data for analysis.  Plenty of Linux utilities are available to help.  For example, one could type:

sort -k 3,3 zipcodes.dat

to sort the data by state.  Or awk could be used to resort the data, search for city names, etc.  Those utilities work but they can be complex to use.  That's where you come in...

## Overview

Write a bash script called zips.sh that implements the following features:

Usage: ./zips.sh

-h      This help message.
-s      Sort by zipcode, city, and/or state.
-d      Set output delimiter
-l      Locate city by text.
-c      Data to display.

Available data:
a       Latitude
o       Longitude
t       Timezone offset from UTC
d       DST offset from UTC
g       Geolocation

I have given you a help message in a template bash script (for the -h flag).  By default, the program should output just the zipcode, city, and state of a data entry.  The various flags of the program help add different information, output in different formats, search, etc.

## Sorting

To sort, your script must use the "sort" utility as discussed in class.  The syntax of your script should be such that:
./zips.sh -s z
should sort by zipcode.  For example, 
./zips.sh -s z | head -n 5
00210;Portsmouth;NH
00211;Portsmouth;NH
00212;Portsmouth;NH
00213;Portsmouth;NH
00214;Portsmouth;NH

The flags "-s c" should sort by city:
./zips.sh -s c | head -n 5
16820;Aaronsburg;PA
29620;Abbeville;SC
31001;Abbeville;GA
36310;Abbeville;AL
38601;Abbeville;MS

and "-s s" should sort by state:
./zips.sh -s s | head -n 5
99501;Anchorage;AK
99502;Anchorage;AK
99503;Anchorage;AK
99504;Anchorage;AK
99505;Fort Richardson;AK

The s, c, and z should be usable in any order.  Whichever flag comes first should be the highest priority.  So "scz" should sort by state, then city, then zipcode, like so:
./zips.sh -s scz | head -n 5
99546;Adak;AK
99551;Akiachak;AK
99552;Akiak;AK
99553;Akutan;AK
99554;Alakanuk;AK

## Output Delimiter

The default output delimiter is a semicolon, just like the input.  But this should be changeable.  Many times you have a program X that outputs data in one format, and program Y that uses the same data but in a slightly different format.  Data utilities like the one you're writing form the glue between these programs.

./zips.sh -d "\t" | head -n 5
48834   Fenwick MI
55304   Andover MN
55422   Minneapolis     MN
29079   Lydia   SC
29390   Duncan  SC

./zips.sh -d "|" | head -n 5
48834|Fenwick|MI
55304|Andover|MN
55422|Minneapolis|MN
29079|Lydia|SC
29390|Duncan|SC

## Searching

The program should support searching by city name.  The program should *only* search by city name.  So if one enters "MO" as a city, the program should only output cities names MO, not every entry in the state of Missouri.  Hint: Use awk and not grep.

./zips.sh -l "Notre Dame"
46556;Notre Dame;IN

./zips.sh -l "Springfield" | head -n 5
22153;Springfield;VA
62715;Springfield;IL
45502;Springfield;OH
22151;Springfield;VA
62763;Springfield;IL

./zips.sh -l "Springfield" -s s | head -n 5
72157;Springfield;AR
81073;Springfield;CO
31329;Springfield;GA
83277;Springfield;ID
62701;Springfield;IL

## Data Selection

Your script should permit custom access to the data.  By default, your script should only display the zipcode, city, and state.  But the underlying data has more than that.  Your script should be able to output requested data in any order.

Available data:
a       Latitude
o       Longitude
t       Timezone offset from UTC
d       DST
g       Geolocation

Where the a, o, etc. are inputs to the flag -c.  For example:

./zips.sh -c ao | head -n 5
48834;Fenwick;MI;43.141649;-85.04948
55304;Andover;MN;45.254715;-93.28652
55422;Minneapolis;MN;45.014764;-93.33965
29079;Lydia;SC;34.296064;-80.11319
29390;Duncan;SC;34.888237;-81.96902

But any order should work!

./zips.sh -c oa | head -n 5
48834;Fenwick;MI;-85.04948;43.141649
55304;Andover;MN;-93.28652;45.254715
55422;Minneapolis;MN;-93.33965;45.014764
29079;Lydia;SC;-80.11319;34.296064
29390;Duncan;SC;-81.96902;34.888237

The first one is   zipcode, city, state, latitude, longitude.
The second is      zipcode, city, state, longitude, latitude.

Here's one that has timezone, dst, and longitude:
./zips.sh -c tdo | head -n 5
48834;Fenwick;MI;-5;1;-85.04948
55304;Andover;MN;-6;1;-93.28652
55422;Minneapolis;MN;-6;1;-93.33965
29079;Lydia;SC;-5;1;-80.11319
29390;Duncan;SC;-5;1;-81.96902

You should be able to mix and match any flags:
./zips.sh -c ao -l "Notre Dame" -d "|"
46556|Notre Dame|IN|41.701415|-86.24498

## Testing and Grades!

I've provided a test script called zipstest.sh that automatically grades your assignment.  The reference output is in the "ref" subdirectory.  Read the test script itself to see the exact inputs used.  The script will output your expected grade along with point totals.  The diff output between your script's output (in the "wrk" subdirectory) and the reference should help you find what went wrong.

But hopefully it will look like this!

./zipstest.sh zips.sh 
Testing zips.sh ...
   Sample 1, 5 points             ... Success
   Sample 2, 2 points             ... Success
   Sample 3, 2 points             ... Success
   Sample 4, 2 points             ... Success
   Sample 5, 1 points             ... Success
   Sample 6, 1 points             ... Success
   Sample 7, 3 points             ... Success
   Sample 8, 1 points             ... Success
   Sample 9, 3 points             ... Success
Time: 1 seconds (max allowed=10)
Score: 20 / 20

Be sure to include your script as an input parameter as shown above.  Also note the time requirement.  Your script should run in a second or less.  The absolute maximum is 10 seconds.  Sometimes there is hard drive or network latency that could cost you another second or two.  But if it goes over 10 seconds, there is something really inefficient about your code.  The penalty for going over the time limit is 50% of the assignment grade, so be sure to fix any major inefficiencies.

## Turnin

As many of you have noticed, it's useful to copy the entire public/shell/m1a directory to your own dropbox space, like so:

cd $HOME/esc-courses/fa21-cse-20289.01/
cp -r public/shell/m1a dropbox/shell/m1a

And then do your work inside the m1a folder.  That way you get all the reference data along with the test, plus any notes/examples I've left there from lecture.

