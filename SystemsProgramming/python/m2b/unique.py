#!/usr/bin/env python3

import sys
import argparse

descr="This program will only output the unique lines in a given text file."

parser = argparse.ArgumentParser(description=descr, formatter_class=argparse.RawTextHelpFormatter)

parser.add_argument('-c', action='store_true', help='Prefix lines by the number of occurrences')
parser.add_argument('-i', action='store_true', help='Ignore differences in case when comparing, prints out full line in lowercase')

group = parser.add_mutually_exclusive_group(required=False)
group.add_argument('-d', action='store_true', help='Only print duplicate lines')
group.add_argument('-u', action='store_true', help='Only print unique lines')

args=parser.parse_args()

uniq_dict = dict()

for line in sys.stdin:
    currline = line.rstrip()
    if(args.i):
        currline = currline.lower()
    try:
        uniq_dict[currline] = uniq_dict[currline] + 1
    except KeyError as ex:
        uniq_dict[currline] = 1

for key in list(uniq_dict):
    if (uniq_dict[key] > 1 and args.d) or (uniq_dict[key] == 1 and args.u) or (not args.d and not args.u):
        if args.c:
            print(f'{uniq_dict[key]} ', end='')
        print(key)
