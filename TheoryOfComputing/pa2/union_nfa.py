#!/usr/bin/env python3
from functions import *

arguments = sys.argv

m1 = NFA()
m1.read_nfa(arguments[1])

m2 = NFA()
m2.read_nfa(arguments[2])

m3 = union_nfa(m1, m2)

m3.print_nfa()
