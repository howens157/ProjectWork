#!/usr/bin/env python3
from functions import *

arguments = sys.argv
re = arguments[1]
re_nfa = re_to_nfa(re)

# process every line in the input
for line in sys.stdin:
    #strip the newline character
    string = line.strip()
    #check if it matches the re and if so, print it out
    matched = re_nfa.match(string)
    if matched:
        print(string)

