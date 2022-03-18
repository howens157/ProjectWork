#!/bin/bash

mkdir -p wrk

WORTH=3
POINTS=0
SECONDS=0
MAXSECONDS=60

SCRIPT=$1

echo "Testing D7 ..."

# tests getting zipcode lat/lng
printf "   %-30s ... " "Test 1"
bash $SCRIPT -n | head -n 500 > wrk/1
diff wrk/1 ref/1
if [ $? -ne 0 ]; then
	echo "Failure"
else
	echo "Success"
	let POINTS=$POINTS+1
fi

# tests calculating min/max lat/lng
printf "   %-30s ... " "Test 2"
bash $SCRIPT -n -g -a | awk -v FS='\t' '{print $6, $16, $20}' | head -n 500 > wrk/2
diff wrk/2 ref/2
if [ $? -ne 0 ]; then
	echo "Failure"
else
	echo "Success"
	let POINTS=$POINTS+1
fi

# full test condition, few results
printf "   %-30s ... " "Test 3"
bash $SCRIPT -n -a -g | awk -v FS='\t' '{print $6, $16, $20}' | head -n 500 > wrk/3
diff wrk/3 ref/3
if [ $? -ne 0 ]; then
	echo "Failure"
else
	echo "Success"
	let POINTS=$POINTS+1
fi

echo "Time: $SECONDS seconds (max allowed=$MAXSECONDS)"

if [ $SECONDS -gt $MAXSECONDS ]; then
	echo "  WARNING: Half credit due to time overage."
	let POINTS=$POINTS-$WORTH/2
fi

echo "Score: $POINTS / $WORTH"
