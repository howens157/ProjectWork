import re
import argparse
import pdb

import dataframe

descr = 'really cool program!'

examples = """Here are some examples of how to use my program:
"""

parser = argparse.ArgumentParser(description=descr, epilog=examples, formatter_class=argparse.RawTextHelpFormatter)
parser.add_argument('-f', dest='filename', type=str, default='movies.dat', help='the filename to read')
parser.add_argument('-q', dest='somestuff', action='append')
args = parser.parse_args()

#print(args.somestuff)
#quit()






f = open(args.filename, 'r')

headers = [ 'mid', 'name', 'year', 'genres' ]

dataframe = dataframe.Dataframe()

#dataframe = list()
#dataframe.append(headers)

dataframe.set_headers(headers)

atrerrors = 0

#pdb.set_trace()

for line in f:
	(mid, nameyear, genres) = line.split('::')

	x = re.search('(.+)\s+\(([0-9]{4})\)', nameyear)

	try:
		name = x.group(1)
		year = x.group(2)

		#pdb.set_trace()

		print(f'{name} {year}')

		dataframe.append([mid, name, year, genres])
	except AttributeError as ex:
		atrerrors += 1
		pass

f.close()

print(f'attribute errors\t{atrerrors}')

