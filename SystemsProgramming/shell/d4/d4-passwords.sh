#!/bin/bash

# set parameter values
PASS=$1
MAX=$2
NLEN=$3
WLEN=$4
LENA=$5
LENB=$6

echo "top $MAX most-common passwords"

# a freebie! :-)
cat $PASS | sort | uniq -c | sort -r -h | head -n $MAX

echo ""
echo "top $MAX most-common number sequences of length $NLEN"

cat $PASS | sed -nE "s/.*([^0-9])([0-9]{$NLEN})([^0-9]).*/\2/p" | sort | uniq -c | sort -r -h | head -n $MAX

echo ""
echo "top $MAX most-common words of length $WLEN"

cat $PASS | sed -nE "s/.*([^a-zA-Z])([a-zA-Z]{$WLEN})([^a-zA-Z]).*/\2/p" | sort | uniq -c | sort -r -h | head -n $MAX


# calculate total (non-unique) occurrences of passwords matching letters-numbers-letters pattern
# set a variable called NUMLNL that counts the number of letters-numbers-letters matches
# remember the format VARIABLENAME=$(...)

NUMLNL=$(cat $PASS | sed -nE "/^[a-zA-Z]+[0-9]+[a-zA-Z]+$/p" | wc -l)

echo ""
echo "top $MAX most-common of pattern letters-numbers-letters (out of $NUMLNL total)"

cat $PASS | sed -nE "/^[a-zA-Z]+[0-9]+[a-zA-Z]+$/p"| sort | uniq -c | sort -r -h | head -n $MAX

echo ""
echo "number of total (non-unique) passwords that match pattern: my NUM XYZ"

cat $PASS | sed -nE "/^my[0-9]+[a-zA-Z]+$/p"| wc -l

echo ""
echo "number of occurrences of number sequences of various lengths"
echo "length num_occur"

# use a for loop that iterates over a sequence
# then inside the loop, run a command to get the number of occurrences of
# number sequences of the length $i
# then print them out along with the index
for i in $(seq $LENA $LENB)
do
    NUMSEQ=$(cat $PASS | sed -nE "/.*([^0-9])[0-9]{$i}([^0-9]).*/p" | wc -l)
    echo "$i $NUMSEQ"
done
