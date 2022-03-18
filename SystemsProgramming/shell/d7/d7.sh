#!/bin/bash

# area 1) globals

SORT="sort"
DINOFILE="dinosaur.dat"

# area 2) usage message

usage() {
    cat 1>&2 <<EOF
Usage: $(basename $0) <SORT_FUNCTIONS>

SORT_FUNCTIONS are:
    -g sort geographically, south to north
    -n sort by name, alphabetically
    -a sort by maximum possible age, oldest to youngest

Examples:

Sort south-north only:
$(basename $0) dinosaur.dat -g

Sort south-north, then sort by name:
$(basename $0) dinosaur.dat -g -n

Sort by name, and then south-north:
$(basename $0) dinosaur.dat -n -g

Sort by name, then south-north, then by age:
$(basename $0) dinosaur.dat -n -g -a

EOF
}

# area 3) function area

set_sort() {
    # write a function that takes in the flag (g, n, or a)
    # and modifies the SORT variable so that the correct
    # SORT_FUNCTION is applied
    case $1 in
        g) SORT="$SORT -k20,20h";;
        n) SORT="$SORT -k6,6";;
        a) SORT="$SORT -k16,16hr";;
    esac
}

# area 4) handle parameters

while [ $# -gt 0 ]; do
	# write a case statement that
	# calls set_sort for whichever
	# flag is set in the parameters or
	# calls usage() if unknown flag
    case $1 in
        -g) set_sort "g";;
        -n) set_sort "n";;
        -a) set_sort "a";;
        *) usage 1;;
    esac
	shift
done

# do not remove, used for grading purposes
echo "$SORT"

# area 5) call the utility

cat $DINOFILE | $SORT -t $'\t' # note how we have to use an ANSI-C quoted char here for the tab


