mkdir -p wrk

SCRIPT=$1
WORTH=10
POINTS=0
SECONDS=0
MAXSECONDS=60

echo "Testing $SCRIPT ..."

printf "   %-30s ... " "Sample 1, 2 points"
./$SCRIPT stegosaurus tyrannosaurus > wrk/1
diff wrk/1 ref/1
if [ $? -ne 0 ]; then
	echo "Failure"
else
	echo "Success"
	let POINTS=$POINTS+2
fi

printf "   %-30s ... " "Sample 2, 2 points"
./$SCRIPT allosaurus stegosaurus > wrk/2
diff wrk/2 ref/2
if [ $? -ne 0 ]; then
        echo "Failure"
else
        echo "Success"
	let POINTS=$POINTS+2
fi

printf "   %-30s ... " "Sample 3, 2 points"
./$SCRIPT tyrannosaurus sauropod > wrk/3
diff wrk/3 ref/3
if [ $? -ne 0 ]; then
        echo "Failure"
else
        echo "Success"
	let POINTS=$POINTS+2
fi

printf "   %-30s ... " "Sample 4, 2 points"
./$SCRIPT hadrosaurus sauropod > wrk/4
diff wrk/4 ref/4
if [ $? -ne 0 ]; then
        echo "Failure"
else
        echo "Success"
	let POINTS=$POINTS+2
fi

printf "   %-30s ... " "Sample 5, 2 points"
./$SCRIPT eoraptor hadrosaur > wrk/5
diff wrk/5 ref/5
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

