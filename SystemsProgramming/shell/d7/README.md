# Systems Programming Daily 7

Today you will write a script that uses sort to sort dinosaur.dat in user-specified order.  Check out the usage doc:

===================
Usage: d7.sh <SORT_FUNCTIONS>

SORT_FUNCTIONS are:
    -g sort geographically, south to north
    -n sort by name, alphabetically
    -a sort by maximum possible age, oldest to youngest

Examples:

Sort south-north only:
d7.sh -g

Sort south-north, then sort by name:
d7.sh -g -n

Sort by name, and then south-north:
d7.sh -n -g

Sort by name, then south-north, then by age:
d7.sh -n -g -a
===================

Remember that dinosaur.dat is layed out like this:

occurrence_no   record_type     reid_no flags   collection_no   identified_name identified_rank identified_no  difference       accepted_name   accepted_attr   accepted_rank   accepted_no     early_interval  late_interval  max_ma   min_ma  reference_no    lng     lat     cc      state   county  latlng_basis    latlng_precision       geogscale        geogcomments    research_group

And now notice that there are columns for max_ma, lat, and identified_name.  The column identified_name is in position 6, for example.

If you run:
$ d7.sh -n

it should sort by column 6.

If you run:

$ d7.sh -g

it should sort by the column for latitude, least to greatest (which will be south to north).

If you run:

$ d7.sh -a

it should sort by the column for max_ma, which is the maximum believed possible age in millions of years.  Sort from oldest to youngest.

It should be possible to sort by multiple ones, depending on the order of parameters.

$ d7.sh -n -g -a

should sort by name, then by geography (south-north), then by maximum possible age.

## Grading

As many of you have noticed, it's useful to copy the entire public/shell/d7 directory to your own dropbox space, like so:

cd $HOME/esc-courses/fa21-cse-20289.01/
cp -r public/shell/d7 dropbox/shell/d7

And then do your work inside the d7 folder.  That way you get all the reference data along with the test, plus any notes/examples I've left there from lecture.

As usual I provide a test script called d7test.sh.  Check out the examples in that test and the folder ref.  Note that I pipe the results through awk for easier reading.  Your script should not do anything with awk right now.  I just pipe them in the test script.  You'll want to do the same when debugging.

Much of this assignent should help you with the milestones.

$ bash d7test.sh d7.sh 
Testing D7 ...
   Test 1                         ... Success
   Test 2                         ... Success
   Test 3                         ... Success
Time: 1 seconds (max allowed=60)
Score: 3 / 3

