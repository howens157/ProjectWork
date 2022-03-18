# Bash Milestone M1B

The objective of this homework is to practice using bash scripting to answer a specific research question.  Recall that the purpose of many bash scripts is to collate data to extract a specific piece of that data or to draw a specific conclusion.  Common examples include counting the percentage of failed login attempts from an SSH log, creating a list of highest-spending customers from a transaction record, or extracting geolocations from sensor recordings.  Typically a bash script will be written only for one or two questions at a time.  More complex analysis is (usually) performed in other languages or tools.

## The Research Question

The research question you will answer is "would dinosaur A and dinosaur B have been able to interact in the wild?"  A common path for answering a research question is to define a metric that can be calculated from data, calibrate the metric using already-established facts, and then calculate the metric on some new information.

The metric for this class will be very simple: the overlap of occurrences of one dinosaur to another dinosaur.  Let's say there are 110 instances of Allosaurus in the dataset and 76 instances of Stegosaurus.  Then let's say we want to know the dinosaur overlap (dinoverlap?) between Allosaurus and Stegosaurus.

We'd calculate this via:
  For each Allosaurus occurrence:
      For each Stegosaurus occurrence:
          If Allosaurus occurrence timespan overlaps with Stegosaurus occurrence, add one to YES
          otherwise, add one to NO

DINOVERLAP = YES / (YES + NO)

(This is not really a scientific metric, but work with me here... it is a CS class not a Palentology class. :-)

Then we can cross reference some known information.  A quick search of known Dinosaur information shows that Stegosaurus was a prey animal for Allosaurus, so we know they did actually interact.  Your program should calculate the following:

$ ./dinos.sh allosaurus stegosaurus
dinoverlap between allosaurus and stegosaurus is 54%

In our nested loop we checked 8360 possible overlaps (110 Allosaurus instances X 76 Stegosaurus instances).  Of those, about 4347 were in overlapping timespans according to the geological record.

Now let's try another one.

$ ./dinos.sh tyrannosaurus eoraptor
dinoverlap between tyrannosaurus and eoraptor is 0%

Tyrannosaurus was one of the latest dinosaurs.  It actually died out with the meteor blast 66 million years ago (way to go Tyrannosaur, it is a glorious end).  On the other hand, Eoraptor was one of the earliest, dying out the normal, less interesting way 228 million years ago.  It means Eoraptor missed seeing Tyrannosaur by 162 million years.  It's worse than our record of missing seeing Tyrannosaur by 66 million years.  Anyway, the point is that a 0% score is expected.

The metric isn't perfect though, check out:

$ ./dinos.sh tyrannosaurus stegosaurus
dinoverlap between tyrannosaurus and stegosaurus is 6%

Stegosaurus also died out long before Tyrannosaur, but there are some overlapping fossil records.  The reason can be attributed to uncertainty of date in some geological strata, errors in the database, and mixing of geological strata due to weathering.  But still, 6% is a whole lot less than 54%, so we conclude that it is far less likely that a Stegosaurus got to see a Tyrannosaur than an Allosaur.

So now let's ask some interesting questions about Tyrannosaur diet.  Did they eat Hadrosaurs (duck billed dinosaurs)?

$ ./dinos.sh hadrosaur tyrannosaurus
dinoverlap between hadrosaur and tyrannosaurus is 57%

Seems possible, since they overlapped a lot!  How about Ceratops (like the famous Triceratops)?

$ ./dinos.sh ceratop tyrannosaurus
dinoverlap between ceratop and tyrannosaurus is 57%

We see that these numbers of 57% are not that far from the 54% dinoverlap between Allosauraus and Stegosaurus, which we know from other evidence were predator and prey.

(Suddenly I am reminded of the old statistics joke, what is the chance you will see a dinosaur today?  Answer: 50%, you either see one or you don't.)

## How do we know if two dinosaurs' timeline overlapped?

Take a look at the headers in dinosaur.dat:

occurrence_no   record_type     reid_no flags   collection_no   identified_name identified_rank identified_no   difference      accepted_name   accepted_attr   accepted_rank   accepted_no     early_interval  late_interval   max_ma  min_ma  reference_no    lng     lat     cc      state   county  latlng_basis    latlng_precision        geogscale       geogcomments    research_group

max_ma and min_ma refer to "ma" or Mega-annum meaning millions of years.

$ grep -i tyrannosaurus dinosaur.dat | tail -n 1
1477772 occ                     14599   Tyrannosaurus rex       species 54833           Tyrannosaurus rex      species  54833   Lancian         70.6    66      70720   -111.000000     39.000000       US      Utah    Emery  based on political unit  1       small collection                vertebrate

Above is a sample entry in the dataset.  It's the last entry for Tyrannosaurus.  Notice that the columns for max_ma and min_ma are 70.6 and 66.  That means that this sample was found in a geological strata dated between 70.6 and 66 million years ago.  These numbers are not perfect, of course.  For one thing, numbers are rounded to the nearest hundred thousand years (like that amount of time is nothing).  Second, geological strata move around and dating techniques are not perfect, so the possible time band is quite large (4.6 million years in this case).  Third, the database may contain errors since some samples were collected 100+ years ago, published in papers in non-English languages, etc.

But, these numbers will serve for a our little project.  You can assume that these numbers are upper bounds, so if one sample appeared from 75 ma to 70.5 ma, and this sample is 70.6 ma to 66 ma, then there is an overlap of 0.1 ma.  So from our perspective writing our program, we need a function called:

overlap_ma(){
}

Which takes in the min and max ma of two samples.  The function should output a 0 for no or 1 for yes.

So the pseudocode above becomes:

  For each Allosaurus occurrence:
      For each Stegosaurus occurrence:
          YN = overlap_ma(dinoA_maxma, dinoA_minma, dinoB_maxma, dinoB_minma)
          if YN equals 1
              yes_count += 1
          else
              no_count += 1

## Efficiency

There is one small hiccup in our plan.  If a dinosaur occurs 200 times in the dataset, and another dinosaur also occurs 200 times, it means 200x200=40000 comparisons.  If that doesn't seem like a problem, remember that bash only is equipped with integer arithmetic.  We need to deal with floats.  So... you have to call a whole other process called "bc."  Recall from class how we pipe information into bc to do real arithmetic in bash scripts.  So each comparision is expensive because we have to create a whole new process for it.

Fortunately, we notice that most of the records are identical.  I.e. 70.6ma to 66ma, over and over again.  So we can use the "uniq" command to count the unique examples.  For instance:

$ awk -F '\t' '{ print $16,$17 }' dinosaur.dat | head -n 10
max_ma min_ma
55.8 37.2
55.8 37.2
150.8 132.9
130 122.46
130 122.46
83.6 72.1
145 113
83.5 70.6
83.5 70.6

awk -F '\t' '{ print $16,$17 }' dinosaur.dat | head -n 10 | uniq -c
      1 max_ma min_ma
      2 55.8 37.2
      1 150.8 132.9
      2 130 122.46
      1 83.6 72.1
      1 145 113
      2 83.5 70.6

So instead of calculating for the range 55.8-37.2 range twice, we can do it just once.  Then we multiply the number of "yes" or "no" calculations by two.  In other words, our pseudocode becomes:

  For each *unique* Allosaurus occurrence:
      NUM_ALLOSAUR = number of times this Allosaurus timespan occurs
      For each *unique* Stegosaurus occurrence:
          NUM_STEGOSAUR = number of times this Stego timespan occurs
          YN = overlap_ma(dinoA_maxma, dinoA_minma, dinoB_maxma, dinoB_minma)
          if YN equals 1
              yes_count += NUM_ALLOSAUR + NUM_STEGOSAUR
          else
              no_count += NUM_ALLOSAUR + NUM_STEGOSAUR

You can get the NUM_ALLOSAUR and NUM_STEGOSAUR numbers from the uniq output.  But, as ever, there is a problem.  The uniq command pretty-prints the output with leading whitespace.  Bash is not smart enough to know that "    2" is the same as "2".  So you need to remove that whitespace.  Now... if only there were a way to use a regular expression to eliminate leading whitespace... maybe I "sed" something about it once... (sorry for the cringy pun)

## But how do we search for Dinosaur names?

Let's do a simple approach.  Remember the headers in dinosaur.dat again:

occurrence_no   record_type     reid_no flags   collection_no   identified_name identified_rank identified_no   difference      accepted_name   accepted_attr   accepted_rank   accepted_no     early_interval  late_interval   max_ma  min_ma  reference_no    lng     lat     cc      state   county  latlng_basis    latlng_precision        geogscale       geogcomments    research_group

$ grep -i tyrannosaurus dinosaur.dat | tail -n 1
1477772 occ                     14599   Tyrannosaurus rex       species 54833           Tyrannosaurus rex      species  54833   Lancian         70.6    66      70720   -111.000000     39.000000       US      Utah    Emery  based on political unit  1       small collection                vertebrate

If you look carefully, the reid_no and flags entries are blank in many entries, like the one above.  So the sixth column contains the species name (identified_name column).

occurrence_no = 1477772
record_type = occ
reid_no = 
flags = 
collection_no = 14599
identified_name = Tyrannosaurus rex

So use awk to search the sixth column.  Just be sure to do a case-insensitive search!

## Grading

I provide a script called dinostest.sh.  Check out the "ref" subdirectory for sample outputs for the inputs in dinostest.sh.  Time requirements is 60 seconds or less on this assignment.  Hopefully your output will look like mine!

$ ./dinostest.sh dinos.sh 
Testing dinos.sh ...
   Sample 1, 2 points             ... Success
   Sample 2, 2 points             ... Success
   Sample 3, 2 points             ... Success
   Sample 4, 2 points             ... Success
   Sample 5, 2 points             ... Success
Time: 5 seconds (max allowed=60)
Score: 10 / 10

## Turnin

As many of you have noticed, it's useful to copy the entire public/shell/m1b directory to your own dropbox space, like so:

cd $HOME/esc-courses/fa21-cse-20289.01/
cp -r public/shell/m1b dropbox/shell/m1b

And then do your work inside the m1b folder.  That way you get all the reference data along with the test, plus any notes/examples I've left there from lecture.


                         .       .
                        / `.   .' \
                .---.  <    > <    >  .---.
                |    \  \ - ~ ~ - /  /    |
                 ~-..-~             ~-..-~
             \~~~\.'                    `./~~~/
   .-~~^-.    \__/                        \__/
 .'  O    \     /               /       \  \
(_____,    `._.'               |         }  \/~~~/
 `----.          /       }     |        /    \__/
       `-.      |       /      |       /      `. ,~~|
           ~-.__|      /_ - ~ ^|      /- _      `..-'   f: f:
                |     /        |     /     ~-.     `-. _||_||_
                |_____|        |_____|         ~ - . _ _ _ _ _>

