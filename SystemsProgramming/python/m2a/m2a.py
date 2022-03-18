import dinodata
import mapmaker
import argparse
import math

descr = "This program will output a map of all dinosaur finds within a given amount of long/lat units from a given zipcode"

parser = argparse.ArgumentParser(description=descr, formatter_class=argparse.RawTextHelpFormatter)
parser.add_argument('-z', dest='cent_zipcode', type=int, help='The zipcode to search around', required = True)
parser.add_argument('-d', dest='max_dist', type=float, help='The maximum distance in latitude/longitude units to search from the zipcode', required=True)

args = parser.parse_args()
cent_zipcode = args.cent_zipcode
max_dist = args.max_dist

my_dinos = dinodata.dinodata()
my_dinos.readdinos('dinosaur.dat')
my_dinos.readzips('zipcodes.dat')

cent_long, cent_lat, city_state = my_dinos.get_long_lat(cent_zipcode)
dino_finds_to_map = my_dinos.dino_finds(cent_long, cent_lat, max_dist)

max_age = dino_finds_to_map[0][2]
min_age = max_age

for line in dino_finds_to_map:
    if line[2] > max_age:
        max_age = line[2]
    if line[2] < min_age:
        min_age = line[2]

for line in dino_finds_to_map:
    if max_age != min_age:
        red = 0 + math.ceil(255 * (line[2] - min_age)/(max_age - min_age))
        green = 0
        blue = 255 - math.ceil(255 * (line[2] - min_age)/(max_age - min_age))
    else:
        red = 255
        green = 0
        blue = 255
    color = red*pow(16, 4) + green*pow(16,2) + blue
    color = hex(color)
    color = color[2:]
    while len(color) != 6:
        color = '0' + color
    color = '#' + color
    line[2] = color

my_map_plot = mapmaker.mapmaker()
outfile = f'{cent_zipcode}_r{int(max_dist)}.png'
extents = my_map_plot.make_map(cent_long, cent_lat, dino_finds_to_map, outfile)
new_extents = (extents[0], extents[2], extents[1], extents[3])
my_map_plot.add_axes(new_extents, f'Dinosaurs near {city_state}', outfile)
