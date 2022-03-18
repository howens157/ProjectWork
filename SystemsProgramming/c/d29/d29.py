from cdinodata import *

cdd = cdinodata()

num_dinos = cdd.readdinos("dinosaur.dat")

dinos = cdd.get_dinos()

for i in range(0, 30):
    d = dinos[i]

    print(d['lat'], d['lng'], d['maxma'], d['minma'], d['namelen'], d['name'])
