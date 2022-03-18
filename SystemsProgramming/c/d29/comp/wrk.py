from cgeodist import *

gd = cgeodist()

d = gd.geodist(41.676388, -86.250275, 90, 0)

print(d)

p = gd.palindrome('civic')

print(p)

p = dict()
p['name'] = 'Taylor Swift'
p['age'] = 31

print(p)

p = gd.setperson(p)

print(p)

people = gd.initpeople(5)

print(people)

