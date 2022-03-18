#!/usr/bin/env python3
from functions import *

arguments = sys.argv
w = arguments[1]

my_nfa = string_nfa(w)
my_nfa.print_nfa()


