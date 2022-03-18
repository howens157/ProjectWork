# Systems Programming Daily 9 - Python File Input and Data Manipulation

The objective of this assignment is to practice file input and manipulation in Python.  You will read in dinosaur.dat, store it in a "dataframe" (just a list of lists in this case), and use the data to make some calculations.

## Prey-Predator Ratio

On the practice exam, you wrote a script in bash to calculate the prey-predator ratio among different animals.  You will do the same thing on this assignment!  Except for this daily, you only need to support one predator and one prey animal, like so:

predatorprey.py <PREY> <PREDATOR>

$ python3 predatorprey.py hadrosaur tyrannosaur
number of prey: 1025
number of predator: 273
ratio: 3.7545787545787546

$ python3 predatorprey.py stegosaur allosaur
number of prey: 132
number of predator: 142
ratio: 0.9295774647887324

Unlike the exam, for this daily you don't need to do any argument parsing (the -y, -r, flags and such).  You just need to support one prey and one predator animal.

## Code

You need two modules for this assignment:

import re
import sys

Do *not* use any other modules.  No numpy or pandas yet!

Check out the template predatorprey-TEMPLATE.py for hints and guidelines.  I have divided the work into four items that are clearly labeled in the template.  You must stick to these items.  Don't go off script and start making some giant complicated spaghetti.  Don't start importing other libraries.  Just stick to the script.

## Grading

Copy the public/python/d9 folder over to your dropbox, just like you usually do.  Then create a predatorprey.py file and write your code in there.  I provide a test script as before.

$ cd ~/esc-courses/fa21-cse-20289.01/
$ cd dropbox
$ cd python
$ cp -r ~/esc-courses/fa21-cse-20289.01/public/python/d9 .
$ cd d9

$ bash d9test.sh predatorprey.py 
Testing predatorprey.py ...
   Sample 1, 1 point              ... Success
   Sample 2, 2 points             ... Success
   Sample 3, 2 points             ... Success
Time: 1 seconds (max allowed=20)
Score: 5 / 5

Please name your file predatorprey.py and do not leave your code in the template file.

Note this is *not* the same test script as the practice exam.  There are subtle differences in the way awk and Python regex works, so the results may be off by one or two between the bash and Python versions.  Also, again, we're not using the -y or -r flags yet.

