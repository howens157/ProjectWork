import sys

filename = sys.argv[1]

f = open(filename, 'r')
uniq_dict = dict()
for line in f:
    try:
        uniq_dict[line] = uniq_dict[line] + 1
    except KeyError as ex:
        print(line.rstrip())
        uniq_dict[line] = 1

