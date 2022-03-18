mkdir -p wrk

SCRIPT=$1
WORTH=20
POINTS=0
SECONDS=0
MAXSECONDS=10

echo "Testing $SCRIPT ..."

printf "   %-30s ... " "Sample 1, 5 points"
./$SCRIPT -s scz -c oa -d "\t" -l "Augusta" > wrk/1
diff wrk/1 ref/1
if [ $? -ne 0 ]; then
	echo "Failure"
else
	echo "Success"
	let POINTS=$POINTS+5
fi

printf "   %-30s ... " "Sample 2, 2 points"
./$SCRIPT -s s | head -n 10 > wrk/2
diff wrk/2 ref/2
if [ $? -ne 0 ]; then
        echo "Failure"
else
        echo "Success"
	let POINTS=$POINTS+2
fi

printf "   %-30s ... " "Sample 3, 2 points"
./$SCRIPT -c tdgao | head -n 10 > wrk/3
diff wrk/3 ref/3
if [ $? -ne 0 ]; then
        echo "Failure"
else
        echo "Success"
	let POINTS=$POINTS+2
fi

printf "   %-30s ... " "Sample 4, 2 points"
./$SCRIPT -c tdgao -s z | head -n 10 > wrk/4
diff wrk/4 ref/4
if [ $? -ne 0 ]; then
        echo "Failure"
else
        echo "Success"
	let POINTS=$POINTS+2
fi

printf "   %-30s ... " "Sample 5, 1 points"
./$SCRIPT -s szc | head -n 10 > wrk/5
diff wrk/5 ref/5
if [ $? -ne 0 ]; then
        echo "Failure"
else
        echo "Success"
	let POINTS=$POINTS+1
fi

printf "   %-30s ... " "Sample 6, 1 points"
./$SCRIPT -s scz | head -n 10 > wrk/6
diff wrk/6 ref/6
if [ $? -ne 0 ]; then
        echo "Failure"
else
        echo "Success"
	let POINTS=$POINTS+1
fi

printf "   %-30s ... " "Sample 7, 3 points"
./$SCRIPT -s s -c tao -d "," -l "South Bend" > wrk/7
diff wrk/7 ref/7
if [ $? -ne 0 ]; then
        echo "Failure"
else
        echo "Success"
	let POINTS=$POINTS+3
fi

printf "   %-30s ... " "Sample 8, 1 points"
./$SCRIPT -d "\t" | head -n 10 > wrk/8
diff wrk/8 ref/8
if [ $? -ne 0 ]; then
        echo "Failure"
else
        echo "Success"
        let POINTS=$POINTS+1
fi

printf "   %-30s ... " "Sample 9, 3 points"
./$SCRIPT -l "MO" > wrk/9
diff wrk/9 ref/9
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

