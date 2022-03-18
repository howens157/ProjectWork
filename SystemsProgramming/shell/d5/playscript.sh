#!/bin/bash

# step 1) set globals
SED="sed -nE"
UNIQ="uniq"

# step 2) function area

usage(){
    cat 1>&2 <<EOF
Usage: $(basename $0) <FILENAME> <FORMAT> <REGEX_TYPE> <NOUN>

FILENAME    The name of the file with the Shakespeare data.

FORMATS     u: print in uppercase
            l: print in lowercase

OPERATIONS  a: extract adjectives (must also specify noun)
            n: extract names

EOF
    exit $1
}

set_regex(){
    WHICHREGEX=$1
    NOUN=$2

    if [ $WHICHREGEX != 'a' ] && [ $WHICHREGEX != 'n' ]; then
        echo "invalid operation specified"
        exit 1
    fi
    
    case $WHICHREGEX in
        a) REGEX=".*\s(a|the)\s+([a-zA-Z]+)\s+($NOUN).*"; LOC="\2" ;;
        n) REGEX="^\s+\b([A-Z]{3,16})\b\..*"; LOC="\1" ;;
    esac
}

set_format(){
    FORM=$1
    
    case $FORM in
        u) OPTIONS="\U" ;;
        l) OPTIONS="\L" ;;
    esac
}

# step 3) handle parameter values

P_PASS=$1
P_FORM=$2
P_REGEX=$3
P_NOUN=$4

if [ $# -ge 3 ]; then
    set_regex $P_REGEX $P_NOUN
    set_format $P_FORM
else
    usage 1
fi

# step 4) finally, call the command(s)

cat $P_PASS | $SED "s/$REGEX/$OPTIONS$LOC/p"
