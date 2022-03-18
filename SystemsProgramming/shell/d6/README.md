# Systems Programming Daily 6

This is an AWKward assignment.

An auk is a type of bird.  It looks roughly like this, kinda like a penguin:

 __
( o>
///\ 
\V_/_

AWK is a UNIX program for working with delimited data files, also called "separated volumes."  Delimited just means that the has some entries of data on each line, and each line is split up by some token.  Comma delimited files are common, for example remember the zipcode data:

48834,Fenwick,MI
55304,Andover,MN
55422,Minneapolis,MN
29079,Lydia,SC
29390,Duncan,SC

Today you will awk some separated volumes.  First thing to do is understand what the script needs to do:

===================
Usage: d6-REFERENCE.sh <ZIPCODE> <L_UNITS>

Returns a list of dinosaur finds within L_UNITS of ZIPCODE.

An "L_UNIT" is one degree of longitude or latitude.  Example:

$ ./d6-REFERENCE.sh 62681 1
62681 location 40.134957 -90.55222
search range:
  min latitude 39.134957
  max latitude 41.134957
  min longitude -91.55222
  max longitude -89.55222

The latitude is 40.134957 and longitude is -90.55222.  With
L_UNITS=1, this script will search between 39.134957 and
41.134957 latitude and -91.55222 and -89.55222 longitude.

The location is a town in rural Illinois.  The script will
find one sample:

1411848 occ                     195057  Numenius americanus
species 368729          Numenius americanus    species  
368729  Holocene                0.0117  0       66319   
-89.754997      40.560001       US      Illinois Peoria  
based on nearby landmark        2       outcrop  vertebrate
===================

You can see from the usage info that it takes in a zipcode and a number of l_units, and outputs all the dinosaur finds within l_units of that zipcode.  To do this, you'll need to cross-reference two datasets: first you get the longitude and latitude from zipcodes.dat, and then you search dinosaur.dat for the dinofinds within a given distance of that latitude and longitude.

The dinosaur.dat file has data entries in columns:

occurrence_no   record_type     reid_no flags   collection_no   identified_name identified_rank identified_no  difference       accepted_name   accepted_attr   accepted_rank   accepted_no     early_interval  late_interval  max_ma   min_ma  reference_no    lng     lat     cc      state   county  latlng_basis    latlng_precision       geogscale        geogcomments    research_group

Notice lng and lat in position 19 and 20.

Now look at data in zipcodes.dat:

48834;Fenwick;MI;43.141649;-85.04948;-5;1;43.141649,-85.04948
55304;Andover;MN;45.254715;-93.28652;-6;1;45.254715,-93.28652
55422;Minneapolis;MN;45.014764;-93.33965;-6;1;45.014764,-93.33965

Latitude and longitude is in position 4 and 5.  **NOTICE** that the order in dinosaur.dat is LNG-LAT, while the order in zipcodes.dat is LAT-LNG.

So once you get the lat/lng from zipcodes.dat, you need to subtract and add the given number of L_UNITS to get the range.  Remember that bash doesn't know anything more than integers on its own.  You need to use the 'bc' utility.

Once you have the max/min lat/lng range, you need to write an awk program that prints out just the entries within that range.  Do not use a complicated loop or anything.  Use the functionality provided within awk.  The awk program should fit into one line.

## Template

I have provided a template file for you in d6-TEMPLATE.sh.  **Use this template.**  I want you to see how your awk commands and such fit into a tidy data utility format.  I don't want you to just hack something together in some spaghetti ball and then turn it in saying "yeah it's unreadable but technically it works professor."  Keep your work nice and clean, please! :-)

## Grading

As many of you have noticed, it's useful to copy the entire public/shell/d6 directory to your own dropbox space, like so:

cd $HOME/esc-courses/fa21-cse-20289.01/
cp -r public/shell/d6 dropbox/shell/d6

I provided a test script for you as d6test.sh.  This time, since there is no regex to content with, the output should be unamibiguous.  Hopefully it will look like this when you run it!

$ d6test.sh d6.sh 
Testing D6 ...
   Test 1                         ... Success
   Test 2                         ... Success
   Test 3                         ... Success
   Test 4                         ... Success
Time: 0 seconds (max allowed=60)
Score: 4 / 4

