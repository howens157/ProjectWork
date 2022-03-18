import re

import pdb

f = open('movies.dat', 'r')

headers = [ 'mid', 'name', 'year', 'genres' ]

dataframe = list()
dataframe.append(headers)

atrerrors = 0

for line in f:
	(mid, nameyear, genres) = line.split('::')

	x = re.search('(.+)\s+\(([0-9]{4})\)', nameyear)

	try:
		name = x.group(1)
		year = x.group(2)

		pdb.set_trace()

		print(f'{name} {year}')

		dataframe.append([mid, name, year, genres])
	except AttributeError as ex:
		atrerrors += 1
		pass

f.close()

print(f'attribute errors\t{atrerrors}')

