#!/usr/bin/env python3
from functions import *

arguments = sys.argv

m1 = NFA()
m1.read_nfa(arguments[1])

m3 = star_nfa(m1)

m3.print_nfa()
