mkdir -p wrk

PID=$1
WORTH=6
POINTS=0
SECONDS=0
MAXSECONDS=300

echo "Testing ..."

printf "   %-30s ... " "Sample 1, 3 points"
make clean > /dev/null
make > /dev/null
LD_LIBRARY_PATH=. ./d25_signaler $PID 92 > wrk/1
diff wrk/1 ref/1
if [ $? -ne 0 ]; then
	echo "Failure"
else
	echo "Success"
	let POINTS=$POINTS+3
fi

printf "   %-30s ... " "Sample 2, 2 points"
make clean > /dev/null
make > /dev/null
LD_LIBRARY_PATH=. ./d25_signaler $PID 8080 > wrk/2
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
