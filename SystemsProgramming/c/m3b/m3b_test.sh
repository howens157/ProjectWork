mkdir -p wrk

WORTH=10
POINTS=0
SECONDS=0
MAXSECONDS=15

echo "Testing simg_display, simg_convert ..."

printf "   %-30s ... " "simg_display, black and white, 1 point"
make clean > /dev/null
make libsimg.so > /dev/null
LD_LIBRARY_PATH=. ./simg_display ref/dino_ref_bw.simg > wrk/1
diff wrk/1 ref/1
if [ $? -ne 0 ]; then
	echo "Failure"
else
	echo "Success"
	let POINTS=$POINTS+1
fi

printf "   %-30s ... " "simg_display, color, 1 point"
LD_LIBRARY_PATH=. ./simg_display ref/dino_ref_cl.simg > wrk/2
diff wrk/2 ref/2
if [ $? -ne 0 ]; then
        echo "Failure"
else
        echo "Success"
        let POINTS=$POINTS+1
fi

printf "   %-30s ... " "simg_convert, dino, 4 points"
LD_LIBRARY_PATH=. ./simg_convert ref/dino.txt wrk/dino.simg > /dev/null
diff wrk/dino.simg ref/dino_ref_bw.simg
if [ $? -ne 0 ]; then
        echo "Failure"
else
        echo "Success"
        let POINTS=$POINTS+4
fi

printf "   %-30s ... " "simg_convert, at-at, 4 points"
LD_LIBRARY_PATH=. ./simg_convert ref/walker.txt wrk/walker.simg > /dev/null
diff wrk/walker.simg ref/walker_ref_bw.simg
if [ $? -ne 0 ]; then
        echo "Failure"
else
        echo "Success"
        let POINTS=$POINTS+4
fi


echo "Time: $SECONDS seconds (max allowed=$MAXSECONDS)"

if [ $SECONDS -gt $MAXSECONDS ]; then
	echo "  WARNING: Half credit due to time overage."
	let POINTS=$POINTS-$WORTH/2
fi

echo "Score: $POINTS / $WORTH"

echo "(note: simg_edit is worth 10 additional points and "
echo "    will be graded by hand due to interactive input)"

