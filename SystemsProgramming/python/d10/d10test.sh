mkdir -p wrk

SCRIPT=$1
WORTH=6
POINTS=0
SECONDS=0
MAXSECONDS=60

echo "Testing $SCRIPT ..."

# test single predator and prey
printf "   %-30s ... " "Sample 1, 1 points"
python3 $SCRIPT -y hadrosaur -r tyrannosaur > wrk/1
diff wrk/1 ref/1
if [ $? -ne 0 ]; then
	echo "Failure"
else
	echo "Success"
	let POINTS=$POINTS+1
fi

# test single predator and prey
printf "   %-30s ... " "Sample 2, 1 points"
python3 $SCRIPT -y stegosaur -r allosaur > wrk/2
diff wrk/2 ref/2
if [ $? -ne 0 ]; then
        echo "Failure"
else
        echo "Success"
	let POINTS=$POINTS+1
fi

# test multiple prey, single predator
printf "   %-30s ... " "Sample 3, 2 points"
python3 $SCRIPT -y hadrosaur -y ceratop -r tyrannosaur > wrk/3
diff wrk/3 ref/3
if [ $? -ne 0 ]; then
        echo "Failure"
else
        echo "Success"
	let POINTS=$POINTS+2
fi

# test multiple prey, multiple predator, any order
printf "   %-30s ... " "Sample 4, 2 points"
python3 $SCRIPT -y hadrosaur -r tyrannosaur -r raptor -y ceratop -r allosaur > wrk/4
diff wrk/4 ref/4
if [ $? -ne 0 ]; then
        echo "Failure"
else
        echo "Success"
	let POINTS=$POINTS+2
fi

echo "Time: $SECONDS seconds (max allowed=$MAXSECONDS)"

if [ $SECONDS -gt $MAXSECONDS ]; then
	echo "  WARNING: Half credit due to time overage."
	let POINTS=$POINTS-$WORTH/2
fi

echo "Score: $POINTS / $WORTH"
