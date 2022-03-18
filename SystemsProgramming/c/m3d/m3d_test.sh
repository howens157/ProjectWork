mkdir -p wrk

WORTH=2
POINTS=0
SECONDS=0
MAXSECONDS=90

echo "Testing ..."

printf "   %-30s ... " "message 0, 1 point"
mkdir -p messages
rm -rf messages/msg_*.txt
make clean > /dev/null
make > /dev/null
LD_LIBRARY_PATH=. ./m3d > /dev/null
diff messages/msg_0.txt ref/msg_0.txt
if [ $? -ne 0 ]; then
	echo "Failure"
else
	echo "Success"
	let POINTS=$POINTS+1
fi

printf "   %-30s ... " "message 1, 1 point"
diff messages/msg_1.txt ref/msg_1.txt
if [ $? -ne 0 ]; then
	echo "Failure"
else
	echo "Success"
	let POINTS=$POINTS+1
fi

echo "Time: $SECONDS seconds (max allowed=$MAXSECONDS)"

if [ $SECONDS -gt $MAXSECONDS ]; then
	echo "  WARNING: Half credit due to time overage."
	let POINTS=$POINTS-$WORTH/2
fi

echo "Score: $POINTS / $WORTH"

echo "  NOTE: This is just a sample test file.  See end of README file for details.  This assignment is really worth 20 points not 2."

