import math

class dinodata:
    def __init__(self):
        self.dinoframe = list()
        self.zipsframe = list()

    def readdinos(self, datfile):
        f = open(datfile, 'r')
        headers = f.readline().split('\t')
        errors = 0
        for line in f:
            currline = line.split('\t')
            if len(currline) == len(headers):
                self.dinoframe.append(currline)
            else:
                errors += 1
        f.close()
        return errors

    def readzips(self, datfile):
        f = open(datfile, 'r')
        first_line = f.readline().split(';')
        self.zipsframe.append(first_line)
        errors = 0
        for line in f:
            currline = line.split(';')
            if len(currline) == len(first_line):
                self.zipsframe.append(currline)
            else:
                errors += 1
        f.close()
        return errors

    def get_long_lat(self, zipcode):
        zip_long = 0
        zip_lat = 0
        for line in self.zipsframe:
            if int(line[0]) == zipcode:
                zip_long = line[4]
                zip_lat = line[3]
                city = line[1]
                state = line[2]
                break
        return float(zip_long), float(zip_lat), f'{city}, {state}'   

    def dino_finds(self, cent_long, cent_lat, max_dist):
        found_dinos = list()
        min_long = cent_long - max_dist
        max_long = cent_long + max_dist
        min_lat = cent_lat - max_dist
        max_lat = cent_lat + max_dist
        for line in self.dinoframe:
            curr_long = float(line[18])
            curr_lat = float(line[19])
            curr_max_ma = float(line[15])
            if(curr_long >= min_long and curr_long <= max_long and curr_lat >= min_lat and curr_lat <= max_lat):
                found_dinos.append([curr_long, curr_lat, curr_max_ma])
        return found_dinos      
