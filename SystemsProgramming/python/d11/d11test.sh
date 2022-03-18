rm -rf wrk # CAUTION
mkdir -p wrk

WORTH=6
POINTS=0
SECONDS=0
MAXSECONDS=600

echo "Testing D11 ..."

# test writing data unencrypted
printf "   %-30s ... " "Sample 1, 1 points"
python3 dinocolumns.py -d dinosaur.dat -o wrk/1 -c 5,15,16 -l 15
diff wrk/1 ref/1
if [ $? -ne 0 ]; then
	echo "Failure"
else
	echo "Success"
	let POINTS=$POINTS+1
fi

# test writing data encrypted, single line
printf "   %-30s ... " "Sample 2, 2 points"
python3 dinocolumns.py -d dinosaur.dat -o wrk/2a -c 5,15,16 -l 1 -e $1
python3 easycrypt.py wrk/2a $1 > wrk/2b
diff wrk/2b ref/2b
if [ $? -ne 0 ]; then
        echo "Failure"
else
        echo "Success"
	let POINTS=$POINTS+2
fi

# test writing data encrypted, multiple lines
printf "   %-30s ... " "Sample 3, 3 points"
python3 dinocolumns.py -d dinosaur.dat -o wrk/3a -c 5,15,16 -l 5 -e $1
python3 easycrypt.py wrk/3a $1 > wrk/3b
diff wrk/3b ref/3b
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
