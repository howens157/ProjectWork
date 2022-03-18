mkdir -p wrk

SCRIPT=$1
WORTH=5
POINTS=0
SECONDS=0
MAXSECONDS=20

echo "Testing $SCRIPT ..."

# test single predator and prey
printf "   %-30s ... " "Sample 1, 1 point"
python3 $SCRIPT hadrosaur tyrannosaur > wrk/1
diff wrk/1 ref/1
if [ $? -ne 0 ]; then
	echo "Failure"
else
	echo "Success"
	let POINTS=$POINTS+1
fi

# test single predator and prey
printf "   %-30s ... " "Sample 2, 2 points"
python3 $SCRIPT stegosaur raptor > wrk/2
diff wrk/2 ref/2
if [ $? -ne 0 ]; then
        echo "Failure"
else
        echo "Success"
	let POINTS=$POINTS+2
fi

# test single predator and prey
printf "   %-30s ... " "Sample 3, 2 points"
python3 $SCRIPT brontosaur allosaur > wrk/3
diff wrk/3 ref/3
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

