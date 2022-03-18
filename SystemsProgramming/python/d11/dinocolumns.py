#!/usr/bin/env python3

import sys
import dinodata
import argparse

descr = 'Calculates Prey-Predator Ratio of specified animals'
examples = """Filters dinosaur data and writes to an (optionally encrypted) file."""

parser = argparse.ArgumentParser(description=descr, epilog=examples, formatter_class=argparse.RawTextHelpFormatter)
parser.add_argument('-d', dest='datfile_in', type=str, default='dinosaur.dat', help='data file to read')
parser.add_argument('-o', dest='datfile_out', type=str, default='dinosmini.dat', help='data file to write')
parser.add_argument('-e', dest='encryptpw', type=str, default='', help='encrypt, if specified, with given password')
parser.add_argument('-c', dest='columns', type=str, required=True, help='columns to write')
parser.add_argument('-l', dest='limit', type=int, default=10, help='maximum entries to write')
args = parser.parse_args()

encryptpw = args.encryptpw
datfile_in = args.datfile_in
datfile_out = args.datfile_out
columns = args.columns
limit = args.limit

columns = columns.split(',')
columns = [int(e) for e in columns]

dinos = dinodata.dinodata([], [], encryptpw)

dinos.readdinos(datfile_in)

dinos.save_df(datfile_out, columns, limit)
