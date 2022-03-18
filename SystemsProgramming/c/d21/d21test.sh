mkdir -p wrk

SCRIPT=$1
WORTH=6
POINTS=0
SECONDS=0
MAXSECONDS=5

echo "Testing $SCRIPT ..."

printf "   %-30s ... " "checking your d21 implementation, 3 points"
gcc -o d21 d21.c
LD_LIBRARY_PATH=. ./d21 dino.dat > wrk/1
diff wrk/1 ref/1
if [ $? -ne 0 ]; then
	echo "Failure"
else
	echo "Success"
	let POINTS=$POINTS+3
fi

printf "   %-30s ... " "checking if your dino.dat works with the reference implementation, 3 points"
gcc -o d21 d21.c
LD_LIBRARY_PATH=. ./d21-ref dino.dat > wrk/2
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
