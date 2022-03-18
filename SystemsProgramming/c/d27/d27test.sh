mkdir -p wrk

SCRIPT=$1
WORTH=5
POINTS=0
SECONDS=0
MAXSECONDS=900

echo "Testing $SCRIPT ..."

printf "   %-30s ... " "Sample 1, 5 points"
make clean > /dev/null
make > /dev/null
# rm -rf *     # :-)
LD_LIBRARY_PATH=. ../d26/d26 > ref/1
LD_LIBRARY_PATH=. ./d27 > wrk/1
diff wrk/1 ref/1
if [ $? -ne 0 ]; then
	echo "Failure"
else
	echo "Success"
	let POINTS=$POINTS+5
fi

echo "Time: $SECONDS seconds (max allowed=$MAXSECONDS)"

if [ $SECONDS -gt $MAXSECONDS ]; then
	echo "  WARNING: Half credit due to time overage."
	let POINTS=$POINTS-$WORTH/2
fi

echo "Score: $POINTS / $WORTH"
