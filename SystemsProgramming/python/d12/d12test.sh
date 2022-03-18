mkdir -p wrk

SCRIPT=$1
WORTH=5
POINTS=0
SECONDS=0
MAXSECONDS=30

echo "Testing $SCRIPT ..."

python3 $SCRIPT hosts.txt > wrk/1

# test single line connection
printf "   %-30s ... " "Sample 1, 1 points"
head -n 1 wrk/1 > wrk/2
diff wrk/2 ref/2
if [ $? -ne 0 ]; then
	echo "Failure"
else
	echo "Success"
	let POINTS=$POINTS+1
fi

# test connection refused message
printf "   %-30s ... " "Sample 2, 1 points"
head -n 4 wrk/1 | tail -n 1 > wrk/3
diff wrk/3 ref/3
if [ $? -ne 0 ]; then
	echo "Failure"
else
	echo "Success"
	let POINTS=$POINTS+1
fi

# test connection timeout message
printf "   %-30s ... " "Sample 3, 1 points"
tail -n 1 wrk/1 > wrk/4
diff wrk/4 ref/4
if [ $? -ne 0 ]; then
	echo "Failure"
else
	echo "Success"
	let POINTS=$POINTS+1
fi

# test complete output
printf "   %-30s ... " "Sample 4, 2 points"
diff wrk/1 ref/1
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
