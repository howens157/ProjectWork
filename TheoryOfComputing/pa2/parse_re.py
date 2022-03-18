#!/usr/bin/env python3
from functions import *

arguments = sys.argv
re = arguments[1]
topNode = parse(re)

scheme = nodeTraversal(topNode)
print(scheme)
