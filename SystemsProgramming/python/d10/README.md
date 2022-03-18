# Systems Programming Daily 10 - Python Modules

The objective of this assignment is to gain experience in Python modules!

## Make a Module

Create a module called dinodata that performs the same tasks as D8 (that is, reading in a datfile and calculating prey-predator ratio).  Your module should have a class called dinodata in it.  That class should have two functions in addition to the initializer: readdinos and preypredrat.  The function definitions should be:

__init__
  inputs: preys - a list containing strings, each of which is a prey dinosaur name
          preds - a list containing strings, each of which is a predator dinosaur name
  outputs: none

readdinos
  inputs: datfile - a string that is the name of the file to read (default to dinosaur.dat)
  outputs: errors - an integer that reports the number of lines that were skipped due to errors

preypredrat
  inputs: none
  outputs: num_preys - number of prey animals found
           num_preds - number of predator animals found
           yrrat - prey-predator ratio

Your module should be called dinodata.py.
           
## Testing / Grading

I have provided a test script like usual, *but also* as a Python program that uses your dinodata module.  You need to edit this program so that it reads in any number of -y and -r flags using argparse.  See predatorprey-TEMPLATE.py *be sure to rename this file to predatorprey.py in your dropbox.*

        #!/usr/bin/env python3

        import sys
        import dinodata
        import argparse

        descr = 'Calculates Prey-Predator Ratio of specified animals'
        examples = """Note that -y and -r may be specified multiple times.  The number of each predator and prey should be added.

        This script does not consider time.  It only counts total occurrences of an animal in the data file that occur within the specified state.

        The search is case insensitive.

        Ratio of hadrosaur animals to tyrannosaur:
            predatorprey.sh -y hadrosaur -r tyrannosaur

        Ratio of stegasaur animals to allosaur:
            predatorprey.sh -y stegosaur -r allosaur
            
        Ratio of hadrosaur and ceratop animals to tyrannosaur:
            predatorprey.sh -y hadrosaur -y ceratop -r tyrannosaur

        Ratio of hadrosaur and ceratop animals to tyrannosaur, raptor, and allosaur:
            predatorprey.sh -y hadrosaur -y ceratop -r tyrannosaur -r raptor -r allosaur"""

Parse arguments here!  Do not make any other changes!

        dinos = dinodata.dinodata(args.preys, args.preds)

        dinos.readdinos(args.datfile)
        (num_prey, num_pred, yrrat) = dinos.preypredrat()

        print(f'number of prey: {num_prey}')
        print(f'number of predator: {num_pred}')

        print(f'ratio: {yrrat}')

Then also use the test script:

$ bash d10test.sh predatorprey.py 
Testing predatorprey.py ...
   Sample 1, 1 points             ... Success
   Sample 2, 1 points             ... Success
   Sample 3, 2 points             ... Success
   Sample 4, 2 points             ... Success
Time: 1 seconds (max allowed=60)
Score: 6 / 6

## Directory Structure

As we begin to deal with modules more, directory structure will become more and more important.  Be sure your dropbox for this assignment is in the form:

dropbox/python/d10/

(*not* dropbox/d10 or anything else, please)

Be sure you have these two files there:

predatorprey.py
dinodata.py

The predatorprey.py file should be the renamed and completed predatorprey-TEMPLATE.py.
The dinodata.py file should be your Python module.

