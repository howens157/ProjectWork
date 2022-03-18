from covdemolib import CovDemoLib

import sys

num = int(sys.argv[1])

cdl = CovDemoLib()

p = cdl.primeq(num)

print(p)

