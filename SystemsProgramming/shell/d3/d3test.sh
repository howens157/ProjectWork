mkdir -p wrk

WORTH=4
POINTS=0
SECONDS=0
MAXSECONDS=10

#NETID=$1
#DROPBOX="/escnfs/courses/fa21-cse-20289.01/$NETID/dropbox/d3"

DROPBOX=$1

echo "Testing D3 ..."

printf "   %-30s ... " "Task 1"
bash $DROPBOX/d3-1.sh | head -n 20 > wrk/1
diff wrk/1 ref/1
if [ $? -ne 0 ]; then
	echo "Failure"
else
	echo "Success"
	let POINTS=$POINTS+1
fi

printf "   %-30s ... " "Task 2"
bash $DROPBOX/d3-2.sh | head -n 20 > wrk/2
diff wrk/2 ref/2
if [ $? -ne 0 ]; then
	echo "Failure"
else
	echo "Success"
	let POINTS=$POINTS+1
fi

printf "   %-30s ... " "Task 3"
bash $DROPBOX/d3-3.sh | head -n 20 > wrk/3
diff wrk/3 ref/3
if [ $? -ne 0 ]; then
	echo "Failure"
else
	echo "Success"
	let POINTS=$POINTS+1
fi

printf "   %-30s ... " "Task 4"
bash $DROPBOX/d3-4.sh | head -n 20 > wrk/4
diff wrk/4 ref/4
if [ $? -ne 0 ]; then
	echo "Failure"
else
	echo "Success"
	let POINTS=$POINTS+1
fi

printf "   %-30s ... " "Task 5"
bash $DROPBOX/d3-5.sh | head -n 20 > wrk/5
diff wrk/5 ref/5
if [ $? -ne 0 ]; then
	echo "Failure"
else
	echo "Success"
	let POINTS=$POINTS+1
fi

printf "   %-30s ... " "Task 6"
bash $DROPBOX/d3-6.sh | head -n 20 > wrk/6
diff wrk/6 ref/6
if [ $? -ne 0 ]; then
	echo "Failure"
else
	echo "Success"
	let POINTS=$POINTS+1
fi

printf "   %-30s ... " "Task 7"
bash $DROPBOX/d3-7.sh | head -n 20 > wrk/7
diff wrk/7 ref/7
if [ $? -ne 0 ]; then
	echo "Failure"
else
	echo "Success"
	let POINTS=$POINTS+1
fi

printf "   %-30s ... " "Task 8"
bash $DROPBOX/d3-8.sh > wrk/8
diff wrk/8 ref/8
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

let POINTS=$POINTS/2

echo "Score: $POINTS / $WORTH"
