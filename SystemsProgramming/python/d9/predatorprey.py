#!/usr/bin/env python3

import re
import sys
import pdb

# some globals
num_prey = 0
num_pred = 0
datfile = "dinosaur.dat"

# ITEM 1) use the sys module to read in the two parameters
prey = sys.argv[1]
pred = sys.argv[2]
# ITEM 2) open the file and read it into a dataframe
f = open(datfile, 'r')
# open a file object for datfile

dinoframe = list()
# smartly called "dinoframe", this is a dataframe of the dinosaur.dat file
# every row in the dataframe should be a line in dinosaur.dat 
# every column in the dataframe should be a column in dinosaur.dat, delimited by \t

# be sure to keep a headers list that is the first line of the file!
# don't want the headers in the dataframe!
headers = f.readline().split('\t')

# write a for loop to iterate through the entire file one line at a time
# for...
for line in f:
    # split the line by \t
    currline = line.split('\t')
    # be sure to check if the number of items in the line is the same as the number of headers!
    if len(currline) == len(headers):
        dinoframe.append(currline)
    # errors could occur in the dat file that lead to misinterpretations
    # if...
        # if it's ok, we add the line to the dataframe
    

f.close()

# don't forget to close the file object

# ITEM 3) count the number of predator and prey

# write a for loop that goes through each row in the dataframe
for line in dinoframe:
    # check if the line is one of the prey
    name = line[5]
    preymatch = re.search(prey, name, re.IGNORECASE)
    predmatch = re.search(pred, name, re.IGNORECASE)
    # check if the line is one of the predator
    # ** you must use the re module's search function for this check **
    # remember the search must be case insensitive
    if preymatch:
        num_prey += 1

    if predmatch:
        num_pred += 1

# ITEM 4) calculate and print out the results, no need to change anything below this line
if num_pred != 0:
    yrrat = (num_prey / num_pred)

print(f'number of prey: {num_prey}')
print(f'number of predator: {num_pred}')

print(f'ratio: {yrrat}')

