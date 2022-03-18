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

# PARSE ARGUMENTS USING ARGPARSE HERE
# Do not make other changes to the code.
# Be sure to pass descr and examples as description and epilogue parameters.
parser = argparse.ArgumentParser(description = descr, epilog=examples, formatter_class=argparse.RawTextHelpFormatter)
parser.add_argument('-f', dest='datfile', type=str, default='dinosaur.dat')
parser.add_argument('-y', dest='preys', action='append')
parser.add_argument('-r', dest='preds', action='append')
args = parser.parse_args()

dinos = dinodata.dinodata(args.preys, args.preds)

dinos.readdinos(args.datfile)
(num_prey, num_pred, yrrat) = dinos.preypredrat()

print(f'number of prey: {num_prey}')
print(f'number of predator: {num_pred}')

print(f'ratio: {yrrat}')
