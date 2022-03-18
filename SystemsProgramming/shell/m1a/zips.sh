#!/bin/bash

# Hayden Owens
# howens@nd.edu
# 9/12/2021

# You may include some comments here for me to read while
# grading.  If you had particular trouble or thought
# something especially fun or confusing, let us know so we
# can think about it while applying partial credit.

# globals area
AWK="cat"
SORT="cat"
DELIM=";"
CITY=""
PRINT="print \$1, \$2, \$3"


DATFILE="zipcodes.dat"

# functions area, starting with usage()

usage() {
    cat 1>&2 <<EOF
Usage: $(basename $0)

-h	This help message.
-s	Sort by zipcode, city, and/or state.
-d	Set output delimiter
-l	Locate city by text.
-c	Data to display.

Available data:
a	Latitude
o	Longitude
t	Timezone offset from UTC
d	DST
g	Geolocation

Examples:

	Output sorted by state, then city, then zipcode.
	$0 -s scz

	Output sorted only by state.
	$0 -s s

	Output uses tabs instead of spaces.
	$0 -s s -d '\t'

	Display latitude and longitude with zipcodes.
	$0 -c ao

	Display timezone, longitude, then latitude.
	$0 -c toa

	Search for Rushville, sort by state/city/zip, delimit using tab.
	./zips.sh -s scz -c oa -d "\t" -l "Rushville"

EOF
    exit $1
}

set_sort(){
    local VAR=$1
    SORT="sort -t ;"
    for i in $(seq 0 $(echo "${#VAR}-1" | bc)); do
        case ${VAR:i:1} in
            z) SORT="$SORT -k1,1h";;
            c) SORT="$SORT -k2,2";;
            s) SORT="$SORT -k3,3";;
            *) usage 1;;
        esac
    done
}

set_delim(){
    DELIM=$1
}

set_locate(){
    CITY="\$2~/$1/"
}

set_data(){
    local VAR=$1
    for i in $(seq 0 $(echo "${#VAR}-1" | bc)); do
        case ${VAR:i:1} in
            a) PRINT="$PRINT, \$4";;
            o) PRINT="$PRINT, \$5";;
            t) PRINT="$PRINT, \$6";;
            d) PRINT="$PRINT, \$7";;
            g) PRINT="$PRINT, \$8";;
            *) usage 1;;
        esac
    done
}
# read parameters

while [ $# -gt 0 ]; do
	case $1 in
	    -h) usage 0;;
        -s) shift; set_sort $1;;
        -d) shift; set_delim $1;;
        -l) shift; set_locate "$1";;
        -c) shift; set_data $1;;
	    *) usage 1;;
	esac
	shift
done

# call the utilities

cat "$DATFILE" | $SORT | awk -v FS=';' -v OFS="$DELIM" "$CITY"'{'"$PRINT"';}'

# Whew! Thanks for working hard on this assignment.
#
# Here's an ASCII fish I thought was cute:
#
#                O  o
#           _\_   o
# >('>   \\/  o\ .
#        //\___=
#           ''
# I especially like the little fish behind the big one.
# 
# I put it here as a reminder of how simple things, like
# a couple greater-than signs and a paren, can have
# a big meaning.  As you gain knowledge of this material,
# you will throw off the yoke put on you by most
# operating systems like Android, iOS, Windows, and yes
# even MacOS.  Those OSes are designed to keep you from
# making mistakes, but also to keep you contained.  They
# have you right where they want you, in your cell.
#
# Learn well, take the power into your own hands, and
# be free.
#
#            - cmc

