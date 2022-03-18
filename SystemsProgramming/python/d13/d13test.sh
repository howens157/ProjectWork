mkdir -p wrk

PORT=$1
WORTH=6
POINTS=0
SECONDS=0
MAXSECONDS=30

echo "Testing  ..."

# test single predator and prey
printf "   %-30s ... " "Sample 1, 1 points"
python3 dinoclient.py -n localhost -r tyrannosaur -y hadrosaur -p $PORT > wrk/1
diff wrk/1 ref/1
if [ $? -ne 0 ]; then
	echo "Failure"
else
	echo "Success"
	let POINTS=$POINTS+1
fi

# test single predator and multiple preys
printf "   %-30s ... " "Sample 2, 1 points"
python3 dinoclient.py -n localhost -r tyrannosaur -y hadrosaur -y ceratop -p $PORT > wrk/2
diff wrk/2 ref/2
if [ $? -ne 0 ]; then
	echo "Failure"
else
	echo "Success"
	let POINTS=$POINTS+2
fi

# test multiple predators and preys
printf "   %-30s ... " "Sample 3, 3 points"
python3 dinoclient.py -n localhost -r tyrannosaur -y hadrosaur -y ceratop -r raptor -p $PORT > wrk/3
diff wrk/3 ref/3
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
