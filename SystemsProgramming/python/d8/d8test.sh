#!/bin/bash

mkdir -p wrk

WORTH=3
POINTS=0
SECONDS=0
MAXSECONDS=10

SCRIPT=$1

echo "Testing D8 ..."

printf "   %-30s ... " "Test 1"
python3 $SCRIPT > wrk/1
diff wrk/1 ref/1
if [ $? -ne 0 ]; then
	echo "Failure"
else
	echo "Success"
	let POINTS=$POINTS+3
fi

echo "Time: $SECONDS seconds (max allowed=$MAXSECONDS)"

if [ $SECONDS -gt $MAXSECONDS ]; then
	echo "  WARNING: Half credit due to time overage."
	let POINTS=$POINTS-$WORTH/2
fi

echo "Score: $POINTS / $WORTH"

