#!/usr/bin/env python3
from functions import *

arguments = sys.argv
re = arguments[1]

reNFA = re_to_nfa(re)
reNFA.print_nfa()
