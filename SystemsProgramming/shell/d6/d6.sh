#!/bin/bash

# area 1) globals
AWK='awk'
AWKARGS='-v FS=\t'

# area 2) functions
usage() {
    cat 2>&1 <<EOF
Usage: $(basename $0) <ZIPCODE> <L_UNITS>

Returns a list of dinosaur finds within L_UNITS of ZIPCODE.

An "L_UNIT" is one degree of longitude or latitude.  Example:

$ ./$(basename $0) 62681 1
62681 location 40.134957 -90.55222
search range:
  min latitude 39.134957
  max latitude 41.134957
  min longitude -91.55222
  max longitude -89.55222

The latitude is 40.134957 and longitude is -90.55222.  With
L_UNITS=1, this script will search between 39.134957 and
41.134957 latitude and -91.55222 and -89.55222 longitude.

The location is a town in rural Illinois.  The script will
find one sample:

1411848 occ                     195057  Numenius americanus
species 368729          Numenius americanus    species  
368729  Holocene                0.0117  0       66319   
-89.754997      40.560001       US      Illinois Peoria  
based on nearby landmark        2       outcrop  vertebrate
EOF
    exit $1
}

get_lnglat(){
    local ZIPCODE=$1
    
    # get latitude of city using awk
    LAT=$(cat zipcodes.dat | awk -v FS=';' "\$1~/$ZIPCODE/{print \$4;}")
    
    # get longitude of city using awk (same as above, just a different column
    LNG=$(cat zipcodes.dat | awk -v FS=';' "\$1~/$ZIPCODE/{print \$5;}")
}

calc_minmax_lnglat(){
    local LAT=$1
    local LNG=$2
    local DIST=$3
    
    # calculate minimum and maximum latitude and longitude
    # remember that bash can't do integers natively, so you
    # need to use 'bc'... specifically 'bc -l'
    MIN_LAT=$(echo "$LAT-$DIST" | bc -l)
    MAX_LAT=$(echo "$LAT+$DIST" | bc -l)
    
    MIN_LNG=$(echo "$LNG-$DIST" | bc -l)
    MAX_LNG=$(echo "$LNG+$DIST" | bc -l)
}

set_awkprog(){
    local MIN_LAT=$1
    local MAX_LAT=$2
    local MIN_LNG=$3
    local MAX_LNG=$4

    # now build your awk program to get dinosaur finds from dinosaur.dat
    AWKPROG="NR>1 && \$19>=$MIN_LNG && \$19<=$MAX_LNG && \$20>=$MIN_LAT && \$20<=$MAX_LAT{print}" 
}

# area 3) read in and handle parameters
# note: you shouldn't have to change anything below this line!
# it is just an example for you to see how data utilities work

# first we check to make sure we have enough parameters
if [ $# -lt 2 ]; then # $# is the number of parameters
    usage 1
fi

# then, for clarity, we assign the variables names
ZIPCODE=$1
DIST=$2

# next we call our functions
get_lnglat $ZIPCODE

# (don't futz with these echo lines, I use them for grading purposes)
echo "$ZIPCODE location $LAT $LNG"

calc_minmax_lnglat $LAT $LNG $DIST

echo "search range:"
echo "  min latitude $MIN_LAT"
echo "  max latitude $MAX_LAT"

echo "  min longitude $MIN_LNG"
echo "  max longitude $MAX_LNG"

set_awkprog $MIN_LAT $MAX_LAT $MIN_LNG $MAX_LNG 

# area 4) and call awk with your awk program
cat dinosaur.dat | $AWK $AWKARGS "$AWKPROG"

# notice how this whole script is basically building up the parameters
# for a big call to awk at the end
