mkdir -p wrk

WORTH=5
POINTS=0
SECONDS=0
MAXSECONDS=60

#NETID=$1
#DROPBOX="/escnfs/courses/fa21-cse-20289.01/$NETID/dropbox/shell/d3"

DROPBOX=$1

echo "Testing D4 ..."

printf "   %-30s ... " "Test 1"
bash $DROPBOX/d4-passwords.sh yahoo.clean.txt 3 3 4 1 5 > wrk/1
diff wrk/1 ref/1
if [ $? -ne 0 ]; then
	echo "Failure"
else
	echo "Success"
	let POINTS=$POINTS+2
fi

printf "   %-30s ... " "Test 2"
bash $DROPBOX/d4-passwords.sh yahoo.clean.txt 5 2 6 2 7 > wrk/2
diff wrk/1 ref/1
if [ $? -ne 0 ]; then
	echo "Failure"
else
	echo "Success"
	let POINTS=$POINTS+1
fi

printf "   %-30s ... " "Test 3"
bash $DROPBOX/d4-shakespeare.sh shakespeare.txt fish > wrk/3
diff wrk/3 ref/3
if [ $? -ne 0 ]; then
	echo "Failure"
else
	echo "Success"
	let POINTS=$POINTS+1
fi

printf "   %-30s ... " "Test 4"
bash $DROPBOX/d4-shakespeare.sh shakespeare.txt man > wrk/4
diff wrk/4 ref/4
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
