mkdir -p wrk

WORTH=20
POINTS=0
SECONDS=0
MAXSECONDS=90

echo "Testing ..."

printf "   %-30s ... " "your tx(), reference rx(), 6 points"
LD_LIBRARY_PATH=. ./smt_tx "diseases desperate grown, by desperate appliance are relieved, or not at all."
mv smtadt.bin wrk/smtadt.bin
diff wrk/smtadt.bin ref/smtadt.bin
if [ $? -ne 0 ]; then
	echo "Failure"
else
	echo "Success"
	let POINTS=$POINTS+6
fi

printf "   %-30s ... " "reference tx(), your rx(), 6 points"
LD_LIBRARY_PATH=. ./smt_rx ref/smtadt.bin > wrk/2
diff wrk/2 ref/2
if [ $? -ne 0 ]; then
	echo "Failure"
else
	echo "Success"
	let POINTS=$POINTS+6
fi

printf "   %-30s ... " "your tx(), your rx(), 8 points"
LD_LIBRARY_PATH=. ./smt_tx "olly wolly polly wolly ump bump fizz"
LD_LIBRARY_PATH=. ./smt_rx smtadt.bin > wrk/3
diff wrk/3 ref/3
if [ $? -ne 0 ]; then
	echo "Failure"
else
	echo "Success"
	let POINTS=$POINTS+8
fi

echo "Time: $SECONDS seconds (max allowed=$MAXSECONDS)"

if [ $SECONDS -gt $MAXSECONDS ]; then
	echo "  WARNING: Half credit due to time overage."
	let POINTS=$POINTS-$WORTH/2
fi

echo "Score: $POINTS / $WORTH"
