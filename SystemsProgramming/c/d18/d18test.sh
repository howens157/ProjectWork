mkdir -p wrk

SCRIPT=$1
WORTH=6
POINTS=0
SECONDS=0
MAXSECONDS=5

echo "Testing $SCRIPT ..."

printf "   %-30s ... " "Sample 1, 6 points"
echo ""
make clean
make
LD_LIBRARY_PATH=. ./d18 > wrk/1
diff wrk/1 ref/1
if [ $? -ne 0 ]; then
	echo "Failure"
else
	echo "Success"
	let POINTS=$POINTS+6
fi

echo "Time: $SECONDS seconds (max allowed=$MAXSECONDS)"

if [ $SECONDS -gt $MAXSECONDS ]; then
	echo "  WARNING: Half credit due to time overage."
	let POINTS=$POINTS-$WORTH/2
fi

echo "Score: $POINTS / $WORTH"
