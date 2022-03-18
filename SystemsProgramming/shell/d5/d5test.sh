#!/bin/bash

mkdir -p wrk

WORTH=5
POINTS=0
SECONDS=0
MAXSECONDS=10

DROPBOX=$1

echo "Testing D5 ..."

printf "   %-30s ... " "Test 1"
bash $DROPBOX/d5.sh yahoo.clean.txt q | head -n 30 > wrk/1
diff wrk/1 ref/1
if [ $? -ne 0 ]; then
	echo "Failure"
else
	echo "Success"
	let POINTS=$POINTS+1
fi

printf "   %-30s ... " "Test 2"
bash $DROPBOX/d5.sh yahoo.clean.txt l | head -n 30 > wrk/2
diff wrk/2 ref/2
if [ $? -ne 0 ]; then
	echo "Failure"
else
	echo "Success"
	let POINTS=$POINTS+1
fi

printf "   %-30s ... " "Test 3"
bash $DROPBOX/d5.sh yahoo.clean.txt l s | head -n 30 > wrk/3
diff wrk/3 ref/3
if [ $? -ne 0 ]; then
	echo "Failure"
else
	echo "Success"
	let POINTS=$POINTS+1
fi

printf "   %-30s ... " "Test 4"
bash $DROPBOX/d5.sh yahoo.clean.txt n | head -n 30 > wrk/4
diff wrk/4 ref/4
if [ $? -ne 0 ]; then
	echo "Failure"
else
	echo "Success"
	let POINTS=$POINTS+1
fi

printf "   %-30s ... " "Test 5"
bash $DROPBOX/d5.sh yahoo.clean.txt n s | head -n 30 > wrk/5
diff wrk/5 ref/5
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
