#!/bin/bash

mkdir -p wrk

WORTH=4
POINTS=0
SECONDS=0
MAXSECONDS=60

SCRIPT=$1

echo "Testing D6 ..."

# tests getting zipcode lat/lng
printf "   %-30s ... " "Test 1"
bash $SCRIPT 46615 1 | head -n 1 > wrk/1
diff wrk/1 ref/1
if [ $? -ne 0 ]; then
	echo "Failure"
else
	echo "Success"
	let POINTS=$POINTS+1
fi

# tests calculating min/max lat/lng
printf "   %-30s ... " "Test 2"
bash $SCRIPT 46615 1 | tail -n 4 > wrk/2
diff wrk/2 ref/2
if [ $? -ne 0 ]; then
	echo "Failure"
else
	echo "Success"
	let POINTS=$POINTS+1
fi

# full test condition, few results
printf "   %-30s ... " "Test 3"
bash $SCRIPT 62681 1 > wrk/3
diff wrk/3 ref/3
if [ $? -ne 0 ]; then
	echo "Failure"
else
	echo "Success"
	let POINTS=$POINTS+1
fi

# full test condition, many results
printf "   %-30s ... " "Test 4"
bash $SCRIPT 46615 10 > wrk/4
diff wrk/4 ref/4
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
