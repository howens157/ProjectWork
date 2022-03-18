mkdir -p wrk

SCRIPT=$1
WORTH=5
POINTS=0
SECONDS=0
MAXSECONDS=5

echo "Testing $SCRIPT ..."

# test dinosaur.txt (short file)
printf "   %-30s ... " "Sample 1, 2 points"
python3 $SCRIPT dinosaur.txt > wrk/1
diff wrk/1 ref/1
if [ $? -ne 0 ]; then
	echo "Failure"
else
	echo "Success"
	let POINTS=$POINTS+2
fi

# test yahoo.clean.short.txt (longer file)
printf "   %-30s ... " "Sample 2, 3 points"
python3 $SCRIPT yahoo.clean.short.txt > wrk/2
diff wrk/2 ref/2
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
